#include "TitleScene.h"
#include "Pad.h"
#include "ResourceManager.h"
#include "Sound.h"
#include "GameMain.h"
#include "ShaderManager.h"
#include "ShareDataManager.h"
#include "RenderManager.h"


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
	RenderManager::getIns()->addScreen(ScreenType::MapScreen, MakeScreen(SCREEN_WIDTH, SCREEN_HEIGHT, TRUE), Vector2(0, 0));
	RenderManager::getIns()->addScreen(ScreenType::LightAlphaScreen, MakeScreen(SCREEN_WIDTH, SCREEN_HEIGHT, TRUE), Vector2(0, 0));
	RenderManager::getIns()->changeScreen(ScreenType::MapScreen);
	ShaderManager::getIns()->setShader(ShaderID::SHADER_LIGHT);
	map = std::make_unique<Map>();
	fadeCount = 0;
	state = 0;
	SetFontSize(30);
}

/// <summary>
/// シーンの更新
/// </summary>
void TitleScene::update() {
	if (Pad::getIns()->isDown(PadCode::Z) && state == 0 && fadeCount >= 180) {
		state = 1;
		fadeCount = 0;
	}
	if (state == 1 && fadeCount >= 180) {
		implRequestScene->requestScene(SCENE_PLAY);
	}
	if (fadeCount < 180) {
		++fadeCount;
	}

}


/// <summary>
/// シーンの描画
/// </summary>
void TitleScene::render() {
	RenderManager* render_manager = RenderManager::getIns();
	render_manager->changeScreen(ScreenType::MapScreen);
	map->draw();
	render_manager->changeScreen(ScreenType::LightAlphaScreen);
	if (state == 0) {
		DrawRotaGraph(SCREEN_CENTER_X, SCREEN_CENTER_Y, (std::min)(fadeCount / 180.0f*6.0f, 6.0f), 0.0f, ResourceManager::getIns()->getTexture(TextureID::TEXTURE_LIGHT1)->getResource(), true);
	}
	else {
		DrawRotaGraph(SCREEN_CENTER_X, SCREEN_CENTER_Y, (std::max)((180-fadeCount) / 180.0f*6.0f, 0.0f), 0.0f, ResourceManager::getIns()->getTexture(TextureID::TEXTURE_LIGHT1)->getResource(), true);
	}
	render_manager->changeScreen(ScreenType::MapScreen);
	DrawRotaGraph(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.5f, 0.0f, ResourceManager::getIns()->getTexture(TEXTURE_TITLE)->getResource(), true);
	
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
void TitleScene::finalize() {
	ShareDataManager::getIns()->setMap(std::move(map));
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
