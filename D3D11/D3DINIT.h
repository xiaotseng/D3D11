#pragma once
#include <d3d11.h>
class D3DINIT//静态类
{
private:
	ID3D11Device* Device;
	ID3D11DeviceContext* DeviceContent;
	IDXGISwapChain *pSwapChain;
	D3DINIT():Device(nullptr), DeviceContent(nullptr){}
	~D3DINIT();
public:
	static D3DINIT& getSingleton();
	bool initD3D(HWND);
	
};

