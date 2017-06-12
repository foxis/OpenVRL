#include "common/string.h"

namespace openvrl {

CString::CString()
{
    m_string = 0;
}

CString::CString(const CString& v)
{
        m_string = 0;
        (*this) = v;
}

CString::CString(const CHAR* str)
{
	if ( !OVRL_ISSTREMPTY(str) )
	{
		::size_t cb= strlen(str)+1;
		m_string = new CHAR[cb];
        //OVRL_NEW_EX(m_string,CHAR,cb);
        strcpy(m_string, str);
	}
	else
		m_string = 0;
}

CString::~CString()
{
        OVRL_DELETE(m_string);
}

CString& CString::operator=(const CString& a)
{
        OVRL_DELETE(m_string);
		if ( !a.is_empty() )
		{
			OVRL_NEW_EX(m_string,CHAR,a.length()+1);
			strcpy(m_string,a.get_cstr());
		}
		else
			m_string = 0;
        return *this;
}

index_t CString::find(const CString&)
{
        return -1;
}

index_t CString::find_ch(CHAR ch)
{
        index_t i =0;
        while ( m_string && m_string[i] && m_string[i]==ch ) i++ ;
        return i;
}

CString CString::select(index_t i, index_t j)
{
        CHAR *str;
        CString* tmp;
        index_t k,l;

		if ( !m_string ) return CString();

        if ( i>j ) {
           OVRL_NEW_EX(str,CHAR,i-j);
           for ( k=j,l=0;k<i;k++,l++ )
               str[l] = m_string[k];
           str[l]='\0';
           tmp = new CString(str);
        } else {
           OVRL_NEW_EX(str,CHAR,j-i);
           for ( k=i,l=0;k<j;k++,l++ )
               str[l] = m_string[k];
           str[l]='\0';
           tmp = new CString(str);
        }
        OVRL_DELETE(str);
        return *tmp;
}

void CString::clear()
{
        OVRL_DELETE(m_string);
}

void CString::feed_char(CHAR ch, num_t num)
{
	ulong i;
    OVRL_DELETE(m_string);
    OVRL_NEW_EX(m_string,CHAR,num+1);
	for ( i=0;i<num;i++ ) m_string[i] = ch; 
	m_string[i]=0;
}

}