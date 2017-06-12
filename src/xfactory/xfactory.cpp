#include "xfactory/xfactory.h"
#include "iosystem/fileiodev.h"

namespace openvrl {


CxFactory::CxFactory(CSystem* sys)
{
	OVRL_ASSERT(sys);
	m_System = sys;
}

CxFactory::CxFactory(CSystem* sys, const CxFactory& xf)
{
	OVRL_ASSERT(sys);
	m_System = sys;
}

CxFactory::~CxFactory()
{
	Cleanup();
}

bool CxFactory::Initialize()
{
	materials = create_MaterialList();
	lights = create_LightList();
	cameras = create_CameraList();
	textures = create_TextureList();
	vertex_buffers = create_VertexBufferList();
	index_buffers = create_IndexBufferList();
	vertex_shaders = create_VertexShaderList();
	meshes = create_MeshList();
	return false;
}

bool CxFactory::Cleanup()
{
	if ( meshes )
	{
		printf("xfactory: meshes");
		delete_MeshList(meshes);
		meshes = 0;
	}
	if ( lights )
	{
		printf("xfactory: lights");
		delete_LightList(lights);
		lights = 0;
	}
	if ( cameras )
	{
		printf("xfactory: cameras");
		delete_CameraList(cameras);
		cameras = 0;
	}

	if ( materials )
	{
		printf("xfactory: materials");
		delete_MaterialList(materials);
		materials = 0;
	}
	if ( textures )
	{
		printf("xfactory: textures");
		delete_TextureList(textures);
		textures = 0;
	}
	if ( vertex_shaders )
	{
		printf("xfactory: vs");
		delete_VertexShaderList(vertex_shaders);
		vertex_shaders = 0;
	}
	if ( vertex_buffers )
	{
		printf("xfactory: vb");
		delete_VertexBufferList(vertex_buffers);
		vertex_buffers = 0;
	}
	if ( index_buffers )
	{
		printf("xfactory: ib\b");
		delete_IndexBufferList(index_buffers);
		printf("xfactory: ib =0\b");
		index_buffers = 0;
		printf("xfactory: ib done\b");
	}
	printf("xfactory: done");
	return false;
}

int CxFactory::load_library(const CString& path, const CString& pattern, DWORD flags)
{
	CFileIOD f(0);
	CTPLLib	tpl(&f, 0, 1, 1);
	int rc;

	if ( tpl.open(path.c_str(), IOD_RDWR) )
	{
			ovrl_warning("xFactory: Couldn't open template...");
			return 1;
	}

	rc = load_library(&tpl, pattern, flags);
	tpl.close();
	return rc;
}

int CxFactory::load_library(CTPLLib* tpl, const CString& pattern, DWORD flags)
{
	textures->load_library(tpl, pattern, flags);
	materials->load_library(tpl, pattern, flags);
	lights->load_library(tpl, pattern, flags);
	cameras->load_library(tpl, pattern, flags);
	vertex_shaders->load_library(tpl, pattern, flags);
	return 0;
}

int CxFactory::save_library(const CString& path)
{
	CFileIOD f(0);
	CTPLLib	tpl(&f, "Test TPL file", 1, 1);
	int rc;

	if ( tpl.open(path.c_str(), IOD_RDWR) )
	{
			ovrl_warning("xFactory: Couldn't open template...");
			return 1;
	}

	rc = save_library(&tpl);
	tpl.modified = true;
	tpl.close();
	return rc;
	return 0;
}

int CxFactory::save_library(CTPLLib* tpl)
{
	materials->save_library(tpl);
	lights->save_library(tpl);
	cameras->save_library(tpl);
	textures->save_library(tpl);
//	vertex_buffers->save_library(tpl);
//	index_buffers->save_library(tpl);
	vertex_shaders->save_library(tpl);
	return 0;
}

}