#include "pch.h"
#include "Game.h"
#include "Camera.h"	

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

	_gameObject = make_shared<GameObject>(_graphics->GetDevice(), 
		_graphics->GetDeviceContext());
	{
		_gameObject->GetOrAddTransform();

	}

	_camera = make_shared<GameObject>(_graphics->GetDevice(),
		_graphics->GetDeviceContext());
	{
		_camera->GetOrAddTransform();
		_camera->AddComponent(make_shared<Camera>());
	}
}

void Game::Update()
{
	_gameObject->Update();
}


void Game::Render()
{
	_graphics->RenderBegin();

	ComPtr<ID3D11DeviceContext> deviceContext = _graphics->GetDeviceContext();
	{
		_gameObject->Render(_pipeline);
	}
	_graphics->RenderEnd();
}