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
	float _clearColor[4] = { 1.f, 0.5f, 0.5f, 0.5f };

private:
	// Geometry
	vector<Vertex> _vertices;
	ComPtr<ID3D11Buffer> _vertexBuffer = nullptr;
	vector<uint32> _indices;
	ComPtr<ID3D11Buffer> _indexBuffer = nullptr;
	ComPtr<ID3D11InputLayout> _inputLayout = nullptr;

	// VS
	ComPtr<ID3D11VertexShader> _vertexShader = nullptr;
	ComPtr<ID3DBlob> _vsBlob = nullptr;

	// RS
	ComPtr<ID3D11RasterizerState> _rasterizerState = nullptr;

	// PS
	ComPtr<ID3D11PixelShader> _pixelShader = nullptr;
	ComPtr<ID3DBlob> _psBlob = nullptr;

	// SRV
	ComPtr<ID3D11ShaderResourceView> _shaderResourceView = nullptr;

	ComPtr<ID3D11SamplerState> _samplerState = nullptr;
	ComPtr<ID3D11BlendState> _blendState = nullptr;

private:
	// [CPU <-> RAM] [GPU <-> VRAM]
	// SRT
	TransformData _transformData;
	ComPtr<ID3D11Buffer> _constantBuffer;


private:
	void RenderBegin();
	void RenderEnd();

private:
	void CreateDeviceAndSwapChain();
	void CreateRenderTargetView();
	void SetViewport();

private:
	void CreateGeometry();
	void CreateInputLayout();

	void CreateVS();
	void CreatePS();

	void CreateRasterizerState();
	void CreateSamplerState();
	void CreateBlendState();
	void CreateSRV();

	void CreateConstantBuffer();

	void LoadShaderFromFile(const wstring& path, const string& name, 
		const string& version, ComPtr<ID3DBlob>& blob);
};

