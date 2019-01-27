#pragma once

#include "AbstractScene.h"
#include "Map.h"
#include "Player.h"
#include "FieldObjectManager.h"
#include "MouseEventManager.h"
#include "ArrowManager.h"
#include "EnemyManager.h"
#include "MessageInterface.h"


class PlayScene : public AbstractScene, public MessageInterface {
private:
	enum class PlaySceneState {
		PLAYING,
		PLAYER_DEAD,
		TENT_DESTROYED,
	};

private:
	PlaySceneState                      state;
	std::unique_ptr<Map>                map;
	std::unique_ptr<Player>             player;
	std::unique_ptr<EnemyManager>       enemyManager;
	std::unique_ptr<FieldObjectManager> fieldObjectManager;
	std::unique_ptr<ArrowManager>       arrowManager;
	std::unique_ptr<MouseEventManager>  mouseEventManager;

public:
	PlayScene(RequestSceneListener* _impl);
	~PlayScene();


	void initialize() override;	//������
	void update() override;	    //�X�V
	void render() override;	    //�`��
	void finalize() override;	//�I������

	static std::unique_ptr<AbstractScene> create(RequestSceneListener* _impl);	//�V�[�������֐�
public:
	bool getMessage(const MessageType _type, void* _out, void* _in);

private:
	void updatePlaying();
	void updatePlayerDead();
	void updateTentDestroyed();
};