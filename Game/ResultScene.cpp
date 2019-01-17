#include "ResultScene.h"
#include "Pad.h"
#include "ShareDataManager.h"
#include "GameMain.h"


/// <summary>
/// �V�[���؂�ւ��C���^�t�F�[�X�̓o�^
/// </summary>
/// <param name="_impl">���X�i�[�ւ̃|�C���^</param>
ResultScene::ResultScene(RequestSceneListener* _impl) 
	: AbstractScene(_impl) {
	initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ResultScene::~ResultScene() {

}

/// <summary>
/// �V�[���̏�����
/// </summary>
void ResultScene::initialize() {
}

/// <summary>
/// �V�[���̍X�V
/// </summary>
void ResultScene::update() {
	if (Pad::getIns()->isDown(PadCode::Z)) {
		implRequestScene->requestScene(SCENE_TITLE);
	}
	
}


/// <summary>
/// �V�[���̕`��
/// </summary>
void ResultScene::render() {
	//SetFontSize(30);
	//DrawFormatStringF(SCREEN_CENTER_X - GetDrawFormatStringWidth("SCORE : %d", ShareDataManager::getIns()->getScore()) / 2.f, 
	//	(float)SCREEN_CENTER_Y, COLOR_WHITE, "SCORE : %d", ShareDataManager::getIns()->getScore());
	//SetFontSize(20);
	//DrawFormatStringF(SCREEN_CENTER_X - GetDrawFormatStringWidth("press Z key") / 2.f, SCREEN_CENTER_Y + 100.0f, COLOR_WHITE, "press Z key");
}

/// <summary>
/// �V�[���̏I������
/// </summary>
void ResultScene::finalize() {
}

/// <summary>
/// �V�[����������
/// </summary>
/// <param name="_impl">�C���^�t�F�[�X�ւ̃|�C���^</param>
/// <returns>
/// �V�[���I�u�W�F�N�g
/// </returns>
std::unique_ptr<AbstractScene> ResultScene::create(RequestSceneListener* _impl) {
	return std::move(std::make_unique<ResultScene>(_impl));
}
