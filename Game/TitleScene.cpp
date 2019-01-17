#include "TitleScene.h"
#include "Pad.h"
#include "ResourceManager.h"
#include "Sound.h"
#include "GameMain.h"

/// <summary>
/// シーン切り替えインタフェースの登録
/// </summary>
/// <param name="_impl">リスナーへのポインタ</param>
TitleScene::TitleScene(RequestSceneListener* _impl) 
	: AbstractScene(_impl) {
	initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
TitleScene::~TitleScene() {

}

/// <summary>
/// シーンの初期化
/// </summary>
void TitleScene::initialize() {
	ResourceManager::getIns()->load(SCENE_TITLE);
	SoundPlayer::getIns()->reset();
}

/// <summary>
/// シーンの更新
/// </summary>
void TitleScene::update() {
	if (Pad::getIns()->isDown(PadCode::Z)) {
		implRequestScene->requestScene(SCENE_PLAY);
	}
}


/// <summary>
/// シーンの描画
/// </summary>
void TitleScene::render() {
	//DrawRotaGraph(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.5f, 0.0f, ResourceManager::getIns()->getTexture(TEXTURE_TITLE)->getResource(), true);
	//DrawFormatStringF(SCREEN_CENTER_X - GetDrawFormatStringWidth("press Z key") / 2.f, SCREEN_CENTER_Y + 100, COLOR_WHITE, "press Z key");
}

/// <summary>
/// シーンの終了処理
/// </summary>
void TitleScene::finalize() {

}

/// <summary>
/// シーン生成処理
/// </summary>
/// <param name="_impl">インタフェースへのポインタ</param>
/// <returns>
/// シーンオブジェクト
/// </returns>
std::unique_ptr<AbstractScene> TitleScene::create(RequestSceneListener* _impl) {
	return std::move(std::make_unique<TitleScene>(_impl));
}
