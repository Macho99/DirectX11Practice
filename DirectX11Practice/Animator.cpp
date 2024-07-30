#include "pch.h"
#include "Animator.h"
#include "Animation.h"
#include "Game.h"
#include "TimeManager.h"

Animator::Animator()
	:Super(ComponentType::Animator)
{
}

Animator::~Animator()
{
}

void Animator::Init()
{
}

void Animator::Update()
{
	if (_currentAnimation == nullptr)
		return;

	const Keyframe& keyframe = GetCurrentKeyframe();

	float deltaTime = TIME->GetDeltaTime();
	_sumTime += deltaTime;

	if (_sumTime >= keyframe.time)
	{
		_sumTime = 0.f;
		_currentKeyframeIndex++;
		int32 totalCount = _currentAnimation->GetKeyFrameCount();

		if (_currentKeyframeIndex >= totalCount)
		{
			if (_currentAnimation->IsLoop())
				_currentKeyframeIndex = 0;
			else
				_currentKeyframeIndex = totalCount - 1;
		}
	}
}

shared_ptr<Animation> Animator::GetCurrentAnimation()
{
	return _currentAnimation;
}

const Keyframe& Animator::GetCurrentKeyframe()
{
	return _currentAnimation->GetKeyFrame(_currentKeyframeIndex);
}
