#pragma once

struct PipelineInfo
{
	shared_ptr<InputLayout> inputLayout;
	shared_ptr<VertexShader> vertexShader;
	shared_ptr<PixelShader> pixelShader;
	shared_ptr<RasterizerState> rasterizerState;
	shared_ptr<BlendState> blendState;
	D3D11_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
};

class Pipeline
{
public:
	Pipeline(ComPtr<ID3D11DeviceContext> deviceContext);
	~Pipeline();

	void UpdatePipeline(PipelineInfo info);

	void SetVertexBuffer(shared_ptr<VertexBuffer> vertexBuffer);
	void SetIndexBuffer(shared_ptr<IndexBuffer> indexBuffer);

	template<typename T>
	void SetConstantBuffer(shared_ptr<ConstantBuffer<T>> constantBuffer, 
		uint32 slot, uint32 scope)
	{
		if(scope & SS_VertexShader)
			_deviceContext->VSSetConstantBuffers(slot, 1, constantBuffer->GetComPtr().GetAddressOf());

		if(scope & SS_PixelShader)
			_deviceContext->PSSetConstantBuffers(slot, 1, constantBuffer->GetComPtr().GetAddressOf());
	}

	void SetTexture(shared_ptr<Texture> texture, uint32 slot, uint32 scope);
	void SetSamplerState(shared_ptr<SamplerState> samplerState,
		uint32 slot, uint32 scope);

	void Draw(uint32 vertexCount, uint32 startVertexLocation);
	void DrawIndexed(uint32 indexCount, uint32 startIndexLocation, 
		uint32 baseVertexLocation);

private:
	ComPtr<ID3D11DeviceContext> _deviceContext;
};

