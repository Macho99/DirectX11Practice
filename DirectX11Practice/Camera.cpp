#include "pch.h"
#include "Camera.h"

Matrix Camera::S_MatView = Matrix::Identity;
Matrix Camera::S_MatProjection = Matrix::Identity;

Camera::Camera() : Super(ComponentType::Camera)
{
}

Camera::~Camera()
{
}

void Camera::Update()
{
	UpdateMatrix();
}

void Camera::UpdateMatrix()
{
	S_MatView = GetTransform()->GetWorldMatrix().Invert();

	if (_type == ProjectionType::Perspective)
		S_MatProjection = ::XMMatrixPerspectiveLH(XM_PI / 4.f, 800.f / 600.f, 1.f, 1000.f);
	else if (_type == ProjectionType::Orthographic)
		S_MatProjection = ::XMMatrixOrthographicLH(800.f, 600.f, 1.f, 1000.f);
}
