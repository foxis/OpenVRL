/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/tpllib/tpl.hpp,v $
 * $Implementation:  $
 * $Revision: 1.2 $
 * $Author: foxis $
 * $Date: 2005/03/04 13:21:16 $
 * $Description: *.tpl library $
 *
 * Revision 0.1  20010919  17:56:12 FoxiE
 * started :)
 *
 */


#if !defined(__tpl_TPL_HPP)
#define __tpl_TPL_HPP

#include <vector>
#include "tpllib/tplconf.h"
#include "tpllib/tpltypes.h"
#include "tpllib/tplcore.h"
#include "iosystem/iodevice.h"
#include "common/log.h"

/* include plugins */
#include "tpllib/pl_hdr.hpp"
#include "tpllib/pl_mtrl.hpp"
#include "tpllib/pl_lght.hpp"
#include "tpllib/pl_cmr.hpp"

namespace openvrl {
/**
 *
 */
class TPL_API CTPLLib /*: public COVRLObject */
{
protected:  /* data */
        IIODevice*      devio;
        TPL_CHAR*           fname;
        TPL_WORD            rights;
        TPL_WORD            styles;

public: /* functions */
        bool            modified;

        CTPLLib(IIODevice* h, const CHAR* name, TPL_WORD UID, TPL_WORD GID);
        ~CTPLLib();

	/* */
	static TPL_DWORD dllTPLLib_Version();
	static TPL_DWORD dllTPLLib_Description(char* str, TPL_DWORD max_cb);

        /* generic functions */
		int opened() const { return fname!=0; }
        virtual int open(const TPL_CHAR* fname, TPL_WORD rights);
        virtual int create(const TPL_CHAR* fname, TPL_WORD styles, TPL_WORD rights);
        virtual int create(const TPL_CHAR* fname, const TPL_HDR& hdr, TPL_WORD styles, TPL_WORD rights);
        virtual int close();
        virtual int flush();

        /* specific functions */
        virtual void set_name(const TPL_CHAR* nm) { strncpy(name, nm, TPL_MAX_NAME_LEN); }
        virtual TPL_CHAR* get_name() { return name; }
		virtual TPL_CHAR* get_fname() { return fname; }

        /**
         *  include template supported data plugins
         */
#define __TPL_INCLUDE_SUPPORT_PLUGINS

#if defined(TPL_SUPPORTED_HEADER)
#include "tpllib/pl_hdr.hpp"
#endif // if defined(TPL_SUPPORTED_HEADER

#if defined(TPL_SUPPORTED_MATERIALS)
#include "tpllib/pl_mtrl.hpp"
#endif // if defined(TPL_SUPPORTED_MATERIALS

#if defined(TPL_SUPPORTED_TEXTURES)
#include "tpllib/pl_txtr.hpp"
#endif // if defined(TPL_SUPPORTED_TEXTURES

#if defined(TPL_SUPPORTED_LIGHTS)
#include "tpllib/pl_lght.hpp"
#endif // if defined(TPL_SUPPORTED_LIGHTS

#if defined(TPL_SUPPORTED_CAMERAS)
#include "tpllib/pl_cmr.hpp"
#endif // if defined(TPL_SUPPORTED_CAMERAS

#if defined(TPL_SUPPORTED_RAW_MESHES)
#include "tpllib/pl_rwmsh.hpp"
#endif // if defined(TPL_SUPPORTED_RAW_MESHES

#undef __TPL_INCLUDE_SUPPORT_PLUGINS

};

};

#endif // if !defined(__TPL_H)
