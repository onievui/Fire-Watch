#include "PlayScene.h"
#include "ShareDataManager.h"
#include "ResourceManager.h"
#include "Sound.h"
#include "RenderManager.h"
#include "ScreenInfo.h"
#include "MessageManager.h"
#include "Collision.h"
#include "ShaderManager.h"
#include "MouseEventManager.h"
#include "ErrorMessage.h"


/// <summary>
/// シーン切り替えインタフェースの登録
/// </summary>
/// <param name="_impl">リスナーへのポインタ</param>
PlayScene::PlayScene(RequestSceneListener* _impl) 
	: AbstractScene(_impl) {
	initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
PlayScene::~PlayScene() {
}

/// <summary>
/// シーンの初期化
/// </summary>
void PlayScene::initialize() {
	ResourceManager::getIns()->load(SCENE_PLAY);
	SoundPlayer::getIns()->reset();
	MessageManager* message_manager = MessageManager::getIns();
	message_manager->add(this);
	//状態の初期化
	state = PlaySceneState::PLAYING;
	waitCount = 0;
	killCount = 0;
	liveTime = 0;
	//マップ管理クラスの生成
	map = std::move(ShareDataManager::getIns()->getMap());
	message_manager->add(map.get());
	//プレイヤーの生成
	player = std::make_unique<Player>();
	message_manager->add(player.get());
	//敵管理クラスの生成
	enemyManager = std::make_unique<EnemyManager>();
	message_manager->add(enemyManager.get());
	//フィールドオブジェクト管理クラスの生成
	fieldObjectManager = std::make_unique<FieldObjectManager>();
	message_manager->add(fieldObjectManager.get());
	//矢管理クラスの生成
	arrowManager = std::make_unique<ArrowManager>();
	message_manager->add(arrowManager.get());
	//マウスイベント管理クラスの生成
	mouseEventManager = std::make_unique<MouseEventManager>();
	//使用するシェーダーの設定
	ShaderManager::getIns()->setShader(ShaderID::SHADER_LIGHT);

}

/// <summary>
/// シーンの更新
/// </summary>
void PlayScene::update() {
	switch (state) {
	case PlayScene::PlaySceneState::PLAYING:
		updatePlaying();
		break;
	case PlayScene::PlaySceneState::PLAYER_DEAD:
		updatePlayerDead();
		break;
	case PlayScene::PlaySceneState::TENT_DESTROYED:
		updateTentDestroyed();
		break;
	default:
		ErrorMessage("プレイシーンの状態が不正です");
			break;
	}

	//シェーダーの更新
	ShaderManager::getIns()->update();
}


/// <summary>
/// シーンの描画
/// </summary>
void PlayScene::render() {
	RenderManager* render_manager = RenderManager::getIns();
	//描画先をマップにする
	render_manager->changeScreen(ScreenType::LightAlphaScreen);
	//DrawFillBox(0, 0, Map::GRID_COLS*Map::DEFAULT_GRID_SIZE, Map::GRID_ROWS*Map::DEFAULT_GRID_SIZE, ColorCode::COLOR_BLACK);
	render_manager->changeScreen(ScreenType::MapScreen);
	//ライティングに影響される描画
	map->draw();
	fieldObjectManager->draw();
	enemyManager->draw();
	arrowManager->draw();
	player->drawFlashLight();

	//シェーダーの使用(ライトの反映)
	ShaderManager::getIns()->draw();

	//ライトデータの更新
	map->updateLightData();

	//ライティングに影響しない描画
	player->draw();

	if (state == PlaySceneState::PLAYER_DEAD || (state == PlaySceneState::TENT_DESTROYED && waitCount >= 60)) {
		fadeOut();
	}

	//マップを裏画面に反映
	render_manager->flipScreen();
	render_manager->clearScreen(ScreenType::MapScreen);
	render_manager->clearScreen(ScreenType::LightAlphaScreen);

}

/// <summary>
/// シーンの終了処理
/// </summary>
void PlayScene::finalize() {
	MessageManager::getIns()->reset();
	//ResourceManager::getIns()->release();
	SoundPlayer::getIns()->stopAll();
	SoundPlayer::getIns()->reset();
	ShareDataManager::getIns()->setMap(std::move(map));
	ShareDataManager::getIns()->setPlayData(killCount, liveTime);
	//使用するシェーダーの設定
	//ShaderManager::getIns()->setShader(ShaderID::SHADER_NONE);
}

/// <summary>
/// シーン生成処理
/// </summary>
/// <param name="_impl">インタフェースへのポインタ</param>
/// <returns>
/// シーンオブジェクト
/// </returns>
std::unique_ptr<AbstractScene> PlayScene::create(RequestSceneListener* _impl) {
	return std::move(std::make_unique<PlayScene>(_impl));
}

/// <summary>
/// メッセージの受け取り
/// </summary>
/// <param name="_type">メッセージタイプ</param>
/// <param name="_out">出力</param>
/// <param name="_in">入力</param>
/// <returns>
/// 有効なメッセージを受け取ったかどうか
/// </returns>
bool PlayScene::getMessage(const MessageType _type, void* _out, void* _in) {
	switch (_type) {
	case MessageType::PLAYER_DEAD:
		state = PlaySceneState::PLAYER_DEAD;
		return true;
	case MessageType::TENT_DESTROYED:
		state = PlaySceneState::TENT_DESTROYED;
		return true;
	case MessageType::ENEMY_KILLED:
		++killCount;
		return true;
	default:
		break;
	}
	return false;
}

/// <summary>
/// プレイ中の更新処理
/// </summary>
void PlayScene::updatePlaying() {
	//各オブジェクトの更新
	player->update();
	enemyManager->update();
	fieldObjectManager->update();
	arrowManager->update();
	map->update();

	//マウスイベント処理
	mouseEventManager->update();

	//当たり判定処理
	Collision collision;
	collision.update();

	++liveTime;
}

/// <summary>
/// プレイヤー死亡時の更新処理
/// </summary>
void PlayScene::updatePlayerDead() {
	player->update();
	if (waitCount >= 180) {
		implRequestScene->requestScene(SceneID::SCENE_RESULT);
	}
	++waitCount;
}

/// <summary>
/// テント破壊時の更新処理
/// </summary>
void PlayScene::updateTentDestroyed() {
	if (waitCount < 60) {
		float rate = waitCount / 60.0f;
		Vector2 tent_pos = MessageManager::getIns()->sendMessage<Vector2>(MessageType::GET_TENT_POS);
		Vector2 player_pos = MessageManager::getIns()->sendMessage<Vector2>(MessageType::GET_PLAYER_POS);
		Vector2 screen_pos = tent_pos * rate + player_pos * (1 - rate);
		screen_pos.x = ClampT(screen_pos.x - SCREEN_CENTER_X, 0.f, (float)Map::GRID_COLS*Map::DEFAULT_GRID_SIZE - SCREEN_WIDTH);
		screen_pos.y = ClampT(screen_pos.y - SCREEN_CENTER_Y, 0.f, (float)Map::GRID_ROWS*Map::DEFAULT_GRID_SIZE - SCREEN_HEIGHT);
		RenderManager::getIns()->setScreenOffset(ScreenType::MapScreen, screen_pos);
		RenderManager::getIns()->setScreenOffset(ScreenType::LightAlphaScreen, screen_pos);
	}
	if (waitCount >= 240) {
		implRequestScene->requestScene(SceneID::SCENE_RESULT);
	}
	++waitCount;
}

/// <summary>
/// フェードアウト処理
/// </summary>
void PlayScene::fadeOut() {
	RenderManager* render_manager = RenderManager::getIns();
	render_manager->clearScreen(ScreenType::LightAlphaScreen);
	render_manager->changeScreen(ScreenType::LightAlphaScreen);
	int fade_count = waitCount - (state == PlaySceneState::TENT_DESTROYED ? 60 : 0);
	DrawRotaGraph(SCREEN_CENTER_X, SCREEN_CENTER_Y, (std::max)((180 - fade_count) / 180.0f*20.0f, 0.0f), 0.0f,
		ResourceManager::getIns()->getTexture(TextureID::TEXTURE_LIGHT1)->getResource(), true);
	render_manager->changeScreen(ScreenType::MapScreen);

	//シェーダーの使用(ライトの反映)
	ShaderManager::getIns()->draw();
}
