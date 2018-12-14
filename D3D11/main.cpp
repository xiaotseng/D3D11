#include <Windows.h>
#include <d3d11.h>
#include <d3dcommon.h>
#include <comutil.h>
#include "D3DINIT.h"
#include <WinUser.h>
#include <string>
using namespace std;
#if  defined(DEBUG)||defined(_DEBUG)
#define createDeviceFlags  D3D11_CREATE_DEVICE_DEBUG
#else 
#define createDeviceFlags  D3D11_CREATE_DEVICE_SINGLETHREADED
#endif
HWND		g_hWnd(NULL);

wstring		g_clsName(L"d3d11");
wstring		g_wndTitle(L"1_D3DInit");
const char* className = "test";
UINT		g_winWidth(640);
UINT		g_winHeight(480);
HINSTANCE g_hInstance(NULL);
int Run();
BOOL InitWin32();
LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	g_hInstance = hInstance;
	InitWin32();
	//Run();
	D3DINIT::getSingleton();
	
	
	return 0;
}
BOOL InitWin32()
{
	WNDCLASS wndcls;
	wndcls.cbClsExtra = 0;
	wndcls.cbWndExtra = 0;
	wndcls.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wndcls.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndcls.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndcls.hInstance = g_hInstance;
	wndcls.lpfnWndProc = WinProc;
	wndcls.lpszClassName = className;
	wndcls.lpszMenuName = NULL;
	wndcls.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClass(&wndcls))
	{
		MessageBox(NULL, "Register window failed!", "error", MB_OK);
		return FALSE;
	}
	//CreateWindow()
		g_hWnd = CreateWindow(
		className,
		className,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		g_winWidth, g_winHeight,
		NULL,
		NULL,
		g_hInstance,
		NULL);
	if (!g_hWnd)
	{
		MessageBox(NULL, "Create window failed!", "error", MB_OK);
		return FALSE;
	}

	ShowWindow(g_hWnd, SW_SHOW);
	UpdateWindow(g_hWnd);

	return TRUE;
}

LRESULT WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return LRESULT();
}

int Run()
{
	MSG msg = { 0 };
	//主消息循环，也是游戏当中的主循环
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//在这里做该做的事:渲染
		
		}
	}


	return msg.wParam;
}