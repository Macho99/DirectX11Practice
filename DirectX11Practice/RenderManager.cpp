#include "pch.h"
#include "RenderManager.h"
#include "Pipeline.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Game.h"
#include "Mesh.h"
#include "Animation.h"
#include "Animator.h"

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

	_animationBuffer = make_shared<ConstantBuffer<AnimationData>>(
		_device, _deviceContext);
	_animationBuffer->Create();

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

void RenderManager::PushAnimationData()
{
	_animationBuffer->CopyData(_animationData);
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

		shared_ptr<Animator> animator = gameObject->GetAnimator();
		if (animator)
		{
			const Keyframe& keyframe = animator->GetCurrentKeyframe();
			_animationData.spriteOffset = keyframe.offset;
			_animationData.spriteSize = keyframe.size;
			_animationData.textureSize = animator->GetCurrentAnimation()->GetTextureSize();
			_animationData.useAnimation = 1.f;
			PushAnimationData();
			_pipeline->SetConstantBuffer(_animationBuffer, 2, SS_VertexShader);
			_pipeline->SetTexture(animator->GetCurrentAnimation()->GetTexture(), 
				0, SS_PixelShader);
		}
		else
		{
			_animationData.spriteOffset = Vec2::Zero;
			_animationData.spriteSize = Vec2::Zero;
			_animationData.textureSize = Vec2::Zero;
			_animationData.useAnimation = 0.f;
			PushAnimationData();
			_pipeline->SetConstantBuffer(_animationBuffer, 2, SS_VertexShader);
			_pipeline->SetTexture(meshRenderer->GetTexture(), 0, SS_PixelShader);
		}

		PipelineInfo info;
		info.inputLayout = meshRenderer->GetInputLayout();
		info.vertexShader = meshRenderer->GetVertexShader();
		info.pixelShader = meshRenderer->GetPixelShader();
		info.rasterizerState = _rasterizerState;
		info.blendState = _blendState;
		_pipeline->UpdatePipeline(info);
		
		_pipeline->SetVertexBuffer(meshRenderer->GetMesh()->GetVertexBuffer());
		_pipeline->SetIndexBuffer(meshRenderer->GetMesh()->GetIndexBuffer());
		_pipeline->SetConstantBuffer(_cameraBuffer, 0, SS_VertexShader);
		_pipeline->SetConstantBuffer(_transformBuffer, 1, SS_VertexShader);
		_pipeline->SetSamplerState(_samplerState, 0, SS_PixelShader);
		
		_pipeline->DrawIndexed(meshRenderer->GetMesh()->GetIndexBuffer()->GetCount(), 0, 0);
	}
}
