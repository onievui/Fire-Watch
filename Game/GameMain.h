#pragma once

#include "AbstractScene.h"
#include "ScreenInfo.h"
#include <memory>






/// <summary>
/// ゲームクラス
/// </summary>
class Game : public RequestSceneListener {

private:
	using SceneFactoryMethod = std::unique_ptr<AbstractScene>(*)(RequestSceneListener *_impl);	//シーン生成関数

	std::unique_ptr<AbstractScene> nowScene;	                //現在のシーン
	SceneID nextScene;							                //次に実行するシーン
	SceneFactoryMethod sceneFactoryMethods[SceneID::SCENE_NUM];	//シーン生成関数のポインタ

public:
	Game();
	~Game();

	void changeScene();	//シーン切り替え

public:
	void initialize(void);
	void update(void);
	void render(void);
	void finalize(void);

	void requestScene(const SceneID _id) override; 	//シーン切り替え要求

private:
	void addScene(const SceneID _id, SceneFactoryMethod _scene_factory_method);
};
