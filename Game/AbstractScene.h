#pragma once

#include "RequestSceneListener.h"
#include <memory>




/// <summary>
/// シーンの抽象クラス
/// </summary>
class AbstractScene {

protected:
	RequestSceneListener* implRequestScene;	//シーン切り替えインタフェース

public:
	AbstractScene() = default;
	AbstractScene(RequestSceneListener* _impl); 	//シーン切り替えインタフェースの登録
	virtual ~AbstractScene() = default;

	virtual void initialize() = 0;	//シーンの初期化
	virtual void update() = 0;	    //シーンの更新
	virtual void render() = 0;	    //シーンの描画
	virtual void finalize() = 0;	//シーンの終了処理


};

