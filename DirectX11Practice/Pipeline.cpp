#include "pch.h"
#include "Pipeline.h"

Pipeline::Pipeline(ComPtr<ID3D11DeviceContext> deviceContext)
	:_deviceContext(deviceContext)
{
}

Pipeline::~Pipeline()
{
}

void Pipeline::UpdatePipeline(PipelineInfo info)
{
	// IA
	uint32 stride = sizeof(VertexTextureData);
	uint32 offset = 0;

	_deviceContext->IASetInputLayout(info.inputLayout->GetComPtr().Get());
	_deviceContext->IASetPrimitiveTopology(info.topology);


	// VS
	if(info.vertexShader)
	{
		_deviceContext->VSSetShader(info.vertexShader->GetComPtr().Get(), nullptr, 0);
	}

	// RS
	if (info.rasterizerState)
	{
		_deviceContext->RSSetState(info.rasterizerState->GetComPtr().Get());
	}

	// PS
	if(info.pixelShader)
	{
		_deviceContext->PSSetShader(info.pixelShader->GetComPtr().Get(), nullptr, 0);
	}

	// OM
	if(info.blendState)
	{
		_deviceContext->OMSetBlendState(info.blendState->GetComPtr().Get(),
			info.blendState->GetBlendFactor(), info.blendState->GetSampleMask());
	}
}

void Pipeline::SetVertexBuffer(shared_ptr<VertexBuffer> vertexBuffer)
{
	uint32 stride = vertexBuffer->GetStride();
	uint32 offset = vertexBuffer->GetOffset();
	_deviceContext->IASetVertexBuffers(0, 1, 
		vertexBuffer->GetComPtr().GetAddressOf(), &stride, &offset);
}

void Pipeline::SetIndexBuffer(shared_ptr<IndexBuffer> indexBuffer)
{
	_deviceContext->IASetIndexBuffer(indexBuffer->GetComPtr().Get(),
		DXGI_FORMAT_R32_UINT, 0);
}

void Pipeline::SetTexture(shared_ptr<Texture> texture, uint32 slot, uint32 scope)
{
	if(scope & SS_VertexShader)
		_deviceContext->VSSetShaderResources(slot, 1, texture->GetComPtr().GetAddressOf());
		
	if(scope & SS_PixelShader)
		_deviceContext->PSSetShaderResources(slot, 1, texture->GetComPtr().GetAddressOf());
}

void Pipeline::SetSamplerState(shared_ptr<SamplerState> samplerState, uint32 slot, uint32 scope)
{
	if (scope & SS_VertexShader)
		_deviceContext->VSSetSamplers(slot, 1, samplerState->GetComPtr().GetAddressOf());

	if (scope & SS_PixelShader)
		_deviceContext->PSSetSamplers(slot, 1, samplerState->GetComPtr().GetAddressOf());
}

void Pipeline::Draw(uint32 vertexCount, uint32 startVertexLocation)
{
	_deviceContext->Draw(vertexCount, startVertexLocation);
}

void Pipeline::DrawIndexed(uint32 indexCount, uint32 startIndexLocation, uint32 baseVertexLocation)
{
	_deviceContext->DrawIndexed(indexCount, startIndexLocation, baseVertexLocation);
}
