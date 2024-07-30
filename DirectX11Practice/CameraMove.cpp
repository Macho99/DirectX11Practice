#include "pch.h"
#include "CameraMove.h"
#include "Game.h"
#include "InputManager.h"
#include "TimeManager.h"

void CameraMove::Update()
{
	auto transform = GetTransform();
	Vec3 pos = transform->GetPosition();
	if (INPUT->GetButton(KEY_TYPE::A))
	{
		pos.x -= 1.f * TIME->GetDeltaTime();
		transform->SetPosition(pos);
	}
	else if (INPUT->GetButton(KEY_TYPE::D))
	{
		pos.x += 1.f * TIME->GetDeltaTime();
		transform->SetPosition(pos);
	}
}
