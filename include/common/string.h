/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/common/string.h,v $
 * $Implementation: /src/ovrlstring.cc $
 * $Revision: 1.3 $
 * $Author: foxis $
 * $Date: 2005/07/14 12:59:56 $
 * $Description: Class for supporting C type strings $
 *
 * $Log: string.h,v $
 * Revision 1.3  2005/07/14 12:59:56  foxis
 * demo bugfix
 * sln bugfix
 *
 * Revision 1.2  2005/07/14 12:14:07  foxis
 * no message
 *
 * Revision 1.1.1.1  2005/02/02 15:39:13  foxis
 * sources import
 *
 * Revision 0.3  20020815  22:05:00 FoxiE
 * operator==(...) turëjo bugà: tikrino null pointerius tuðèiø stringø...
 * operator!=(...) turëjo bugà - gràþindavo true kai str'ai vienodi ir false kai skirësi
 *
 * Revision 0.2  20020105  17:55:10 FoxiE
 *  pervardinau ið 3dlstrng á ovrlm_string, portinau 
 *  klasæ á VC++ 6.
 *
 * Revision 0.1  20010411  22:53:17 FoxiE
 *  :)
 *
 */



#if !defined(__ovrl_OVRLSTRING_H)
#define __ovrl_OVRLSTRING_H

#include "common/types.h"
#include "common/exception.h"
#include "common/classes.h"

namespace openvrl {

#if defined(USE_OWN_STD_CLASSES)
class OVRLIBAPI CString 
{
protected:
           CHAR* m_string;

public:
        CString();
        CString(const CString& v);
        CString(const CHAR* str);
        virtual ~CString();

		virtual int is_empty() const
		{
			return OVRL_ISSTREMPTY(m_string);
		}
        virtual int operator==(const CString& a) const
        {
			return (m_string!=0&&a.get_cstr()!=0)?(strcmp(m_string, a.get_cstr())==0):(m_string==a.get_cstr());
        }
        virtual int operator!=(const CString& a) const
        {
                return !((*this) == a);
        }
        CString& operator=(const CString& a);

        CHAR operator[](DWORD i) const
        {
                return m_string[i];
        }
        CHAR* operator()() const
        {
                return m_string;
        }
        CHAR* operator()(const DWORD i) const
        {
                return m_string+i;
        }
        CString& operator+=(const CString& a)
        {
                CHAR *str;
				OVRL_NEW_EX(str, CHAR, length()+a.length()+1);
                strncpy(str, m_string, length()+a.length()+1);
                strncat(str, a.get_cstr(), length()+a.length()+1);
                OVRL_DELETE(m_string);
                m_string = str;
                return *this;
        }
		CString& operator<<(const CString& a)
		{
			return (*this) += a;
		}
		CString& operator<<(int a)
		{
			char tmp[128];
			snprintf(tmp,128, "%i", a);
			return (*this) += tmp;
		}
		CString& operator<<(ulong a)
		{
			char tmp[128];
			snprintf(tmp, 128, "%lu", a);
			return (*this) += tmp;
		}
		CString& operator<<(CHAR a)
		{
			char tmp[128];
			snprintf(tmp,128, "%c", a);
			return (*this) += tmp;
		}
		CString& operator<<(real a)
		{
			char tmp[128];
			snprintf(tmp,128, "%.20f", a);
			return (*this) += tmp;
		}
		CString& operator<<(const C3DPoint& a)
		{
			char tmp[128];
			snprintf(tmp,128, "{%.f,%f,%f}", a.x(), a.y(), a.z());
			return (*this) += tmp;
		}
		CString& operator<<(const C2DPoint& a)
		{
			char tmp[128];
			snprintf(tmp, 128, "{%.f,%f}", a.x(), a.y());
			return (*this) += tmp;
		}
		CString& operator<<(const C4DPoint& a)
		{
			char tmp[128];
			snprintf(tmp, 128, "{%.f,%f,%f,%f}", a.x(), a.y(), a.z(), a.w());
			return (*this) += tmp;
		}
		CString& operator<<(const C4x4Matrix& a)
		{
			char tmp[128];
			snprintf(tmp,128, "{%f,%f,%f,%f, %f,%f,%f,%f, %f,%f,%f,%f, %f,%f,%f,%f}", 
				a.data()[0], a.data()[1], a.data()[2], a.data()[3], 
				a.data()[4], a.data()[5], a.data()[6], a.data()[7], 
				a.data()[8], a.data()[9], a.data()[10], a.data()[11], 
				a.data()[12], a.data()[13], a.data()[14], a.data()[15]);
			return (*this) += tmp;
		}
        CString operator+(const CString& a) const
        {
                CString s(*this);
                s+=a;
                return s;
        }
        CHAR* get_cstr() const
        {
                return m_string;
        }
        CHAR* c_str() const
        {
                return m_string;
        }
        CHAR* get_cstr() 
        {
                return m_string;
        }
        CHAR* c_str() 
        {
                return m_string;
        }
        size_t length() const
        {
                return (size_t)strlen(m_string);
        }
        index_t find(const CString&);
        index_t find_ch(CHAR ch);
        CString select(index_t i, index_t j);
        void clear();
		void feed_char(CHAR ch, num_t num);
		void feed_tabs(num_t num)
		{
			feed_char('\t', num);
		}
		void feed_spaces(num_t num)
		{
			feed_char(' ', num);
		}
};
#else
#error defined(USE_OWN_STD_CLASSES) failed!
#endif /* defined(USE_OWN_STD_CLASSES) */

};

#endif /* !defined(__ovrl_OVRLSTRING_HPP) */

