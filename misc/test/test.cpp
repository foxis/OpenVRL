// test.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <process.h>
#include "resource.h"

#include "openvrl.h"


using namespace openvrl;
//
//
//
class CMyMesh : public CBody
{
public:
	C3DVector pos,or,vel,w,v,l;
	CBoxGeom* bg;
	CSphereGeom* sg;
	bool a;
	real m;
	bool s;

	CMyMesh() : CBody() 
	{
		pos = C3DVector::ZERO();
		or = C3DVector::ZERO();
		v = C3DVector::ZERO();
		w = C3DVector::ZERO();
		a = false;
		m =1;
		s = true;
		l = C3DVector::UNITXYZ();
	}
	virtual ~CMyMesh() 
	{
	}

	virtual void Release()
	{
		CBody::Release();
	}

	virtual void Prepare()
	{
		CBody::Prepare();

		try {
			if ( a )
				Attach("tcube", 0); //def/mesh/DIAMOND
			else
				Attach("cube", 0); //def/mesh/DIAMOND
		}
		catch ( openvrl::CException& e )
		{
			char str[1024];
			e.Format(str, 1024);
			MessageBox(0, str, "Error attaching mesh to a body", MB_OK|MB_ICONERROR);
		}

		if (a)
		{
			CxfMaterial * mt= GetMesh()->getSubset(0).material();
			CxfTexture* tx = GetPipeline()->textures->find("default");
			if ( mt )
				mt->set_map(MMAP_AMBIENT, tx);
		}

		GetTransformMatrix().set_scale(l.x(),l.y(),l.z());

		bg = new CBoxGeom();
		bg->Create();
		bg->Attach(this);
		bg->SetLengths(C3DVector(l.x(),l.y(),l.z()));
		SetGeom(bg);

		// this thing is needed, because if we use composite objects
		// with many geoms, we need to create a geom space and insert all the geoms there
		// then attach the space to the body
		// then add the body to the physics engine
		// 
		// 2005-02-04 5:01 @todo can make objects auto add into physics engine. or
		// manually... dunno, whether add a flag of auto addition. but for now let it be that way.
		GetPhysicsEngine()->GetSpace()->Add(GetGeom());	

		SetPosition(pos);
		SetOrientation(or);
		SetAngularVelocity(w);
		SetLinearVelocity(v);

		SetMass(m);

		C4x4Matrix I;
		const real 
			lx = l.x(),
			ly = l.y(),
			lz = l.z();
		I.set(
			m/12.0 * (ly*ly + lz*lz),0,0,0,
			0,m/12.0 * (lx*lx + lz*lz),0,0,
			0,0,m/12.0 * (lx*lx + ly*ly),0,
			0,0,0,1
			);
		SetInertiaTensor(I);

//		SetMovable(s);
		if ( !s )
		{
			SetTypeBits(GetTypeBits() & (~OVRL_BT_MOVEABLE));
			EnablePhysics(s);
		}
	}
	virtual void PreparePhysics()
	{
		CBody::PreparePhysics();
	}

	virtual int Update(real dt)
	{
		return CBody::Update(dt);
	}
	virtual void UpdatePhysics(real dt)
	{
		CBody::UpdatePhysics(dt);

//		C3DVector a = GetPosition();
//		C3DVector b = GetGeom()->GetPosition();
	}
};


class CMyCamera : public CCamera
{
public:
	CMyCamera() {  }

	virtual void Prepare()
	{
		CCamera::Prepare();

		Attach("default", 1);

//		SetPosition();
		SetLookAt(C3DVector(-34,9.688,30.2995), C3DVector(0,0,0),0);
//		SetOrientation(C3DVector(-.1,4.5*constants::m_pi/6,.1));
		EnablePhysics(false);
	};

	void F(real x)
	{
		C4x4Matrix m( GetOrientationMatrix());
		C3DVector v(0,0,1);
		v.mul(m);
		v = v*x + GetPosition();
		SetPosition(v);
	};
	void pitch(real x)
	{
		C4x4Matrix m = GetOrientationMatrix();
		m.mul(m.rotate(x,0,0));
		SetOrientationMatrix(m);
	}
	void yaw(real x)
	{
		C4x4Matrix m = GetOrientationMatrix();
		m.mul(m.rotate(0,x,0));
		SetOrientationMatrix(m);
	}
	void roll(real x)
	{
		C4x4Matrix m = GetOrientationMatrix();
		m.mul(m.rotate(0,0,x));
		SetOrientationMatrix(m);
	}

	virtual int Update(real time_step)
	{
		CCamera::Update(time_step);

		return false;
	}
};


