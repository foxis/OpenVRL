/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/xfactory/xfactory.h,v $
 * $Implementation: /src/xfactroy/xfactory.cc $
 * $Revision: 1.1.1.1 $
 * $Author: foxis $
 * $Date: 2005/02/02 15:39:23 $
 * $Description: xFactory class $
 *
 * $Log: xfactory.h,v $
 * Revision 1.1.1.1  2005/02/02 15:39:23  foxis
 * sources import
 *
 * Revision 0.1  20020117  20:30:00 FoxiE
 *  :)
 *
 */



#if !defined(___XFACTORY_HPP)
#define ___XFACTORY_HPP

#include "common/all.h"
#include "xfactory/xfmaterial.h"
#include "xfactory/xfcamera.h"
#include "xfactory/xflight.h"
#include "xfactory/xfvertexbuf.h"
#include "xfactory/xfindexbuf.h"
#include "xfactory/xftexture.h"
#include "xfactory/xfmesh.h"
#include "xfactory/xfVertexShader.h"

namespace openvrl {

class OVRLIBAPI CSystem;


/** 
 * CxFactory class
 *
 */
class OVRLIBAPI CxFactory 
{
protected:
	CSystem		*m_System;

private:
	virtual CxfMaterialList* create_MaterialList() { return new CxfMaterialList(this); } 
	virtual void delete_MaterialList(CxfMaterialList* m) { delete m; } 

	virtual CxfLightList* create_LightList() { return new CxfLightList(this); } 
	virtual void delete_LightList(CxfLightList* m) { delete m; } 

	virtual CxfCameraList* create_CameraList() { return new CxfCameraList(this); } 
	virtual void delete_CameraList(CxfCameraList* m) { delete m; } 

	virtual CxfVertexBufferList* create_VertexBufferList() { return new CxfVertexBufferList(this); } 
	virtual void delete_VertexBufferList(CxfVertexBufferList* vb) { delete vb; } 

	virtual CxfIndexBufferList* create_IndexBufferList() { return new CxfIndexBufferList(this); } 
	virtual void delete_IndexBufferList(CxfIndexBufferList* vb) { delete vb; } 

	virtual CxfTextureList* create_TextureList() { return new CxfTextureList(this); } 
	virtual void delete_TextureList(CxfTextureList* vb) { delete vb; } 

	virtual CxfVertexShaderList* create_VertexShaderList() { return new CxfVertexShaderList(this); } 
	virtual void delete_VertexShaderList(CxfVertexShaderList* vb) { delete vb; } 

	virtual CxfMeshList* create_MeshList() { return new CxfMeshList(this); } 
	virtual void delete_MeshList(CxfMeshList* vb) { delete vb; } 

public:
	CxfMaterialList	*materials;
	CxfLightList	*lights;
	CxfCameraList	*cameras;
	CxfTextureList	*textures;
	CxfVertexBufferList	*vertex_buffers;
	CxfIndexBufferList	*index_buffers;
	CxfVertexShaderList	*vertex_shaders;
	CxfMeshList	*meshes;

	CSystem* System() const { return m_System; } 
	CSystem* get_System() const { return m_System; } 

	virtual bool Initialize();
	virtual bool Cleanup();

	virtual int load_library(const CString& path, const CString& pattern="*", DWORD flags=USAGE_WRITEONLY);
	virtual int load_library(CTPLLib* tpl, const CString& pattern="*", DWORD flags=USAGE_WRITEONLY);
	virtual int save_library(const CString& path);
	virtual int save_library(CTPLLib* tpl);

	/**
	 *
	 */
	CxFactory(CSystem* sys);
	CxFactory(CSystem* sys, const CxFactory& xf);
	virtual ~CxFactory();
};

};


#endif /* !defined(___XFACTORY_HPP) */
