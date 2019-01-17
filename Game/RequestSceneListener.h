#pragma once

#include "SceneID.h"


class RequestSceneListener {

public:
	RequestSceneListener() = default;
	virtual ~RequestSceneListener() = default;

	//ƒV[ƒ“‚ÌØ‚è‘Ö‚¦—v‹
	virtual void requestScene(const SceneID _id) = 0;
};