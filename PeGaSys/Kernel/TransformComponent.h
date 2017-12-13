#pragma once

#include "Matrix44.h"
class TransformComponent {

public:
	Math3D::Matrix44 GetLocalToWorldCache() const;
	void SetLocalToWorldCache(const Math3D::Matrix44 matrix44);
	float GetScale();
	Math3D::Matrix44 GetRotation();
	Math3D::Vector4 GetTranslation();

private:
	float mScale;
	Math3D::Matrix44 mM33Rotation; //rotation relative to parent
	Math3D::Vector4 mv3Translation; //translation relative to parent
	TransformComponent* mParent; // address of parent transform
	Math3D::Matrix44 mM44LocalToWorldCache; // read-only 4x4 matrix tranformation from root. Not just from parent.


};
