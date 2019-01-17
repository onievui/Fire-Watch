#include "ResultScene.h"
#include "Pad.h"
#include "ShareDataManager.h"
#include "GameMain.h"


/// <summary>
/// シーン切り替えインタフェースの登録
/// </summary>
/// <param name="_impl">リスナーへのポインタ</param>
ResultScene::ResultScene(RequestSceneListener* _impl) 
	: AbstractScene(_impl) {
	initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
ResultScene::~ResultScene() {

}

/// <summary>
/// シーンの初期化
/// </summary>
void ResultScene::initialize() {
}

/// <summary>
/// シーンの更新
/// </summary>
void ResultScene::update() {
	if (Pad::getIns()->isDown(PadCode::Z)) {
		implRequestScene->requestScene(SCENE_TITLE);
	}
	
}


/// <summary>
/// シーンの描画
/// </summary>
void ResultScene::render() {
	//SetFontSize(30);
	//DrawFormatStringF(SCREEN_CENTER_X - GetDrawFormatStringWidth("SCORE : %d", ShareDataManager::getIns()->getScore()) / 2.f, 
	//	(float)SCREEN_CENTER_Y, COLOR_WHITE, "SCORE : %d", ShareDataManager::getIns()->getScore());
	//SetFontSize(20);
	//DrawFormatStringF(SCREEN_CENTER_X - GetDrawFormatStringWidth("press Z key") / 2.f, SCREEN_CENTER_Y + 100.0f, COLOR_WHITE, "press Z key");
}

/// <summary>
/// シーンの終了処理
/// </summary>
void ResultScene::finalize() {
}

/// <summary>
/// シーン生成処理
/// </summary>
/// <param name="_impl">インタフェースへのポインタ</param>
/// <returns>
/// シーンオブジェクト
/// </returns>
std::unique_ptr<AbstractScene> ResultScene::create(RequestSceneListener* _impl) {
	return std::move(std::make_unique<ResultScene>(_impl));
}
