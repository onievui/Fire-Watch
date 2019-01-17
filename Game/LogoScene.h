#pragma once

#include "AbstractScene.h"




class LogoScene : public AbstractScene {

private:
	int state;	//���
	int count;	//�o�߃t���[����


public:
	LogoScene(RequestSceneListener* _impl);
	~LogoScene();


	void initialize() override;	//������
	void update() override;	    //�X�V
	void render() override;	    //�`��
	void finalize() override;	//�I������

	static std::unique_ptr<AbstractScene> create(RequestSceneListener* _impl);	//�V�[�������֐�
};