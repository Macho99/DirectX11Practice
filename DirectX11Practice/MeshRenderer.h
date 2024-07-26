#pragma once
#include "Component.h"

class Mesh;
class Material;
class Shader;

class MeshRenderer : public Component
{
	using Super = Component;
public:
	MeshRenderer(ComPtr<ID3D11Device> device,
		ComPtr<ID3D11DeviceContext> deviceContext);
	virtual ~MeshRenderer();

	virtual void Update() override;

	void SetMesh(shared_ptr<Mesh> mesh) { _mesh = mesh; }
	void SetMaterial(shared_ptr<Material> material) { _material = material; }
	void SetShader(shared_ptr<Shader> shader);
	void SetTexture(shared_ptr<Texture> texture);

	shared_ptr<Mesh> GetMesh() { return _mesh; }
	shared_ptr<Material> GetMaterial() { return _material; }
	shared_ptr<InputLayout> GetInputLayout();
	shared_ptr<VertexShader> GetVertexShader();
	shared_ptr<PixelShader> GetPixelShader();
	shared_ptr<Texture> GetTexture();

private:
	ComPtr<ID3D11Device> _device;

	friend class RenderManager;
	shared_ptr<Mesh> _mesh;
	shared_ptr<Material> _material;
};

