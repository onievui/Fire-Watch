#pragma once

#include "SceneID.h"


class RequestSceneListener {

public:
	RequestSceneListener() = default;
	virtual ~RequestSceneListener() = default;

	//�V�[���̐؂�ւ��v��
	virtual void requestScene(const SceneID _id) = 0;
};