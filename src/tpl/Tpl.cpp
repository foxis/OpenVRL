#include <stdlib.h>
#include <string.h>

#include <tpllib/tpl.hpp>

namespace openvrl {

TPL_HDR TPL_DEFAULT_HEADER = {
        TPL_VERSION,
        TPL_SIGNATURE,
        "",
        0, 0,
        0,
        0,
        0,
        0,
        0,
        {0,},
        sizeof(TPL_HDR),
        sizeof(TPL_HDR),
        sizeof(TPL_HDR),
        sizeof(TPL_HDR),
        sizeof(TPL_HDR),
        {0,}
};

/* c-tor */
CTPLLib::CTPLLib(IIODevice* h, const TPL_CHAR* nm, TPL_WORD _UID, TPL_WORD _GID)
{
		TPL_ASSERT(!header_ctor(nm, TPL_VERSION, _UID, _GID));

#if defined(TPL_SUPPORTED_MATERIALS)
		TPL_ASSERT(!material_ctor());
#endif

#if defined(TPL_SUPPORTED_TEXTURES)
		TPL_ASSERT(!texture_ctor());
#endif

#if defined(TPL_SUPPORTED_LIGHTS)
		TPL_ASSERT(!light_ctor());
#endif

#if defined(TPL_SUPPORTED_CAMERAS)
		TPL_ASSERT(!camera_ctor());
#endif

#if defined(TPL_SUPPORTED_RAW_MESHES)
		TPL_ASSERT(!rawmesh_ctor());
#endif

        modified = true;
        devio = h;
        fname = 0;
        rights = 0;
        styles = 0;
}

/* d-tor */
CTPLLib::~CTPLLib()
{
        close();
		header_dtor();
}

TPL_DWORD CTPLLib::dllTPLLib_Version()
{
	return TPL_VERSION;
}

TPL_DWORD CTPLLib::dllTPLLib_Description(char* str, TPL_DWORD max_cb)
{
	char tmp[1024];
	sprintf(tmp, 
		"Library Name:\tTPLLib\n"
		"Library Version:\t%s\n"
		"Library Description:\t%s\n\n"
		"Copyright %s\n"
		"Author:\t\t%s\n"
		"Release Date:\t%s\n"
		"Build Date:\t%s\n"
		"Port OS:\t\t%s\n"
		"Ported by:\t%s\n\n"
		"Contacts:\t%s\n",
		TPL_VERSION_STR,
		"Templates Library File Format Library",
		"(c) 2001-2002, Andrius Mikonis a.k.a. FoxiE",
		"Andrius Mikonis a.k.a. FoxiE",
		TPL_RELEASE_DATE,
		TPL_LAST_BUILD_DATE,
		TPL_OS,
		TPL_PORTED_BY,
"Andrius a.k.a. FoxiE\nemail: vienas@delfi.lt\nsmail: Kapsø 36-31 Vilnius LT2038, Lithuania\n"
"home#: (+37026)695451\nmob.#: (+370)69993651\n"
	);
	strncpy(str, tmp, max_cb);
	return strlen(str);
}

/* generic functions */
int CTPLLib::open(const TPL_CHAR* fname, TPL_WORD rghts)
{
	TPL_ASSERT(fname);
	TPL_ASSERT(devio);
	if ( opened() ) return 1;
	if ( devio->open(fname, rghts) ) return 1;
	if ( header_read() ) return 1;

	this->fname = new TPL_CHAR[strlen(fname)+1];
	TPL_ASSERT(this->fname);
	strcpy(this->fname, fname);
	modified = false;
	rights = rghts;

#if defined(TPL_SUPPORTED_MATERIALS)
	TPL_ASSERT(!read_materials());
#endif
#if defined(TPL_SUPPORTED_LIGHTS)
	TPL_ASSERT(!read_lights());
#endif
#if defined(TPL_SUPPORTED_CAMERAS)
	TPL_ASSERT(!read_cameras());
#endif
#if defined(TPL_SUPPORTED_TEXTURES)
	TPL_ASSERT(!read_textures());
#endif
#if defined(TPL_SUPPORTED_RAW_MESHES)
	TPL_ASSERT(!read_rawmesh());
#endif
	devio->close();

	return 0;
}

int CTPLLib::create(const TPL_CHAR* fname, TPL_WORD stls, TPL_WORD rghts)
{
	TPL_ASSERT(devio);
	TPL_ASSERT(fname);

	if ( opened() ) return 1;
	if ( devio->create(fname, rghts) ) return 1;
	if ( header_write()<sizeof(TPL_HDR) ) return 1;

	this->fname = new TPL_CHAR[strlen(fname)+1];
	TPL_ASSERT(this->fname);
	strcpy(this->fname, fname);
	modified = false;
	rights = rghts;
	devio->close();
        
	return 0;
}

int CTPLLib::create(const TPL_CHAR* fname, const TPL_HDR& hdr, TPL_WORD styles, TPL_WORD rghts)
{
	TPL_ASSERT(devio);
	TPL_ASSERT(fname);

	if ( opened() ) return 1;
	if ( devio->open(fname, rghts) ) return 1;
	if ( header_write(hdr)<sizeof(TPL_HDR) ) return 1;

	this->fname = new TPL_CHAR[strlen(fname)+1];
	TPL_ASSERT(this->fname);
	strcpy(this->fname, fname);
	modified = false;
	rights = rghts;
	devio->close();
        
	return 0;
}

int CTPLLib::close()
{
	if ( !opened() ) return 1;
	if ( devio==0 ) return 1;

	TPL_ASSERT(fname);

	flush();
	delete[] fname;
	fname = 0;
	rights = 0;
#if defined(TPL_SUPPORTED_MATERIALS)
	TPL_ASSERT(!material_dtor());
#endif

#if defined(TPL_SUPPORTED_TEXTURES)
	TPL_ASSERT(!texture_dtor());
#endif

#if defined(TPL_SUPPORTED_LIGHTS)
	TPL_ASSERT(!light_dtor());
#endif

#if defined(TPL_SUPPORTED_CAMERAS)
	TPL_ASSERT(!camera_dtor());
#endif

#if defined(TPL_SUPPORTED_RAW_MESHES)
	TPL_ASSERT(!rawmesh_dtor());
#endif

	return 0;
}

int CTPLLib::flush()
{
	ulong offs = 0;
	if ( !opened() ) return 1;
	if ( !modified ) return 0;

	TPL_ASSERT(devio);
	TPL_ASSERT(fname);
	if ( devio->open(fname, rights|IOD_TRUNC) ) return 1;

	TPL_ASSERT(offs = header_write());
#if defined(TPL_SUPPORTED_MATERIALS)
	TPL_ASSERT(offs += write_materials(offs));
#endif
#if defined(TPL_SUPPORTED_LIGHTS)
	TPL_ASSERT(offs += write_lights(offs));
#endif
#if defined(TPL_SUPPORTED_CAMERAS)
	TPL_ASSERT(offs += write_cameras(offs));
#endif
#if defined(TPL_SUPPORTED_TEXTURES)
	TPL_ASSERT(offs += write_textures(offs));
#endif
#if defined(TPL_SUPPORTED_RAW_MESHES)
	TPL_ASSERT(offs += write_rawmesh(offs));
#endif
	TPL_ASSERT(header_write());
	modified = false;
	devio->close();

	return 0;
}


}