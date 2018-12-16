#define UNICODE 
#include <Windows.h>
#include <iostream>
#include <d3d11.h>
#include <d3dcommon.h>
#include <comutil.h>
#include "D3DINIT.h"
#include <WinUser.h>
#include <string>
#include "FrameWork.h"
using namespace std;
static void Loop();
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	
	FrameWork* f = new FrameWork();
	FrameWork* e= new FrameWork();
	if(!f->Create_Window(hInstance, L"我的第一个窗口", 800, 800)) return -1;
	if(!e->Create_Window(hInstance, L"我的第二个窗口", 800, 800)) return -1;
	if(!D3DINIT::getSingleton().initD3D(f->getWnd())) return -1;
	Loop();
	delete f;
	delete e;
	return 0;
}

static void Loop()
{
	static MSG msg = { 0 };
	//主消息循环，也是游戏当中的主循环
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))//检查线程消息队列，并将该消息放于指定的结构
		{
			TranslateMessage(&msg);//将键盘消息转化
			DispatchMessage(&msg);//将消息传给窗体函数去处理
		}
		else
		{
			//在这里做该做的事:渲染
		}
	}
}