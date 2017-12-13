#include "SceneNodeBase.h"
#include <iostream>

SceneNodeBase::SceneNodeBase()
{
}


SceneNodeBase::~SceneNodeBase()
{
}

void SceneNodeBase::AdoptChild(SceneNodeBase child)
{
	mSceneNodes.push_back(child);
	child.SetParent(this);
}

void SceneNodeBase::SetParent(SceneNodeBase * parent)
{
	mParent->AdoptChild(*this);
}

void SceneNodeBase::Render()
{
	if (mShouldRender) {
		//drawArrays or similar here
	}
}

void SceneNodeBase::RenderChildren()
{
	for (auto child : mSceneNodes) {
		child.Render();
	}
}
