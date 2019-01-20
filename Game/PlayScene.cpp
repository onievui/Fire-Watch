#include "PlayScene.h"
#include "ShareDataManager.h"
#include "ResourceManager.h"
#include "Sound.h"
#include "RenderManager.h"
#include "ScreenInfo.h"
#include "MessageManager.h"
#include "Collision.h"


/// <summary>
/// �V�[���؂�ւ��C���^�t�F�[�X�̓o�^
/// </summary>
/// <param name="_impl">���X�i�[�ւ̃|�C���^</param>
PlayScene::PlayScene(RequestSceneListener* _impl) 
	: AbstractScene(_impl) {
	initialize();
	RenderManager::getIns()->addScreen(ScreenType::MapScreen, MakeScreen(SCREEN_WIDTH, SCREEN_HEIGHT, TRUE), Vector2(0, 0));
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
	//�}�b�v�Ǘ��N���X�̐���
	map = std::make_unique<Map>();
	message_manager->add(map.get());
	//�v���C���[�̐���
	player = std::make_unique<Player>();
	message_manager->add(player.get());
	//�t�B�[���h�I�u�W�F�N�g�Ǘ��N���X�̐���
	fieldObjectManager = std::make_unique<FieldObjectManager>();
	message_manager->add(fieldObjectManager.get());

}

/// <summary>
/// �V�[���̍X�V
/// </summary>
void PlayScene::update() {
	//�e�I�u�W�F�N�g�̍X�V
	player->update();
	fieldObjectManager->update();
	map->update();

	//�����蔻�菈��
	Collision collision;
	collision.update();
}


/// <summary>
/// �V�[���̕`��
/// </summary>
void PlayScene::render() {
	RenderManager* render_manager = RenderManager::getIns();
	//�`�����}�b�v�ɂ���
	render_manager->changeScreen(ScreenType::MapScreen);
	map->draw();
	fieldObjectManager->draw();
	player->draw();
	render_manager->flipScreen();
	render_manager->clearScreen(ScreenType::MapScreen);


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
