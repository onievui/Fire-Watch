#pragma once

#include "AbstractScene.h"
#include "Map.h"
#include "Player.h"
#include "FieldObjectManager.h"
#include "MouseEventManager.h"
#include "ArrowManager.h"
#include "EnemyManager.h"



class PlayScene : public AbstractScene {
private:
	std::unique_ptr<Map>                map;
	std::unique_ptr<Player>             player;
	std::unique_ptr<EnemyManager>       enemyManager;
	std::unique_ptr<FieldObjectManager> fieldObjectManager;
	std::unique_ptr<ArrowManager>       arrowManager;
	std::unique_ptr<MouseEventManager>  mouseEventManager;

public:
	PlayScene(RequestSceneListener* _impl);
	~PlayScene();


	void initialize() override;	//初期化
	void update() override;	    //更新
	void render() override;	    //描画
	void finalize() override;	//終了処理

	static std::unique_ptr<AbstractScene> create(RequestSceneListener* _impl);	//シーン生成関数
};