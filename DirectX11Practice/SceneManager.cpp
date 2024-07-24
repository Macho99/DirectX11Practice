#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "Game.h"

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

		scene->AddGameObject(_camera);
	}

    // TODO
	{
		shared_ptr<GameObject> _gameObject = make_shared<GameObject>(_graphics->GetDevice(),
			_graphics->GetDeviceContext());

		_gameObject->GetOrAddTransform();
		_gameObject->AddComponent(make_shared<MeshRenderer>(_graphics->GetDevice(),
			_graphics->GetDeviceContext(), GAME->GetPipeline()));

		scene->AddGameObject(_gameObject);
	}

    return scene;
}
