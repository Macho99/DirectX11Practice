#pragma once
#include "Component.h"

class Transform : public Component
{
public:
	Transform();
	~Transform();

	virtual void Init() override;
	virtual void Update() override;

	void UpdateTransform();

	// Local
	Vec3 GetLocalScale() { return _localScale; }
	void SetLocalScale(const Vec3& localScale) { _localScale = localScale; }
	Vec3 GetLocalRotation() { return _localRotation; }
	void SetLocalRotation(const Vec3& localRotation) { _localRotation = localRotation; }
	Vec3 GetLocalPosition() { return _localPosition; }
	void SetLocalPosition(const Vec3& localPosition) { _localPosition = localPosition; }

	// World
	Vec3 GetWorldScale() { return _localScale; }
	void SetWorldScale(const Vec3& localScale) { _localScale = localScale; }
	Vec3 GetWorldRotation() { return _localRotation; }
	void SetWorldRotation(const Vec3& localRotation) { _localRotation = localRotation; }
	Vec3 GetWorldPosition() { return _localPosition; }
	void SetWorldPosition(const Vec3& localPosition) { _localPosition = localPosition; }
	
	Matrix GetWorldMatrix() { return _matWorld; }


	bool HasParent() { return _parent != nullptr; }

	shared_ptr<Transform> GetParent() { return _parent; }


private:
	Vec3 _localScale = Vec3::One;
	Vec3 _localRotation = Vec3::Zero;
	Vec3 _localPosition = Vec3::Zero;

	Matrix _matLocal = Matrix::Identity;
	Matrix _matWorld = Matrix::Identity;

	// Cache방식 (수정예정)
	Vec3 _scale;
	Vec3 _rotation;
	Vec3 _position;
	
	Vec3 _right;
	Vec3 _up;
	Vec3 _look;

private:
	shared_ptr<Transform> _parent;
	vector<shared_ptr<Transform>> _children;
};