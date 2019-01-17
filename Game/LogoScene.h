#pragma once

#include "AbstractScene.h"




class LogoScene : public AbstractScene {

private:
	int state;	//状態
	int count;	//経過フレーム数


public:
	LogoScene(RequestSceneListener* _impl);
	~LogoScene();


	void initialize() override;	//初期化
	void update() override;	    //更新
	void render() override;	    //描画
	void finalize() override;	//終了処理

	static std::unique_ptr<AbstractScene> create(RequestSceneListener* _impl);	//シーン生成関数
};