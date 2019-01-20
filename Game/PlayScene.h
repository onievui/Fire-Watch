#pragma once

#include "AbstractScene.h"
#include "Map.h"
#include "Player.h"
#include "FieldObjectManager.h"
#include <memory>



class PlayScene : public AbstractScene {
private:
	std::unique_ptr<Map>                map;
	std::unique_ptr<Player>             player;
	std::unique_ptr<FieldObjectManager> fieldObjectManager;

public:
	PlayScene(RequestSceneListener* _impl);
	~PlayScene();


	void initialize() override;	//������
	void update() override;	    //�X�V
	void render() override;	    //�`��
	void finalize() override;	//�I������

	static std::unique_ptr<AbstractScene> create(RequestSceneListener* _impl);	//�V�[�������֐�
};