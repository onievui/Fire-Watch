#pragma once

#include "RequestSceneListener.h"
#include <memory>




/// <summary>
/// �V�[���̒��ۃN���X
/// </summary>
class AbstractScene {

protected:
	RequestSceneListener* implRequestScene;	//�V�[���؂�ւ��C���^�t�F�[�X

public:
	AbstractScene() = default;
	AbstractScene(RequestSceneListener* _impl); 	//�V�[���؂�ւ��C���^�t�F�[�X�̓o�^
	virtual ~AbstractScene() = default;

	virtual void initialize() = 0;	//�V�[���̏�����
	virtual void update() = 0;	    //�V�[���̍X�V
	virtual void render() = 0;	    //�V�[���̕`��
	virtual void finalize() = 0;	//�V�[���̏I������


};

