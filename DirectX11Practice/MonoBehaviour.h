#pragma once
#include "Component.h"
class MonoBehaviour : public Component
{
	using Super = Component;

public:
	MonoBehaviour();
	virtual ~MonoBehaviour();

	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
};

