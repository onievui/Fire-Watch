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
	RenderManager::getIns()->addScreen(ScreenType::MapScreen, MakeScreen(SCREEN_WIDTH, SCREEN_HEIGHT, TRUE), Vector2(0, 0));
	RenderManager::getIns()->addScreen(ScreenType::LightAlphaScreen, MakeScreen(SCREEN_WIDTH, SCREEN_HEIGHT, TRUE), Vector2(0, 0));
	RenderManager::getIns()->changeScreen(ScreenType::MapScreen);
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
	//�}�b�v�Ǘ��N���X�̐���
	map = std::make_unique<Map>();
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
	ResourceManager::getIns()->release();
	SoundPlayer::getIns()->stopAll();
	SoundPlayer::getIns()->reset();
	RenderManager::getIns()->deleteScreen(ScreenType::MapScreen);
	RenderManager::getIns()->deleteScreen(ScreenType::LightAlphaScreen);
	//�g�p����V�F�[�_�[�̐ݒ�
	ShaderManager::getIns()->setShader(ShaderID::SHADER_NONE);
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
}

/// <summary>
/// �v���C���[���S���̍X�V����
/// </summary>
void PlayScene::updatePlayerDead() {

}

/// <summary>
/// �e���g�j�󎞂̍X�V����
/// </summary>
void PlayScene::updateTentDestroyed() {
}
