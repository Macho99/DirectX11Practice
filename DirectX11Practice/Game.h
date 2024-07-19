#pragma once
#include "GameObject.h"

class Game
{
public:
	Game();
	virtual ~Game();

public:
	void Init(HWND hwnd);
	void Update();
	void Render();

private:
	HWND _hwnd = nullptr;
	//uint32 _width = 0;
	//uint32 _height = 0;

	shared_ptr<Graphics> _graphics;
	shared_ptr<Pipeline> _pipeline;


	// TEMP
	shared_ptr<GameObject> _gameObject;
	shared_ptr<GameObject> _camera;
};

