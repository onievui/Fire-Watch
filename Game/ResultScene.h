#pragma once

#include "AbstractScene.h"
#include "Map.h"
#include <memory>



class ResultScene : public AbstractScene {
private:
	std::unique_ptr<Map> map;
	int fadeCount;
	int state;

public:
	ResultScene(RequestSceneListener* _impl);
	~ResultScene();

	void initialize() override;	//������
	void update() override;	    //�X�V
	void render() override;	    //�`��
	void finalize() override;	//�I������

	static std::unique_ptr<AbstractScene> create(RequestSceneListener* _impl);	//�V�[�������֐�
};