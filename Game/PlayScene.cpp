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
/// �V�[���؂�ւ��C���^�t�F�[�X�̓o�^
/// </summary>
/// <param name="_impl">���X�i�[�ւ̃|�C���^</param>
PlayScene::PlayScene(RequestSceneListener* _impl) 
	: AbstractScene(_impl) {
	initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayScene::~PlayScene() {
}

/// <summary>
/// �V�[���̏�����
/// </summary>
void PlayScene::initialize() {
	ResourceManager::getIns()->load(SCENE_PLAY);
	SoundPlayer::getIns()->reset();
	MessageManager* message_manager = MessageManager::getIns();
	message_manager->add(this);
	//��Ԃ̏�����
	state = PlaySceneState::PLAYING;
	waitCount = 0;
	killCount = 0;
	liveTime = 0;
	//�}�b�v�Ǘ��N���X�̐���
	map = std::move(ShareDataManager::getIns()->getMap());
	message_manager->add(map.get());
	//�v���C���[�̐���
	player = std::make_unique<Player>();
	message_manager->add(player.get());
	//�G�Ǘ��N���X�̐���
	enemyManager = std::make_unique<EnemyManager>();
	message_manager->add(enemyManager.get());
	//�t�B�[���h�I�u�W�F�N�g�Ǘ��N���X�̐���
	fieldObjectManager = std::make_unique<FieldObjectManager>();
	message_manager->add(fieldObjectManager.get());
	//��Ǘ��N���X�̐���
	arrowManager = std::make_unique<ArrowManager>();
	message_manager->add(arrowManager.get());
	//�}�E�X�C�x���g�Ǘ��N���X�̐���
	mouseEventManager = std::make_unique<MouseEventManager>();
	//�g�p����V�F�[�_�[�̐ݒ�
	ShaderManager::getIns()->setShader(ShaderID::SHADER_LIGHT);

}

/// <summary>
/// �V�[���̍X�V
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
		ErrorMessage("�v���C�V�[���̏�Ԃ��s���ł�");
			break;
	}

	//�V�F�[�_�[�̍X�V
	ShaderManager::getIns()->update();
}


/// <summary>
/// �V�[���̕`��
/// </summary>
void PlayScene::render() {
	RenderManager* render_manager = RenderManager::getIns();
	//�`�����}�b�v�ɂ���
	render_manager->changeScreen(ScreenType::LightAlphaScreen);
	//DrawFillBox(0, 0, Map::GRID_COLS*Map::DEFAULT_GRID_SIZE, Map::GRID_ROWS*Map::DEFAULT_GRID_SIZE, ColorCode::COLOR_BLACK);
	render_manager->changeScreen(ScreenType::MapScreen);
	//���C�e�B���O�ɉe�������`��
	map->draw();
	fieldObjectManager->draw();
	enemyManager->draw();
	arrowManager->draw();
	player->drawFlashLight();

	//�V�F�[�_�[�̎g�p(���C�g�̔��f)
	ShaderManager::getIns()->draw();

	//���C�g�f�[�^�̍X�V
	map->updateLightData();

	//���C�e�B���O�ɉe�����Ȃ��`��
	player->draw();

	if (state == PlaySceneState::PLAYER_DEAD || (state == PlaySceneState::TENT_DESTROYED && waitCount >= 60)) {
		fadeOut();
	}

	//�}�b�v�𗠉�ʂɔ��f
	render_manager->flipScreen();
	render_manager->clearScreen(ScreenType::MapScreen);
	render_manager->clearScreen(ScreenType::LightAlphaScreen);

}

/// <summary>
/// �V�[���̏I������
/// </summary>
void PlayScene::finalize() {
	MessageManager::getIns()->reset();
	//ResourceManager::getIns()->release();
	SoundPlayer::getIns()->stopAll();
	SoundPlayer::getIns()->reset();
	ShareDataManager::getIns()->setMap(std::move(map));
	ShareDataManager::getIns()->setPlayData(killCount, liveTime);
	//�g�p����V�F�[�_�[�̐ݒ�
	//ShaderManager::getIns()->setShader(ShaderID::SHADER_NONE);
}

/// <summary>
/// �V�[����������
/// </summary>
/// <param name="_impl">�C���^�t�F�[�X�ւ̃|�C���^</param>
/// <returns>
/// �V�[���I�u�W�F�N�g
/// </returns>
std::unique_ptr<AbstractScene> PlayScene::create(RequestSceneListener* _impl) {
	return std::move(std::make_unique<PlayScene>(_impl));
}

/// <summary>
/// ���b�Z�[�W�̎󂯎��
/// </summary>
/// <param name="_type">���b�Z�[�W�^�C�v</param>
/// <param name="_out">�o��</param>
/// <param name="_in">����</param>
/// <returns>
/// �L���ȃ��b�Z�[�W���󂯎�������ǂ���
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
/// �v���C���̍X�V����
/// </summary>
void PlayScene::updatePlaying() {
	//�e�I�u�W�F�N�g�̍X�V
	player->update();
	enemyManager->update();
	fieldObjectManager->update();
	arrowManager->update();
	map->update();

	//�}�E�X�C�x���g����
	mouseEventManager->update();

	//�����蔻�菈��
	Collision collision;
	collision.update();

	++liveTime;
}

/// <summary>
/// �v���C���[���S���̍X�V����
/// </summary>
void PlayScene::updatePlayerDead() {
	player->update();
	if (waitCount >= 180) {
		implRequestScene->requestScene(SceneID::SCENE_RESULT);
	}
	++waitCount;
}

/// <summary>
/// �e���g�j�󎞂̍X�V����
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
/// �t�F�[�h�A�E�g����
/// </summary>
void PlayScene::fadeOut() {
	RenderManager* render_manager = RenderManager::getIns();
	render_manager->clearScreen(ScreenType::LightAlphaScreen);
	render_manager->changeScreen(ScreenType::LightAlphaScreen);
	int fade_count = waitCount - (state == PlaySceneState::TENT_DESTROYED ? 60 : 0);
	DrawRotaGraph(SCREEN_CENTER_X, SCREEN_CENTER_Y, (std::max)((180 - fade_count) / 180.0f*20.0f, 0.0f), 0.0f,
		ResourceManager::getIns()->getTexture(TextureID::TEXTURE_LIGHT1)->getResource(), true);
	render_manager->changeScreen(ScreenType::MapScreen);

	//�V�F�[�_�[�̎g�p(���C�g�̔��f)
	ShaderManager::getIns()->draw();
}
