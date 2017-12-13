#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include "SceneNodeBase.h"


class Camera :
	public SceneNodeBase
{
public:
	Camera();
	~Camera();

	// Getters and Setters
	void SetEye(const Math3D::Vector4 & eye);
	const Math3D::Vector4 & GetEye() const { return mPosition; }
	void SetLookAt(const Math3D::Vector4 & lookAt);
	const Math3D::Vector4 & GetLookAt() const { return mLookAt; }
	void SetUpApproximate(const Math3D::Vector4 & upApprox);
	const Math3D::Vector4 & GetUpApproximate() const { return mUpApproximate; }

	void SetFieldOfViewVert(float fovVert) { mFieldOfViewVert = fovVert; }
	const float & GetFieldOfViewVert() const { return mFieldOfViewVert; }
	void SetAspectRatio(float aspectRatio) { mAspectRatio = aspectRatio; }
	const float & GetAspectRatio() const { return mAspectRatio; }
	const float & GetNearClipDist() const { return mNearClipDist; }
	const float & GetFarClipDist() const { return mFarClipDist; }
	void SetClipDepths(float nearClipDistance, float farClipDistance);

	Math3D::Matrix44 ViewMatrix() const;
	Math3D::Matrix44 ProjectionMatrix() const;

private:
	// view
	Math3D::Vector4 mPosition; // world space position of camera
	Math3D::Vector4 mLookAt; // world space position where this camera looks
	Math3D::Vector4 mUpApproximate; // World-space approximate direction toward which this camera top points
	
	// perspective
	float mFieldOfViewVert; ///< Field of view angle (in degrees) along vertical direction
	float mAspectRatio; ///< Aspect ratio (height to width)
	float mNearClipDist; ///< World-space distance to near clip plane
	float mFarClipDist; ///< World-space distance to far clip plane



};

#endif 