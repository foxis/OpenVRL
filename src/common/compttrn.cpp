#include "common/pattern.h"

namespace openvrl {

int CPattern::operator==(const CString& a) const
{
	CHAR* p1, *p2;
	p1 = m_string;
	p2 = a.c_str();
	while ( *p1 && *p2 )
	{
		switch ( *p1 )
		{
		case '?': 
			p1++; 
			break;

		case '*': 
			return 1;
			break;

		default: 
			if ( *p1!=*p2 ) 
				return 0;
			p1++;
		}
		p2++;
	}
	return 1;
}

}
