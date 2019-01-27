#include "ResultScene.h"
#include "Pad.h"
#include "ShareDataManager.h"
#include "GameMain.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "ShaderManager.h"


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
	map = std::move(ShareDataManager::getIns()->getMap());
	state = 0;
	fadeCount = 0;

}

/// <summary>
/// シーンの更新
/// </summary>
void ResultScene::update() {
	if (Pad::getIns()->isDown(PadCode::Z) && state == 0 && fadeCount >= 180) {
		state = 1;
		fadeCount = 0;
	}
	if (state == 1 && fadeCount >= 180) {
		implRequestScene->requestScene(SCENE_TITLE);
	}
	if (fadeCount < 180) {
		++fadeCount;
	}
}


/// <summary>
/// シーンの描画
/// </summary>
void ResultScene::render() {
	RenderManager* render_manager = RenderManager::getIns();
	render_manager->changeScreen(ScreenType::MapScreen);
	map->draw();
	render_manager->changeScreen(ScreenType::LightAlphaScreen);
	if (state == 0) {
		DrawRotaGraph(SCREEN_CENTER_X, SCREEN_CENTER_Y, (std::min)(fadeCount / 180.0f*6.0f, 6.0f), 0.0f, ResourceManager::getIns()->getTexture(TextureID::TEXTURE_LIGHT1)->getResource(), true);
	}
	else {
		DrawRotaGraph(SCREEN_CENTER_X, SCREEN_CENTER_Y, (std::max)((180 - fadeCount) / 180.0f*6.0f, 0.0f), 0.0f, ResourceManager::getIns()->getTexture(TextureID::TEXTURE_LIGHT1)->getResource(), true);
	}
	render_manager->changeScreen(ScreenType::MapScreen);
	int killCount = ShareDataManager::getIns()->getKillCount();
	int liveTime = ShareDataManager::getIns()->getLiveTime();
	DrawFormatStringF(SCREEN_CENTER_X - GetDrawFormatStringWidth("KillCount : %d",killCount) / 2.f, SCREEN_CENTER_Y - 20, COLOR_WHITE, "KillCount : %d", killCount);
	DrawFormatStringF(SCREEN_CENTER_X - GetDrawFormatStringWidth("LiveTime : %d m %d s", liveTime/3600,(liveTime/60)%60) / 2.f, SCREEN_CENTER_Y + 20, COLOR_WHITE, "LiveTime : %d m %d s", liveTime / 3600, (liveTime/60) % 60);


	//シェーダーの使用(ライトの反映)
	ShaderManager::getIns()->draw();

	//マップを裏画面に反映
	render_manager->flipScreen();

	render_manager->changeScreen(ScreenType::BackScreen);
	if (state == 0 && fadeCount >= 180) {
		DrawFormatStringF(SCREEN_CENTER_X - GetDrawFormatStringWidth("press Z key") / 2.f, SCREEN_CENTER_Y + 100, COLOR_WHITE, "press Z key");
	}


	render_manager->clearScreen(ScreenType::MapScreen);
	render_manager->clearScreen(ScreenType::LightAlphaScreen);
}

/// <summary>
/// シーンの終了処理
/// </summary>
void ResultScene::finalize() {
	ResourceManager::getIns()->release();
	RenderManager::getIns()->deleteScreen(ScreenType::MapScreen);
	RenderManager::getIns()->deleteScreen(ScreenType::LightAlphaScreen);
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
