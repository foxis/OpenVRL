#include "openvrl.h"

namespace openvrl {

DWORD dllOpenVRL_Version(void)
{
	return OPENVRL_VERSION;
}

DWORD dllOpenVRL_Description(CHAR* str, size_t max_cb)
{
	CHAR tmp[1024];
	sprintf(tmp, 
		"Library Name:\tOpenVRL\n"
		"Library Version:\t%s\n"
		"Library Description:\t%s\n\n"
		"Copyright %s\n"
		"Author:\t\t%s\n"
		"Release Date:\t%s\n"
		"Build Date:\t%s\n"
		"Port ID:\t\t0x%02x\n"
		"Port OS:\t\t%s\n"
		"Port Pipeline:\t%s\n"
		"Ported by:\t%s\n\n"
		"Contacts:\t%s\n",
		OPENVRL_VERSION_STR,
		"Open Source Virtual Reality Library",
		"(c) 1996-2002, Andrius Mikonis a.k.a. FoxiE",
		"Andrius Mikonis a.k.a. FoxiE",
		OPENVRL_RELEASE_DATE,
		OPENVRL_LAST_BUILD_DATE,
		OPENVRL_PORT_ID,
		OPENVRL_OS,
		OPENVRL_PIPELINE,
		OPENVRL_PORTED_BY,
"Andrius a.k.a. FoxiE\nemail: vienas@delfi.lt\nsmail: Kapsø 36-31 Vilnius LT2038, Lithuania\n"
"home#: (+37025)695451\nmob.#: (+370)69993651\n"
	);
	strncpy(str, tmp, max_cb);
	return strlen(str);
}

//
//
//
CSystem::CSystem()
	: CWindow(),
	  m_pD3D(0), m_pd3dDevice(0), m_FPS(25)
{
	m_Pipeline = 0;
	m_World = 0;
	setActive(false);
}

CSystem::CSystem(HINSTANCE hInstance, HINSTANCE hPrevInstance,
        const CString& szCmdLine, int nCmdShow, uint X, uint Y, uint Width, uint Height)
	: CWindow(hInstance, hPrevInstance,
        nCmdShow, X, Y, Width, Height),
	  m_szCmdLine(szCmdLine),
	  m_pD3D(0), m_pd3dDevice(0), m_FPS(25)
{
	m_Pipeline = 0;
	m_World = 0;
	setActive(false);
}

CSystem::CSystem(HINSTANCE hInstance, HINSTANCE hPrevInstance,
        const CString& szCmdLine, int nCmdShow, 
		const CString& szWinTitle, 
		const CString& szWinClass,
		uint X, uint Y, uint Width, uint Height)
	: CWindow(hInstance, hPrevInstance,
        nCmdShow, szWinTitle, 
		szWinTitle,
		X, Y, Width, Height),
	  m_szCmdLine(szCmdLine),
	  m_pD3D(0), m_pd3dDevice(0), m_FPS(25)
{
	setActive(false);
}

CSystem::~CSystem()
{
	printf("System: dtor\n");
	ReleaseD3D();
	printf("System: dtor release sys\n");
	ReleaseSystem();
	printf("System: dtor done\n");
}

int CSystem::run(bool nOwnLoop)
{
	MSG message;

	if ( CWindow::run(false) )
		return -1;

	if ( InitSystem() || InitD3D() ) {
		MessageBox("Sorry dude, D3D initialization failed ;(, I shall now exit", "Error", MB_OK);
		return -1;
	}

	printf("CSystem: preparing world...\n");
	World()->Prepare();

	setActive(true);

	if ( nOwnLoop ) do {
		if( PeekMessage( &message, NULL, 0U, 0U, PM_REMOVE ) ) {
			TranslateMessage( &message );
            DispatchMessage( &message );
        } else if ( isActive() ) {
			BeginScene();
			FrameCalculate();
			FrameRender();
			EndScene();
		}
    } while( nOwnLoop && message.message!=WM_QUIT );

	setActive(false);

	World()->Release();

	if ( nOwnLoop ) {
		ReleaseD3D();
		ReleaseSystem();
	}

	return nOwnLoop?message.wParam:0;
}

LRESULT CSystem::WndProc(UINT m, WPARAM w, LPARAM l)
	{
	switch (m) {
	case WM_PAINT:
		if ( isActive() ) {
			BeginScene();
			FrameCalculate();
			FrameRender();
			EndScene();
			ValidateRect( NULL );
		} 
		break; 
	case WM_DESTROY:
		setActive(false);
	}
	return CWindow::WndProc(m,w,l);
}

/***/
bool CSystem::InitSystem()
{
    // Create the D3D object, which is needed to create the D3DDevice.
	if( ( m_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) )==0 ) {
		MessageBox("Could not create Direct3D!!!", "Error", MB_OK);
        return true;
	}

