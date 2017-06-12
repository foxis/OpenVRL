#include "system/ovrlwindow.h"

namespace openvrl {

CWindow::CWindow()
{
	m_szWindowTitle = get_window_title();
	m_szWindowClass = get_window_class();
}

CWindow::CWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance,
        int nCmdShow,uint X, uint Y,uint Width, uint Height)
	: m_hInstance(hInstance), m_hPrevInstance(hPrevInstance),
	m_nCmdShow(nCmdShow),
	m_hWnd(0), m_X(X), m_Y(Y),
	m_Width(Width), m_Height(Height)
{
	m_szWindowTitle = get_window_title();
	m_szWindowClass = get_window_class();
}

CWindow::CWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance,
        int nCmdShow, const CString& szWinTitle, 
		const CString& szWinClass,
		uint X, uint Y, uint Width, uint Height)
	: m_hInstance(hInstance), m_hPrevInstance(hPrevInstance),
	m_nCmdShow(nCmdShow),
	m_hWnd(0), m_szWindowTitle(szWinTitle), m_szWindowClass(szWinClass),
	m_X(X), m_Y(Y), m_Width(Width), m_Height(Height)
{
}

CWindow::~CWindow()
{
	if ( m_hWnd ) {
		CloseWindow();
		UnregisterClass(m_szWindowClass(), m_hInstance );
	}
}

bool CWindow::RegisterClass(WNDCLASS& wc)
{
  wc.style = CS_HREDRAW|CS_VREDRAW;
  wc.lpfnWndProc = (WNDPROC)ovrlDefWndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = DLGWINDOWEXTRA+6;
  wc.hInstance = m_hInstance;
  wc.hIcon = 0;
  wc.hCursor = LoadCursor(0, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND+1);
  wc.lpszMenuName = 0;
  wc.lpszClassName = m_szWindowClass.get_cstr();
  
  return false;
}

bool CWindow::RegisterClass(WNDCLASSEX& wc)
{
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW|CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)ovrlDefWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = DLGWINDOWEXTRA+6;
	wc.hInstance = m_hInstance;
	wc.hIcon = 0;
	wc.hIconSm = 0;
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND+0);
	wc.lpszMenuName = 0;
	wc.lpszClassName = m_szWindowClass.get_cstr();
  
	return false;
}

bool CWindow::LoadStrings()
{
	return false;
}

bool CWindow::InitInstance()
{
	m_hWnd = CreateWindowEx(
		get_window_style_ex(),
		m_szWindowClass(), 
		m_szWindowTitle(), 
		get_window_style(),
		m_X, m_Y, 
		m_Width, m_Height, 
		NULL, NULL, 
		m_hInstance, NULL);

   if (!m_hWnd)
   {
      return true;
   }

   SetWindowLong(m_hWnd, DLGWINDOWEXTRA, (UINT)this);
   SetWindowWord(m_hWnd, DLGWINDOWEXTRA+4, 1313);
   ShowWindow(m_hWnd, m_nCmdShow);
   UpdateWindow(m_hWnd);

   return false;
}

int CWindow::run(bool nOwnLoop)
{
	MSG message;
	WNDCLASSEX wc;

	RegisterClass(wc);
	RegisterClassEx(&wc);
	if ( InitInstance () )
		return -1;

	ShowWindow(m_hWnd,SW_SHOW);

	if ( !nOwnLoop )
		return 0;

	while ( GetMessage(&message, 0, 0, 0) ) {
//		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
			TranslateMessage(&message);
			DispatchMessage(&message);
//		}
	}

	return (int)(nOwnLoop)?message.wParam:0;
}


/*******************************************/
/*******************************************/
/*******************************************/
LRESULT CWindow::WndProc(UINT msg, WPARAM wp, LPARAM lp)
{
	switch ( msg ) {
	case WM_DESTROY:
		PostQuitMessage(0);
        break;
	}
	return DefWindowProc(m_hWnd, msg, wp, lp);
}


LRESULT CALLBACK ovrlDefWndProc( HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam )
{
  CWindow* wnd = (CWindow*)GetWindowLong(hWnd, DLGWINDOWEXTRA);

  if ( GetWindowWord(hWnd, DLGWINDOWEXTRA+4)!=1313 )
         return DefWindowProc(hWnd, iMessage, wParam, lParam);
  else
         return wnd->WndProc( iMessage, wParam, lParam );
}

}