class CMyTest : public CSystem
{
	CTPLLib	*m_tpl;
	CMyMesh *m_mesh;
	CMyMesh *m_mesh1;
	CMyCamera *camera;

public: 
	CMyTest(HINSTANCE hInstance, HINSTANCE hPrevInstance,
        const CString& szCmdLine, int nCmdShow)
		: CSystem(hInstance, hPrevInstance,
        szCmdLine, nCmdShow, "Hello, this is just a test", "Fucking test",
		  10, 10, 640, 640)
	{
	}
	virtual ~CMyTest()
	{
	}

	virtual ::DWORD get_window_style() const
	{
		return WS_VISIBLE|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX|WS_DLGFRAME;
	}

protected:
	virtual bool RegisterClass(WNDCLASSEX& wc)
	{
		CWindow::RegisterClass(wc);
		
		wc.hIcon			= LoadIcon(IDI_TEST);
//		wc.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
		wc.lpszMenuName	= (::LPCSTR)IDC_TEST;
		wc.hIconSm		= LoadIcon(IDI_SMALL);

		return false;
	}

	virtual ::LRESULT WndProc(::UINT m, ::WPARAM w, ::LPARAM l)
	{
		::WORD wmId, wmEvent;
		::CHAR *szHello = "Sveiki pyplai!!!";

		switch (m) {
		case WM_COMMAND:
			wmId    = (::WORD)w; 
			wmEvent = (::WORD)(w>>16); 
			// Parse the menu selections:
			switch (wmId) {
			case IDM_ABOUT:
				MessageBox("hello", "FoxiE", MB_OK);
				break;
			case IDM_EXIT:
				Destroy();
				break;
			}
			break;
		case WM_CHAR:
			switch ( w )
			{
			case 'Q': camera->F(1); break;
			case 'A': camera->F(-1); break;
			case 'W': camera->pitch(.05); break;
			case 'S': camera->pitch(-.05); break;
			case 'Z': camera->yaw(-.05); break;
			case 'X': camera->yaw(.05); break;
			case 'R': camera->roll(-.05); break;
			case 'F': camera->roll(.05); break;
			}
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		}
		return CSystem::WndProc(m,w,l);
	}

protected:
	virtual bool InitD3D();
	virtual bool FrameCalculate();
	virtual bool ReleaseD3D();
};


int APIENTRY WinMain(::HINSTANCE hInstance,
					 ::HINSTANCE hPrevInstance,
					 ::LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	CMyTest test(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	return test.run();
}

bool CMyTest::InitD3D()
{
	CSystem::InitD3D();
	CFileIOD f(0);
	CTPLLib	tpl(&f, 0, 1, 1);

	try
	{
		if ( tpl.open("..\\data\\tpl\\demo01.tpl", IOD_RDONLY) )
			OVRL_ASSERT_EX(false, GENERAL, "Could not open tpl file");
		Pipeline()->load_library(&tpl);
		Pipeline()->meshes->load_library(&tpl, 
			"*", USAGE_WRITEONLY|OVRL_VB_CONTAINS_LOCAL);
		tpl.close();
	}
	catch ( openvrl::CException& e )
	{
		MessageBox(e.Format(), "Error", MB_OK);
		PostQuitMessage(0);
		return 1;
	}

	camera =  new CMyCamera();

	CWorldSector* sector = new CWorldSector();
	CMyMesh *mesh0 = new CMyMesh();
//	CMyMesh *mesh1 = new CMyMesh();

	World()->AddSector(sector);
	sector->Add(mesh0); mesh0->l = C3DVector(1000,.01,1000);mesh0->pos = C3DVector(0,-2,0); mesh0->m = 1;mesh0->s = false;
//	sector->Add(mesh1); mesh1->l = C3DVector(1,1,1);mesh1->pos = C3DVector(-2,-2.1,-2); mesh1->m = 1;mesh1->s = false;

	for ( int i=0;i<10;i++ )
	{
		CMyMesh *m;
		m = new CMyMesh();
		m->pos = C3DVector((rand()/(real)RAND_MAX)*50-25, 3,(rand()/(real)RAND_MAX)*50-25);
		m->w = C3DVector((rand()/(real)RAND_MAX)*5-2.5, (rand()/(real)RAND_MAX)*5-2.5,(rand()/(real)RAND_MAX)*5-2.5);
//		m->l = C3DVector((rand()/(real)RAND_MAX)*2+.1, (rand()/(real)RAND_MAX)*2+.1,(rand()/(real)RAND_MAX)*2+.1);
		sector->Add(m);
		m->a = true;
	}

	sector->Add(camera);

	return false;
}

bool CMyTest::ReleaseD3D()
{
	return CSystem::ReleaseD3D();
}

bool CMyTest::FrameCalculate()
{
	return CSystem::FrameCalculate();
}


