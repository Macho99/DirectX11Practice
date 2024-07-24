#include "pch.h"
#include "Game.h"
#include "Camera.h"	
#include "MeshRenderer.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "TimeManager.h"

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
	_pipeline = make_shared<Pipeline>(_graphics->GetDeviceContext());

	_inputManager = make_shared<InputManager>();
	_inputManager->Init(hwnd);

	_timeManager = make_shared<TimeManager>();
	_timeManager->Init();

	_sceneManager = make_shared<SceneManager>(_graphics);
	_sceneManager->Init();

	SCENE->LoadScene(L"TestScene");
}

void Game::Update()
{
	_graphics->RenderBegin();
	TIME->Update();
	INPUT->Update();
	SCENE->Update();
	_graphics->RenderEnd();
}


void Game::Render()
{
}