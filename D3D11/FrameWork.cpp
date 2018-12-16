#define UNICODE 
#include "FrameWork.h"

static LRESULT  CALLBACK WinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	default:
		//函数调用缺省的窗口过程来为应用程序没有处理的任何窗口消息提供缺省的处理。该函数确保每一个消息得到处理。
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	}
	return 0;
}

HWND FrameWork::getWnd() const
{
	return m_hWnd;
}

bool FrameWork::Create_Window(HINSTANCE hInstance, LPCTSTR  className,INT winWidth,INT winHeight)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = m_WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIconSm = wc.hIcon;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = className;
	wc.cbSize = sizeof(WNDCLASSEX);
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"注册失败!", L"错误", MB_OK);
		return FALSE;
	}
	int nStyle = WS_OVERLAPPED | WS_SYSMENU | WS_VISIBLE | WS_CAPTION | WS_MINIMIZEBOX;
	m_hWnd = CreateWindowEx(WS_EX_APPWINDOW, className, className, nStyle, 200, 200, winWidth, winHeight, NULL, NULL, hInstance, NULL);
	if (!m_hWnd)
	{/*
		MessageBox(NULL, L"创建窗口失败!", L"错误", MB_OK);
		return FALSE;
		*/
	}
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);
	return TRUE;
}

FrameWork::FrameWork():m_WinProc(WinProc),m_hWnd(NULL)
{
	
}


FrameWork::~FrameWork()
{
	
}
