/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/system/ovrlwindow.h,v $
 * $Implementation: $
 * $Revision: 1.3 $
 * $Author: foxis $
 * $Date: 2005/07/14 12:59:56 $
 * $Description:  $
 *
 * $Log: ovrlwindow.h,v $
 * Revision 1.3  2005/07/14 12:59:56  foxis
 * demo bugfix
 * sln bugfix
 *
 * Revision 1.2  2005/02/03 11:24:24  foxis
 * added log header everywhere
 *
 *
 */

#if !defined(__ovrl_OVRLWINDOW_HPP)
#define __ovrl_OVRLWINDOW_HPP

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER				// Allow use of features specific to Windows 95 and Windows NT 4 or later.
#define WINVER 0x0400		// Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
#endif

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows NT 4 or later.
#define _WIN32_WINNT 0x0400		// Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
#endif						

#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE			// Allow use of features specific to IE 4.0 or later.
#define _WIN32_IE 0x0400	// Change this to the appropriate value to target IE 5.0 or later.
#endif

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

#include "common/all.h"
#include "common/string.h"

namespace openvrl {


LRESULT CALLBACK ovrlDefWndProc( HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam );


class OVRLIBAPI CWindow 
{
	HINSTANCE m_hInstance;
	HINSTANCE m_hPrevInstance;
	CString m_szCmdLine;
	int m_nCmdShow;
	HWND	  m_hWnd;
	CString m_szWindowTitle;
	CString m_szWindowClass;
	uint m_X;
	uint m_Y;
	uint m_Width;
	uint m_Height;

public:
	CWindow();
	CWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance,
        int nCmdShow, uint X, uint Y, uint Width, uint Height);
	CWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance,
        int nCmdShow, const CString& szWinTitle, 
		const CString& szWinClass,
		uint X, uint Y, uint Width, uint Height);
	virtual ~CWindow();


	virtual CString get_window_title() const
	{
		return "A Window";
	}
	virtual CString get_window_class() const
	{
		return "SIMPLE_OVRL_WINDOW_CLASS";
	}
	virtual DWORD get_window_style() const { return WS_OVERLAPPEDWINDOW; }
	virtual DWORD get_window_style_ex() const { return 0; }

	/** */
	virtual int run(bool nOwnLoop=true);

	/**
     */
	virtual HWND hWindow() const { return m_hWnd; }
	virtual HWND hWnd() const { return m_hWnd; }
	virtual HINSTANCE hInstance() const { return m_hInstance; }

	virtual int DestroyWindow()
	{
		return ::DestroyWindow(m_hWnd);
	}
	virtual int Destroy()
	{
		return ::DestroyWindow(m_hWnd);
	}
	virtual int CloseWindow()
	{
		return ::CloseWindow(m_hWnd);
	}
	virtual int Close()
	{
		return ::CloseWindow(m_hWnd);
	}
	virtual HDC BeginPaint(PAINTSTRUCT* ps)
	{
		return ::BeginPaint(m_hWnd, ps);
	}
	virtual int EndPaint(PAINTSTRUCT* ps)
	{
		return ::EndPaint(m_hWnd, ps);
	}
	virtual int GetClientRect(RECT* rc)
	{
		return ::GetClientRect(m_hWnd, rc);
	}

	virtual int ValidateRect(const RECT* lpRect)
	{
		return ::ValidateRect(m_hWnd, lpRect);
	}

	virtual int MessageBox(const CString& szText, 
		const CString& szTitle, uint nMB)
	{
		return ::MessageBox(m_hWnd, szText(), szTitle(), nMB);
	}
	virtual HICON LoadIcon(UINT id)
	{
		return ::LoadIcon(m_hInstance, (LPCTSTR)id);
	}
	virtual int LoadString(UINT id, CHAR* szStr, ulong n)
	{
		return ::LoadString(m_hInstance, id, szStr, n);
	}

protected:
	/** */
	virtual bool LoadStrings();
	virtual bool RegisterClass(WNDCLASS& WndClass);
	virtual bool RegisterClass(WNDCLASSEX& WndClass);
	virtual bool InitInstance();
	virtual LRESULT WndProc(UINT, WPARAM, LPARAM);

	friend LRESULT CALLBACK ovrlDefWndProc(HWND, UINT, WPARAM, LPARAM);
};


};
#endif /* !defined(__ovrl_OVRLWINDOW_HPP) */
