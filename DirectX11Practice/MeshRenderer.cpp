#include "pch.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "Mesh.h"
#include "Material.h"
#include "Shader.h"

MeshRenderer::MeshRenderer(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext)
	: Super(ComponentType::MeshRenderer), _device(device)
{
}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::Update()
{
}

void MeshRenderer::SetShader(shared_ptr<Shader> shader)
{
	_material->SetShader(shader);
}

void MeshRenderer::SetTexture(shared_ptr<Texture> texture)
{
	_material->SetTexture(texture);
}

shared_ptr<InputLayout> MeshRenderer::GetInputLayout()
{
	return _material->GetShader()->GetInputLayout();
}

shared_ptr<VertexShader> MeshRenderer::GetVertexShader()
{
	return _material->GetShader()->GetVertexShader();
}

shared_ptr<PixelShader> MeshRenderer::GetPixelShader()
{
	return _material->GetShader()->GetPixelShader();
}

shared_ptr<Texture> MeshRenderer::GetTexture()
{
	return _material->GetTexture();
}
