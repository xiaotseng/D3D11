#define UNICODE 
#include "FrameWork.h"

static LRESULT  CALLBACK WinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	default:
		//��������ȱʡ�Ĵ��ڹ�����ΪӦ�ó���û�д�����κδ�����Ϣ�ṩȱʡ�Ĵ����ú���ȷ��ÿһ����Ϣ�õ�����
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
		MessageBox(NULL, L"ע��ʧ��!", L"����", MB_OK);
		return FALSE;
	}
	int nStyle = WS_OVERLAPPED | WS_SYSMENU | WS_VISIBLE | WS_CAPTION | WS_MINIMIZEBOX;
	m_hWnd = CreateWindowEx(WS_EX_APPWINDOW, className, className, nStyle, 200, 200, winWidth, winHeight, NULL, NULL, hInstance, NULL);
	if (!m_hWnd)
	{/*
		MessageBox(NULL, L"��������ʧ��!", L"����", MB_OK);
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
