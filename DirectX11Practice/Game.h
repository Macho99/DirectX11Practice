#pragma once
#include "GameObject.h"

class InputManager;
class TimeManager;
class SceneManager;
class ResourceManager;
class RenderManager;

class Game
{
public:
	Game();
	virtual ~Game();

public:
	void Init(HWND hwnd);
	void Update();
	void Render();

	shared_ptr<InputManager> GetInputManager() { return _inputManager; }
	shared_ptr<TimeManager> GetTimeManager() { return _timeManager; }
	shared_ptr<SceneManager> GetSceneManager() { return _sceneManager; }
	shared_ptr<ResourceManager> GetResourceManager() { return _resourceManager; }
	shared_ptr<RenderManager> GetRenderManager() { return _renderManager; }

private:
	HWND _hwnd = nullptr;
	//uint32 _width = 0;
	//uint32 _height = 0;

	shared_ptr<Graphics> _graphics;

private:
	shared_ptr<InputManager> _inputManager;
	shared_ptr<TimeManager> _timeManager;
	shared_ptr<SceneManager> _sceneManager;
	shared_ptr<ResourceManager> _resourceManager;
	shared_ptr<RenderManager> _renderManager;
};

extern unique_ptr<Game> GGame;