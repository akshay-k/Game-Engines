#include "TransformComponent.h"

Math3D::Matrix44 TransformComponent::GetLocalToWorldCache() const
{
	return mM44LocalToWorldCache;
}

void TransformComponent::SetLocalToWorldCache(const Math3D::Matrix44 matrix44)
{
	mM44LocalToWorldCache = matrix44;
}

float TransformComponent::GetScale()
{
	return mScale;
}

Math3D::Matrix44 TransformComponent::GetRotation()
{
	return mM33Rotation;
}

Math3D::Vector4 TransformComponent::GetTranslation()
{
	return mv3Translation;
}