    // Get the current desktop display mode
    D3DDISPLAYMODE d3ddm;
    if( FAILED( m_pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm ) ) ) {
		MessageBox("Could not retrieve Adapter Display Mode!!!", "Error", MB_OK);
        return true;
	}

    // Set up the structure used to create the D3DDevice. Most parameters are
    // zeroed out. We set Windowed to TRUE, since we want to do D3D in a
    // window, and then set the SwapEffect to "discard", which is the most
    // efficient method of presenting the back buffer to the display.  And 
    // we request a back buffer format that matches the current desktop display 
    // format.
    D3DPRESENT_PARAMETERS d3dpp; 
    ZeroMemory( &d3dpp, sizeof(d3dpp) );
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = d3ddm.Format;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

    // Create the Direct3D device. Here we are using the default adapter (most
    // systems only have one, unless they have multiple graphics hardware cards
    // installed) and requesting the HAL (which is saying we want the hardware
    // device rather than a software one). Software vertex processing is 
    // specified since we know it will work on all cards. On cards that support 
    // hardware vertex processing, though, we would see a big performance gain 
    // by specifying hardware vertex processing.
    if( FAILED( m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd(),
                                      D3DCREATE_HARDWARE_VERTEXPROCESSING,//|D3DCREATE_PUREDEVICE
                                      &d3dpp, &m_pd3dDevice ) ) )
    {
		MessageBox("Could not create Direct3D HAL Device!!!\n"
			"Trying to create Direct3D REF device...", "Error", MB_OK);
	    if( FAILED( m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd(),
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &m_pd3dDevice ) ) )
	    {
			MessageBox("Could not create Direct3D REF Device!!!", "Error", MB_OK);
	        return true;
		}
    }

	m_Pipeline = create_Pipeline();
	m_World = create_World();
	m_Pipeline->Initialize();

	return false;
}

bool CSystem::InitD3D()
{
    // Device state would normally be set here
	return false;
}

int CSystem::BeginScene()
{
	m_FPS.start_frame_measure();
	return m_Pipeline->BeginScene();
}

int CSystem::EndScene()
{
	int rc = m_Pipeline->EndScene();
	m_FPS.stop_frame_measure();
	return rc;
}

bool CSystem::FrameCalculate()
{
	const real dx = m_FPS.frame_dx();
	m_FPS.start_calculate_measure();
	m_Pipeline->Update((dx==0)?.016:dx, m_World);
	m_FPS.stop_calculate_measure();
	return false;
}

bool CSystem::FrameRender()
{
	m_FPS.start_render_measure();
	m_Pipeline->RendereScene();
	m_FPS.stop_render_measure();
	return false;
}

bool CSystem::ReleaseD3D()
{	
	return false;
}

bool CSystem::ReleaseSystem()
{
	printf("System: releasesystem %p %p %p %p\n", m_World, m_Pipeline, m_pd3dDevice, m_pD3D);
	if ( m_World ) 
	{ 
		printf("System: release world\n");
		m_World->Release();
		printf("System: delete world\n");
		delete_World(m_World); 
		m_World=0; 
	}
	if ( m_Pipeline ) { 
		printf("System: release pipeline\n");
		m_Pipeline->Cleanup();
		printf("System: delete pipeline\n");
		delete_Pipeline(m_Pipeline); 
		m_Pipeline=0; 
	}

		printf("System: release d3d\n");
    if( m_pd3dDevice != NULL) {
        m_pd3dDevice->Release();
		m_pd3dDevice = 0;
	}

    if( m_pD3D != NULL) {
        m_pD3D->Release();
		m_pD3D = 0;
	}

	return false;
}


}