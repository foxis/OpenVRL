#include "common/exception.h"

namespace openvrl
{

CHAR* CException::s_Errors[] = 
{
	 "Dummy exception",
	 "!PANIC!: There was an error that can lead to the corruption of data.\nShutting down the program is highly recommended",
	 "!FATAL!: There was a fatal exception. Program will now quit...",
	 "Boundary check failed.",
	 "Memory error(possibly not enough memory)",
	 "Assertion failed",
	 "Array of size zero.",
	 "Cannot perform action: object is already initialized!",
	 "Cannot perform action: object is not initialized!",
	 "Operation is not implemented!",
	 "Wrong source and destination types!",
	 "Wrong header (probably corrupt)",
	 "File io error",
	 "Serialisation error",
	 "Trying to access a null pointer",
	 "Wrong source and destination sizes",
	 "Divide By Zero!",
	 "RESERVED0",
	 "RESERVED1",
	 "RESERVED2",
	 "RESERVED3",
	 "RESERVED4",
	 "RESERVED5",
	 "RESERVED6",
	 "RESERVED7"
};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CException::CException()
{
	m_Exception = NO;
	m_Formatted = 0;
}

CException::CException(CException::ExceptionType type, const CHAR* Message, const CHAR* File, INT lineNumber)
{
	m_Exception = type;
	m_Message = const_cast<CHAR*>(Message);
	m_File = const_cast<CHAR*>(File);
	m_LineNumber = lineNumber;
	m_Formatted = 0;
}

CException::~CException()
{
	if ( m_Formatted ) delete m_Formatted;
}


CHAR* CException::Format()
{
	if ( m_Exception == MEMORY )  
		return "Memory error!";
	else if ( m_Formatted==0 ) 
	{
		CHAR *excpt = s_Errors[INT(m_Exception-NO)];
		size_t cb;
		cb = (size_t)(strlen(m_Message)+strlen(m_File)+strlen(excpt)+strlen("\n\n\nException in file: \nAt line number: ---Exception: ") + 255);
		OVRL_NEW_EX(m_Formatted, CHAR,(INT)(cb*1.1));
		sprintf(m_Formatted, "Exception: %s\n%s\n\nException in file: %s\nAt line number: %i", excpt, m_Message, m_File, m_LineNumber);
	}
	return m_Formatted;
}
CHAR* CException::Format(CHAR* str, size_t cb)
{
	if ( str==0 ) return str;

	if ( m_Exception == MEMORY )  
		strncpy(str, "Memory error!", cb);
	else if ( m_Formatted==0 ) 
	{
		CHAR *excpt = s_Errors[INT(m_Exception-NO)];
		snprintf(str, cb, "Exception: %s\n%s\n\nException in file: %s\nAt line number: %i", excpt, m_Message, m_File, m_LineNumber);
	}
	return str;
}

void CException::Process() const
{
}

};
