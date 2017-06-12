// OpenVRL_v04_tpl_library.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <openvrl.h>
using namespace openvrl;
#include "./materials.h"
//#include "./lights.h"
#include "./raws.h"

int main(int argc, char* argv[])
{
        CFileIOD m_f(0);
        CTPLLib m_tpl(&m_f, "Default Template Library", 1, 1);
        TPL_MAT m;
		TPL_LIGHT l;
		TPL_CAMERA c;
		TPL_RAW r;

        m_tpl.create("default_library.tpl", 0, IOD_RDWR);


        memset(&m, 0, sizeof m);
        strncpy(m.signature, TPL_MAT_SIG, TPL_MAX_SIG_LEN);
        m.version = TPL_MAT_VERSION;
        memset(&l, 0, sizeof l);
        strncpy(l.signature, TPL_LIGHT_SIG, TPL_MAX_SIG_LEN);
        l.version = TPL_LIGHT_VERSION;
        memset(&c, 0, sizeof c);
        strncpy(c.signature, TPL_CAMERA_SIG, TPL_MAX_SIG_LEN);
        c.version = TPL_LIGHT_VERSION;
        memset(&r, 0, sizeof r);
        strncpy(r.signature, TPL_RAW_SIG, TPL_MAX_SIG_LEN);
        r.version = TPL_RAW_VERSION;

        m.style = 0;
        m.flags = 0;
    m.shiness = 0.0;
        m.strength = 0.0;
        m.self_illumination = 0.0;
        m.opacity = 1.0;
        m.bounce_coeficient = 0.5;
        m.static_friction = 0.04;
        m.sliding_friction = 0.008;
    m.filter.red = RGB_BLACK.r;
    m.filter.green = RGB_BLACK.g;
    m.filter.blue = RGB_BLACK.b;
    m.filter.alpha = RGB_BLACK.a;
    m.refraction.red = RGB_BLACK.r;
    m.refraction.green = RGB_BLACK.g;
    m.refraction.blue = RGB_BLACK.b;
    m.refraction.alpha = RGB_BLACK.a;


	ulong i;
	for ( i=0;i<sizeof(g_colors)/sizeof(g_colors[0]);i++ )
	{
        strcpy(m.name, "def/mat/");
		strcat(m.name, g_colors[i].name);
		printf("generating %s\n", m.name);
        m.ambient.red = g_colors[i].amb.red;
        m.ambient.green = g_colors[i].amb.green;
        m.ambient.blue = g_colors[i].amb.blue;
		m.diffuse.red = g_colors[i].diff.red;
		m.diffuse.green = g_colors[i].diff.green;
		m.diffuse.blue = g_colors[i].diff.blue;
		m.specular.red = g_colors[i].spec.red;
		m.specular.green = g_colors[i].spec.green;
		m.specular.blue = g_colors[i].spec.blue;
        m.ambient.alpha = m.diffuse.alpha = m.specular.alpha = 1;
        m_tpl.material_add(m);
	}

	
	strcpy(l.name, "def/lght/DIRECTIONAL");
	l.style = LIGHT_DIRECTIONAL;
        l.ambient.alpha = l.diffuse.alpha = l.specular.alpha = 1.0f;
        l.ambient.red = 1.0f;
        l.ambient.green = 1.0f;
        l.ambient.blue = 0.98f;
		l.diffuse.red = 1.0f;
		l.diffuse.green = 1.0f;
		l.diffuse.blue = 0.98f;
		l.specular.red = 1.0f;
		l.specular.green = 1.0f;
		l.specular.blue = 0.98f;
	l.cut_off = 10000.0f;
	m_tpl.light_add(l);
	strcpy(l.name, "def/lght/AMBIENT");
	l.style = LIGHT_AMBIENT;
        l.ambient.alpha = l.diffuse.alpha = l.specular.alpha = 1.0f;
        l.ambient.red = 1.0f;
        l.ambient.green = 1.0f;
        l.ambient.blue = 0.98f;
		l.diffuse.red = 1.0f;
		l.diffuse.green = 1.0f;
		l.diffuse.blue = 0.98f;
		l.specular.red = 1.0f;
		l.specular.green = 1.0f;
		l.specular.blue = 0.98f;
	l.cut_off = 0.0f;
	m_tpl.light_add(l);

	strcpy(c.name, "def/camera/48mm");
	c.focus = 48.235291f;
	c.dx = 18.0f; 
	c.dy = 18.0f;
	c.gamma = 1.0f;
	c.whitepoint = 255;
	m_tpl.camera_add(c);

	strcpy(r.name, "def/mesh/STAR");
	r.vertex_size = sizeof(star_vertex);
	r.face_size = sizeof(unsigned short)*3;
	r.verteces = sizeof(g_star_vb)/sizeof(star_vertex);
	r.faces = sizeof(g_star_ib)/(sizeof(unsigned short)*3);
	r.VB_flags = STAR_VB;
	r.IB_flags = STAR_IB;
	m_tpl.rawmesh_add(r, (BYTE*)g_star_vb, (BYTE*)g_star_ib);

	m_tpl.modified = true;
	m_tpl.close();

	return 0;
}
