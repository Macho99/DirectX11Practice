#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "Game.h"
#include "ResourceManager.h"
#include "Mesh.h"
#include "Material.h"
#include "Animation.h"
#include "Animator.h"
#include "CameraMove.h"

SceneManager::SceneManager(shared_ptr<Graphics> graphics)
	: _graphics(graphics)
{
}

void SceneManager::Init()
{
    if (_activeScene == nullptr)
        return;

    _activeScene->Awake();
    _activeScene->Start();
}

void SceneManager::Update()
{
    if (_activeScene == nullptr)
        return;

    _activeScene->FixedUpdate();
    _activeScene->Update();
    _activeScene->LateUpdate();
}

void SceneManager::LoadScene(wstring sceneName)
{
	// Resource

	_activeScene = LoadTestScene();
	Init();
}

shared_ptr<Scene> SceneManager::LoadTestScene()
{
    shared_ptr<Scene> scene = make_shared<Scene>();


	{
		shared_ptr<GameObject> _camera = make_shared<GameObject>(_graphics->GetDevice(),
			_graphics->GetDeviceContext());

		_camera->GetOrAddTransform();
		_camera->AddComponent(make_shared<Camera>());
		_camera->AddComponent(make_shared<CameraMove>());

		scene->AddGameObject(_camera);
	}

    // TODO
	{
		shared_ptr<GameObject> _gameObject = make_shared<GameObject>(_graphics->GetDevice(),
			_graphics->GetDeviceContext());
		{
			_gameObject->GetOrAddTransform();
			auto meshRenderer = make_shared<MeshRenderer>(_graphics->GetDevice(),
				_graphics->GetDeviceContext());
			_gameObject->AddComponent(meshRenderer);

			auto mesh = RESOURCES->Get<Mesh>(L"Quad");
			meshRenderer->SetMesh(mesh);

			auto material = RESOURCES->Get<Material>(L"Default");
			meshRenderer->SetMaterial(material);

			auto animator = make_shared<Animator>();
			_gameObject->AddComponent(animator);
			auto anim = RESOURCES->Get<Animation>(L"SnakeAnim");
			animator->SetAnimation(anim);
		}
		scene->AddGameObject(_gameObject);
	}
	{
		shared_ptr<GameObject> _gameObject = make_shared<GameObject>(_graphics->GetDevice(),
			_graphics->GetDeviceContext());
		{
			auto transfrom = _gameObject->GetOrAddTransform();
			transfrom->SetPosition(Vec3{ 1.f, 1.f, 0.f });
			auto meshRenderer = make_shared<MeshRenderer>(_graphics->GetDevice(),
				_graphics->GetDeviceContext());
			_gameObject->AddComponent(meshRenderer);

			auto mesh = RESOURCES->Get<Mesh>(L"Quad");
			meshRenderer->SetMesh(mesh);

			auto material = RESOURCES->Get<Material>(L"Default");
			meshRenderer->SetMaterial(material);

			auto animator = make_shared<Animator>();
			_gameObject->AddComponent(animator);
			auto anim = RESOURCES->Get<Animation>(L"SnakeAnim");
			animator->SetAnimation(anim);
		}
		scene->AddGameObject(_gameObject);
	}

    return scene;
}
