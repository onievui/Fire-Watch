#include "TitleScene.h"
#include "Pad.h"
#include "ResourceManager.h"
#include "Sound.h"
#include "GameMain.h"

/// <summary>
/// �V�[���؂�ւ��C���^�t�F�[�X�̓o�^
/// </summary>
/// <param name="_impl">���X�i�[�ւ̃|�C���^</param>
TitleScene::TitleScene(RequestSceneListener* _impl) 
	: AbstractScene(_impl) {
	initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TitleScene::~TitleScene() {

}

/// <summary>
/// �V�[���̏�����
/// </summary>
void TitleScene::initialize() {
	ResourceManager::getIns()->load(SCENE_TITLE);
	SoundPlayer::getIns()->reset();
}

/// <summary>
/// �V�[���̍X�V
/// </summary>
void TitleScene::update() {
	if (Pad::getIns()->isDown(PadCode::Z)) {
		implRequestScene->requestScene(SCENE_PLAY);
	}
}


/// <summary>
/// �V�[���̕`��
/// </summary>
void TitleScene::render() {
	//DrawRotaGraph(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.5f, 0.0f, ResourceManager::getIns()->getTexture(TEXTURE_TITLE)->getResource(), true);
	//DrawFormatStringF(SCREEN_CENTER_X - GetDrawFormatStringWidth("press Z key") / 2.f, SCREEN_CENTER_Y + 100, COLOR_WHITE, "press Z key");
}

/// <summary>
/// �V�[���̏I������
/// </summary>
void TitleScene::finalize() {

}

/// <summary>
/// �V�[����������
/// </summary>
/// <param name="_impl">�C���^�t�F�[�X�ւ̃|�C���^</param>
/// <returns>
/// �V�[���I�u�W�F�N�g
/// </returns>
std::unique_ptr<AbstractScene> TitleScene::create(RequestSceneListener* _impl) {
	return std::move(std::make_unique<TitleScene>(_impl));
}
