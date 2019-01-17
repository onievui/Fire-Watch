#pragma once

#include "AbstractScene.h"




class ResultScene : public AbstractScene {

private:

public:
	ResultScene(RequestSceneListener* _impl);
	~ResultScene();


	void initialize() override;	//������
	void update() override;	    //�X�V
	void render() override;	    //�`��
	void finalize() override;	//�I������

	static std::unique_ptr<AbstractScene> create(RequestSceneListener* _impl);	//�V�[�������֐�
};