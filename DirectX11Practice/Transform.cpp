#include "pch.h"
#include "Transform.h"

Transform::Transform() : Super(ComponentType::Transform)
{
}

Transform::~Transform()
{
}

void Transform::Awake()
{
}

void Transform::Update()
{
}

void Transform::UpdateTransform()
{
	// SRT
	Matrix matScale = Matrix::CreateScale(_localScale);
	Matrix matRotation = Matrix::CreateRotationX(_localRotation.x);
	matRotation *= Matrix::CreateRotationY(_localRotation.y);
	matRotation *= Matrix::CreateRotationZ(_localRotation.z);
	Matrix matTranslation = Matrix::CreateTranslation(_localPosition);

	_matLocal = matScale * matRotation * matTranslation;
	
	if (HasParent())
	{
		_matWorld = _matLocal * _parent->GetWorldMatrix();
	}
	else
	{
		_matWorld = _matLocal;
	}

	Quaternion quat;

	_matWorld.Decompose(_scale, quat, _position);
	_rotation = ToEulerAngles(quat);

	//_right = Vec3::TransformNormal(Vec3::Right, _matWorld);
	//_up = Vec3::TransformNormal(Vec3::Up, _matWorld);
	//_forward = Vec3::TransformNormal(Vec3::Backward, _matWorld);
	//// SimpleMath 라이브러리가 오른손 좌표계를 사용하기 때문

	for (const shared_ptr<Transform>& child : _children)
	{
		child->UpdateTransform();
	}
}

void Transform::SetScale(const Vec3& scale)
{
	if (HasParent())
	{
		Vec3 parentScale = _parent->GetScale();
		Vec3 newScale = scale;
		newScale.x /= parentScale.x;
		newScale.y /= parentScale.y;
		newScale.z /= parentScale.z;
		SetLocalScale(newScale);
	}
	else
	{
		SetLocalScale(scale);
	}
}

void Transform::SetRotation(const Vec3& rotation)
{
	if (HasParent())
	{
		Matrix worldToParentLocalMat = _parent->GetWorldMatrix().Invert();

		Vec3 newRot;
		newRot.TransformNormal(rotation, worldToParentLocalMat);

		SetLocalRotation(newRot);
	}
	else
	{
		SetLocalRotation(rotation);
	}
}

void Transform::SetPosition(const Vec3& position)
{
	if (HasParent())
	{
		Matrix worldToParentLocalMat = _parent->GetWorldMatrix().Invert();

		Vec3 newPos;
		newPos.Transform(position, worldToParentLocalMat);

		SetLocalPosition(newPos);
	}
	else
	{
		SetLocalPosition(position);
	}
}

// this implementation assumes normalized quaternion
// converts to Euler angles in 3-2-1 sequence
Vec3 Transform::ToEulerAngles(Quaternion q) {
	Vec3 angles;

	// roll (x-axis rotation)
	double sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
	double cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
	angles.x = std::atan2(sinr_cosp, cosr_cosp);

	// pitch (y-axis rotation)
	double sinp = std::sqrt(1 + 2 * (q.w * q.y - q.x * q.z));
	double cosp = std::sqrt(1 - 2 * (q.w * q.y - q.x * q.z));
	angles.y = 2 * std::atan2(sinp, cosp) - 3.14159f / 2;

	// yaw (z-axis rotation)
	double siny_cosp = 2 * (q.w * q.z + q.x * q.y);
	double cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
	angles.z = std::atan2(siny_cosp, cosy_cosp);

	return angles;
}