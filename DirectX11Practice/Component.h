#pragma once

class GameObject;

class Component
{
public:
	Component();
	virtual ~Component();

	shared_ptr<GameObject> GetGameObject() { return _owner.lock(); }

	virtual void Init();
	virtual void Update();

private:
	weak_ptr<GameObject> _owner;
};

