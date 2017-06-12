#include "system/OVRLLog.h"

namespace openvrl {

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CLog::CLog(const CString& path)
{
	m_path = path;
}

CLog::CLog(const CString& str, const CString& path)
{
	m_path = path;
	write(str);
	write("\n");
}

CLog::~CLog()
{
}

}