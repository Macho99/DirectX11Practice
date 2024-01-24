#pragma once
class Game
{
public:
	Game();
	virtual ~Game();

public:
	void Init(HWND hwnd);
	void Update();
	void Render();

private:
	HWND _hwnd = nullptr;
	uint32 _width = 0;
	uint32 _height = 0;

private:
	// Device & Swap
	ComPtr<ID3D11Device> _device = nullptr;
	ComPtr<ID3D11DeviceContext> _deviceContext = nullptr;
	ComPtr<IDXGISwapChain> _swapChain = nullptr;
	
	// RTV
	ComPtr<ID3D11RenderTargetView> _renderTargetView = nullptr;

	// Misc
	D3D11_VIEWPORT _viewport = { 0 };

private:
	void CreateDeviceAndSwapChain();
	void CreateRenderTargetView();

private:
	void RenderBegin();
	void RenderEnd();

};

