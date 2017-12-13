#pragma once
#ifndef SCENE_NODE_BASE_H
#define SCENE_NODE_BASE_H
#include "../Math/Matrix44.h"
#include <vector>

class SceneNodeBase
{
public:
	SceneNodeBase();
	~SceneNodeBase();

	void AdoptChild(SceneNodeBase child);

	void SetParent(SceneNodeBase* parent);

	void Render();
	void RenderChildren();

	Math3D::Matrix44 GetLocalToWorld() const { return mLocalToWorld; }
	void SetLocalToWorld(const Math3D::Matrix44 l2w) { mLocalToWorld = l2w; }


private:
	//TODO: ptr to scene manager
	//TODO: ptr to parent scene node
	//TODO: container of children scene nodes
	Math3D::Matrix44 mLocalToWorld;
	bool mShouldRender;
	std::vector<SceneNodeBase> mSceneNodes;
	SceneNodeBase * mParent;
};

#endif