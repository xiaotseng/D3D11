#include <Windows.h>
#include "D3DINIT.h"
#include <comutil.h>
#include <dxgi.h>
#include <assert.h>
#if  defined(DEBUG)||defined(_DEBUG)
#define createDeviceFlags  D3D11_CREATE_DEVICE_DEBUG
#else 
#define createDeviceFlags  D3D11_CREATE_DEVICE_SINGLETHREADED
#endif

D3DINIT & D3DINIT::getSingleton()
{
	static D3DINIT singleton;
	return singleton;
}

bool  D3DINIT::initD3D(HWND hw)
{
	
	HRESULT  h;
	const int levelNum = 4;
	//可选等级
	D3D_FEATURE_LEVEL levels[levelNum] = {
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_9_1
	};
	D3D_FEATURE_LEVEL FeatrueLevel;
	h = D3D11CreateDevice(
		nullptr,//哪一个显卡，默认显卡
		D3D_DRIVER_TYPE_HARDWARE,//驱动类型，硬件驱动
		nullptr,//软驱动，不需要
		createDeviceFlags,//用以激活调试层。当指定调试标志值后，Direct3D会向VC++的输出窗口发送调试信息
		levels,//特征等级
		levelNum,//可选等级数量 
		D3D11_SDK_VERSION,//SDK版本
		&Device,//设备指针
		&FeatrueLevel,//最终选择的等级
		&DeviceContent//上下文指针
	);
	if (FAILED(h))
	{
		MessageBox(nullptr, "D3D初始化失败", "失败", 0);
		return false;
	}
	else if (FeatrueLevel < D3D_FEATURE_LEVEL_11_0)
	{
		MessageBox(nullptr, "D3D版本太低", "警告", 0);
		return false;
	}
	else
	{
		const char* c = "D3D初始化成功";
		const char* t = "成功";
		MessageBox(nullptr, c, t, 0);
	}
	//是否支持采样
	UINT  m4xMsaaQuality;
	HRESULT mEnable4xMsaa = Device->CheckMultisampleQualityLevels(
		DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m4xMsaaQuality);
	assert(m4xMsaaQuality > 0);
	////////
	//交换链描述结构
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(DXGI_SWAP_CHAIN_DESC));
	DXGI_MODE_DESC ModeDes;
	ZeroMemory(&ModeDes, sizeof(DXGI_MODE_DESC));
	ModeDes.Width = 800;
	ModeDes.Height = 600;
	ModeDes.RefreshRate.Numerator = 60;
	ModeDes.RefreshRate.Denominator = 1;
	ModeDes.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	ModeDes.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	ModeDes.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc = ModeDes;

	if (mEnable4xMsaa)
	{
		sd.SampleDesc.Count = 4;
		sd.SampleDesc.Quality = m4xMsaaQuality - 1;
	}
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hw;
	sd.Windowed = true;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	IDXGIDevice *  dxgiDevice = nullptr;
	Device->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);
	IDXGIAdapter* dxgiAdapter = nullptr;

	//pSwapChain
	///////////创建交换链
	//h = IDXGIFactory::CreateSwapChain(Device, &sd, &pSwapChain);
	return true;
}

D3DINIT::~D3DINIT()
{
	if (Device) Device->Release();
	if (DeviceContent) DeviceContent->Release();
}
