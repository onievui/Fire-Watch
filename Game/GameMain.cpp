//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.cpp
//!
//! @brief  ゲーム関連のソースファイル
//!
//! @date   日付
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include "GameMain.h"
#include "LogoScene.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "ResultScene.h"
#include "Pad.h"
#include "Mouse.h"
#include "ShareDataManager.h"
#include "RenderManager.h"
#include "ShaderManager.h"
#include "Sound.h"



// <Gameクラス> ****************************************************************


// メンバ関数の定義 ========================================================
//------------------------------------------------------------------
//! @brief デフォルトコンストラクタ
//!
//! @param[in] なし
//------------------------------------------------------------------
Game::Game() {

}



//------------------------------------------------------------------
//! @brief デストラクタ
//------------------------------------------------------------------
Game::~Game() {

}



//----------------------------------------------------------------------
//! @brief ゲームの初期化処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void Game::initialize(void) {
	addScene(SCENE_LOGO, LogoScene::create);
	addScene(SCENE_TITLE, TitleScene::create);
	addScene(SCENE_PLAY, PlayScene::create);
	addScene(SCENE_RESULT, ResultScene::create);
	nowScene = sceneFactoryMethods[SCENE_PLAY](this);
	nextScene = SCENE_NONE;
	ShareDataManager::getIns()->initialize();
	RenderManager::getIns()->addScreen(ScreenType::BackScreen, DX_SCREEN_BACK, Vector2(0, 0));
	ShaderManager::getIns();
}


//----------------------------------------------------------------------
//! @brief ゲームの更新処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void Game::update(void) {
	Pad::getIns()->update();
	Mouse::getIns()->update();
	SoundPlayer::getIns()->playSound();
	SoundPlayer::getIns()->playMusic();
	if (nextScene != SCENE_NONE) {
		changeScene();
	}
	nowScene->update();
}



//----------------------------------------------------------------------
//! @brief ゲームの描画処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void Game::render(void) {
	nowScene->render();
}



//----------------------------------------------------------------------
//! @brief ゲームの終了処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void Game::finalize(void) {

}

//----------------------------------------------------------------------
//! @brief シーンの切り替え要求
//!
//! @param[in] _id 要求するシーンID
//!
//! @return なし
//----------------------------------------------------------------------
void Game::requestScene(const SceneID _id) {
	if (_id <= SCENE_NONE || _id >= SCENE_NUM) {
		MessageBox(NULL, "シーンの切り替え要求で不正な値が渡されました", "", MB_OK);
		return;
	}
	nextScene = _id;
}

//----------------------------------------------------------------------
//! @brief シーンの追加
//!
//! @param[in] _id 追加するシーンID
//!                   _scene_factory_method シーン生成関数
//!
//! @return なし
//----------------------------------------------------------------------
void Game::addScene(const SceneID _id, SceneFactoryMethod _scene_factory_method) {
	if (_id <= SCENE_NONE || _id >= SCENE_NUM) {
		MessageBox(NULL, "シーンの追加で不正なシーンIDが渡されました", "", MB_OK);
		return;
	}
	if (_scene_factory_method == nullptr) {
		MessageBox(NULL, "シーンの追加で不正な生成関数が渡されました", "", MB_OK);
		return;
	}

	sceneFactoryMethods[_id] = _scene_factory_method;
}

//----------------------------------------------------------------------
//! @brief シーンの切り替え処理
//!
//! @param[in] _id 次のシーンID
//!
//! @return なし
//----------------------------------------------------------------------
void Game::changeScene(void) {
	nowScene->finalize();
	if (nextScene <= SCENE_NONE || nextScene >= SCENE_NUM) {
		MessageBox(NULL, "シーンの追切り替え処理で不正なシーンIDが渡されました", "", MB_OK);
		return;
	}
	nowScene = sceneFactoryMethods[nextScene](this);
	nextScene = SCENE_NONE;
}
