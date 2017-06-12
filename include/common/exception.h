/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/common/exception.h,v $
 * $Implementation: $
 * $Revision: 1.4 $
 * $Author: foxis $
 * $Date: 2005/07/14 12:59:56 $
 * $Description: copied from NeuralNet project $
 *
 * $Log: exception.h,v $
 * Revision 1.4  2005/07/14 12:59:56  foxis
 * demo bugfix
 * sln bugfix
 *
 * Revision 1.3  2005/02/03 11:24:24  foxis
 * added log header everywhere
 *
 *
 */

#if !defined(AFX_NNEXCEPTION_H__D0CBD3B3_2890_462C_9C7E_CF740417B09C__INCLUDED_)
#define AFX_NNEXCEPTION_H__D0CBD3B3_2890_462C_9C7E_CF740417B09C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "types.h"
#include "exception.h"

#include <stdio.h>
#include <string.h>

namespace openvrl {

class OVRLIBAPI CException  
{
public:
	enum ExceptionType 
	{ 
		NO = 0, 
		PANIC, 
		FATAL, 
		BOUNDARY,
		MEMORY,
		GENERAL,
		ZERO_SIZE,
		INITIALIZED,
		NOTINITIALIZED,
		NOTIMPLEMENTED,
		WRONGTYPES,
		WRONGHEADER,
		FILEERROR,
		SERIALIZEERROR,
		NULLPOINTER,
		WRONGSIZES,
		DIVBYZERO
	} ;

private:

	ExceptionType m_Exception;
	static CHAR *s_Errors[];
	CHAR* m_Message;
	CHAR* m_Formatted;
	CHAR* m_File;
	int	  m_LineNumber;

public:
	CException();
	CException(ExceptionType type, const CHAR* Message, const CHAR* File, int lineNumber);
	CException(const CException& t)
	{
		*this = t;
	}
	virtual ~CException();


	CException& operator =(const CException& t)
	{
		m_Exception = t.Exception();
		m_Message = t.Message();
		m_File = t.File();
		m_Formatted= t.Formatted();
		m_LineNumber = t.LineNumber();
		return *this;
	}


	CHAR* Format(CHAR* str, size_t cb);
	CHAR* Format();
	void Process() const;

	// * Returns exception
	ExceptionType Exception() const { return m_Exception; }
	CHAR* Message() const { return m_Message; }
	CHAR* File() const { return m_File; }
	int LineNumber() const { return m_LineNumber; }
	CHAR* Formatted() const { return m_Formatted; }

	//
	static void exception_assert(bool val, ExceptionType type, const CHAR*Message="", const CHAR* File="", int LineNumber=-1)
	{
		if ( val ) throw CException(type, Message, File, LineNumber);
	}

	//
	static void exception_assert(int i, int min, int max, const CHAR* Message="", const CHAR* File="", int LineNumber=-1)
	{
		if ( i<min || i>=max )
		{
			CHAR *msg;
			msg = new CHAR[strlen(Message)+128];
			snprintf(msg,strlen(Message)+128,"Signed boundary check failed: %i < %i <= %i\n%s", min, i, max, Message);
			exception_assert( 1, BOUNDARY, msg, File, LineNumber);
		}
	}
	//static void BOUNDARY_ASSERT(unsigned int i, unsigned int min, unsigned int max, const CHAR* Message="", const CHAR* File="", int LineNumber=-1)
	//{
	//	if ( i<min || i>=max )
	//	{
	//		CHAR *msg;
	//		msg = new CHAR[strlen(Message)+128];
	//		sprintf(msg,"Unsigned boundary check failed: %u < %u <= %u\n%s", min, i, max, Message);
	//		NN_ASSERT( 1, BOUNDARY, msg, File, LineNumber);
	//	}
	//}
};

};

#endif // !defined(AFX_NNEXCEPTION_H__D0CBD3B3_2890_462C_9C7E_CF740417B09C__INCLUDED_)
