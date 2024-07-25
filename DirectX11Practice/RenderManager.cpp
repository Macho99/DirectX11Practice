#include "pch.h"
#include "RenderManager.h"
#include "Pipeline.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Game.h"

RenderManager::RenderManager(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext)
	:_device(device), _deviceContext(deviceContext)
{
}

void RenderManager::Init()
{
	_pipeline = make_shared<Pipeline>(_deviceContext);

	_cameraBuffer = make_shared<ConstantBuffer<CameraData>>(
		_device, _deviceContext);
	_cameraBuffer->Create();

	_transformBuffer = make_shared<ConstantBuffer<TransformData>>(
		_device, _deviceContext);
	_transformBuffer->Create();

	_rasterizerState = make_shared<RasterizerState>(_device);
	_rasterizerState->Create();
	_samplerState = make_shared<SamplerState>(_device);
	_samplerState->Create();
	_blendState = make_shared<BlendState>(_device);
	_blendState->Create();
}

void RenderManager::Update(shared_ptr<Graphics> graphics)
{
	graphics->RenderBegin();

	PushCameraData();
	GatherRenderableObjects();
	RenderObjects();

	graphics->RenderEnd();
}

void RenderManager::PushCameraData()
{
	_cameraData.matView = Camera::S_MatView;
	_cameraData.matProjection = Camera::S_MatProjection;

	_cameraBuffer->CopyData(_cameraData);
}

void RenderManager::PushTransformData()
{
	_transformBuffer->CopyData(_transformData);
}

void RenderManager::GatherRenderableObjects()
{
	_renderObjects.clear();

	auto& gameObjects = SCENE->GetActiveScene()->GetGameObjects();
	for (const shared_ptr<GameObject>& gameObject : gameObjects)
	{
		shared_ptr<MeshRenderer> meshRenderer = gameObject->GetMeshRenderer();
		if (meshRenderer)
		{
			_renderObjects.push_back(gameObject);
		}
	}
}

void RenderManager::RenderObjects()
{
	for (const shared_ptr<GameObject>& gameObject : _renderObjects)
	{
		shared_ptr<MeshRenderer> meshRenderer = gameObject->GetMeshRenderer();
		if (meshRenderer == nullptr)
		{
			continue;
		}

		shared_ptr<Transform> transform = gameObject->GetTransform();
		if (transform == nullptr)
		{
			continue;
		}

		_transformData.matWorld = transform->GetWorldMatrix();
		PushTransformData();

		PipelineInfo info;
		info.inputLayout = meshRenderer->_inputLayout;
		info.vertexShader = meshRenderer->_vertexShader;
		info.pixelShader = meshRenderer->_pixelShader;
		info.rasterizerState = _rasterizerState;
		info.blendState = _blendState;
		_pipeline->UpdatePipeline(info);
		
		_pipeline->SetVertexBuffer(meshRenderer->_vertexBuffer);
		_pipeline->SetIndexBuffer(meshRenderer->_indexBuffer);
		_pipeline->SetConstantBuffer(_cameraBuffer, 0, SS_VertexShader);
		_pipeline->SetConstantBuffer(_transformBuffer, 1, SS_VertexShader);
		_pipeline->SetTexture(meshRenderer->_texture1, 0, SS_PixelShader);
		_pipeline->SetSamplerState(_samplerState, 0, SS_PixelShader);
		
		_pipeline->DrawIndexed(meshRenderer->_geometry->GetIndexCount(), 0, 0);
	}
}
