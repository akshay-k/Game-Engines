#include "Camera.h"
#include <glad/glad.h>
#include <glfw/glfw3.h>


Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::SetEye(const Math3D::Vector4 & eye)
{
	mPosition.setX(eye.getX());
	mPosition.setY(eye.getY());
	mPosition.setZ(eye.getZ());
	mPosition.setW(1.0f);
	Math3D::Matrix44 loc2w = GetLocalToWorld();
	loc2w.SetTranslation(mPosition);
	SetLocalToWorld(loc2w);
}


void Camera::SetLookAt(const Math3D::Vector4 & lookAt)
{
	mLookAt.setX(lookAt.getX());
	mLookAt.setY(lookAt.getY());
	mLookAt.setZ(lookAt.getZ());
	mLookAt.setW(0.0f);
}

void Camera::SetUpApproximate(const Math3D::Vector4 & upApprox)
{
	mUpApproximate.setX(upApprox.getX());
	mUpApproximate.setY(upApprox.getY());
	mUpApproximate.setZ(upApprox.getZ());
	mUpApproximate.setW(0.0f);
}

void Camera::SetClipDepths(float nearClipDistance, float farClipDistance)
{
	mNearClipDist = nearClipDistance;
	mFarClipDist = farClipDistance;
}


Math3D::Matrix44 Camera::ViewMatrix() const
{
	Math3D::Matrix44 viewMatrix = Math3D::Matrix44();
	viewMatrix.SetView(GetEye(), GetLookAt(), GetUpApproximate());
	return viewMatrix;
}

Math3D::Matrix44 Camera::ProjectionMatrix() const
{
	Math3D::Matrix44 projMatrix = Math3D::Matrix44();
	projMatrix.SetProjection(mFieldOfViewVert, mAspectRatio, mNearClipDist, mFarClipDist);
	return projMatrix;
}




