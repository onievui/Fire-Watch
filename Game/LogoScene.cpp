#include "LogoScene.h"
#include "Pad.h"
#include "ResourceManager.h"
#include "GameMain.h"

/// <summary>
/// シーン切り替えインタフェースの登録
/// </summary>
/// <param name="_impl">リスナーへのポインタ</param>
LogoScene::LogoScene(RequestSceneListener* _impl) 
	: AbstractScene(_impl) {
	initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
LogoScene::~LogoScene() {

}

/// <summary>
/// シーンの初期化
/// </summary>
void LogoScene::initialize() {
	ResourceManager::getIns()->load(SCENE_LOGO);
	state = 0;
	count = 0;
}

/// <summary>
/// シーンの更新
/// </summary>
void LogoScene::update() {
	//Zキーでスキップ
	if (Pad::getIns()->isDown(PadCode::Z)) {
		count = 270;
		state = 2;
	}

	//ロゴ表示時間内ならカウンタを増やす
	if (count < 270) {
		count++;
	}
	//1つ目のロゴが表示し終わったら2つ目を表示する
	else if (state == 0) {
		count = 0;
		state = 1;
	}
	//タイトルシーンに遷移する
	else {
		implRequestScene->requestScene(SCENE_TITLE);
	}
}


/// <summary>
/// シーンの描画
/// </summary>
void LogoScene::render() {
	if (count < 180) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255 * (count / 90.0f)));
	}
	else {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255 * ((270.0f - count) / 90.0f)));
	}
	if (state == 0) {
		DrawRotaGraph(SCREEN_CENTER_X, SCREEN_CENTER_Y, 1.0f, 0.0f, ResourceManager::getIns()->getTexture(TEXTURE_LOGO)->getResource(), true);
	}
	else if (state == 1) {
		DrawRotaGraph(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.5f, 0.0f, ResourceManager::getIns()->getTexture(TEXTURE_LOGO2)->getResource(), true);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

/// <summary>
/// シーンの終了処理
/// </summary>
void LogoScene::finalize() {
	ResourceManager::getIns()->release();
}

/// <summary>
/// シーン生成処理
/// </summary>
/// <param name="_impl">インタフェースへのポインタ</param>
/// <returns>
/// シーンオブジェクト
/// </returns>
std::unique_ptr<AbstractScene> LogoScene::create(RequestSceneListener * _impl) {
	return std::move(std::make_unique<LogoScene>(_impl));
}
