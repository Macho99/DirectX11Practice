#include "pch.h"
#include "Game.h"
#include "Camera.h"	
#include "MeshRenderer.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "RenderManager.h"

unique_ptr<Game> GGame = make_unique<Game>();

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;

	_graphics = make_shared<Graphics>(hwnd);

	_inputManager = make_shared<InputManager>();
	_inputManager->Init(hwnd);

	_timeManager = make_shared<TimeManager>();
	_timeManager->Init();

	_sceneManager = make_shared<SceneManager>(_graphics);
	_sceneManager->Init();

	_resourceManager = make_shared<ResourceManager>(_graphics->GetDevice());
	_resourceManager->Init();

	_renderManager = make_shared<RenderManager>(_graphics->GetDevice(), 
		_graphics->GetDeviceContext());
	_renderManager->Init();

	SCENE->LoadScene(L"TestScene");
}

void Game::Update()
{
	TIME->Update();
	INPUT->Update();
	SCENE->Update();
}


void Game::Render()
{
	RENDER->Update(_graphics);
}