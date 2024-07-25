#pragma once
#include "Component.h"
class MeshRenderer : public Component
{
	using Super = Component;
public:
	MeshRenderer(ComPtr<ID3D11Device> device,
		ComPtr<ID3D11DeviceContext> deviceContext, shared_ptr<Pipeline> pipeline);
	virtual ~MeshRenderer();

	virtual void Update() override;

private:
	ComPtr<ID3D11Device> _device;
	shared_ptr<Pipeline> _pipeline;

	friend class RenderManager;
	// Mesh
	shared_ptr<Geometry<VertexTextureData>> _geometry;
	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;

	//Material
	shared_ptr<InputLayout> _inputLayout;
	shared_ptr<VertexShader> _vertexShader;
	shared_ptr<PixelShader> _pixelShader;
	shared_ptr<Texture> _texture1;

};

