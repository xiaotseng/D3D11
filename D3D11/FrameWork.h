#pragma once
#include <Windows.h>
class FrameWork
{
	LRESULT (CALLBACK*m_WinProc) (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	HWND		m_hWnd;
	
public:
	HWND getWnd()const;
	bool Create_Window(HINSTANCE hInstance, LPCTSTR  className, INT winWidth, INT winHeight);
	FrameWork();
	~FrameWork();
};

