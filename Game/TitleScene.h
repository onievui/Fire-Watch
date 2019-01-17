#pragma once

#include "AbstractScene.h"




class TitleScene : public AbstractScene {

private:

public:
	TitleScene(RequestSceneListener* _impl);
	~TitleScene();


	void initialize() override;	//������
	void update() override;	    //�X�V
	void render() override;	    //�`��
	void finalize() override;	//�I������

	static std::unique_ptr<AbstractScene> create(RequestSceneListener* _impl);	//�V�[�������֐�
};