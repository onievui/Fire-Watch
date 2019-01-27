#include "LogoScene.h"
#include "Pad.h"
#include "ResourceManager.h"
#include "GameMain.h"

/// <summary>
/// �V�[���؂�ւ��C���^�t�F�[�X�̓o�^
/// </summary>
/// <param name="_impl">���X�i�[�ւ̃|�C���^</param>
LogoScene::LogoScene(RequestSceneListener* _impl) 
	: AbstractScene(_impl) {
	initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
LogoScene::~LogoScene() {

}

/// <summary>
/// �V�[���̏�����
/// </summary>
void LogoScene::initialize() {
	ResourceManager::getIns()->load(SCENE_LOGO);
	state = 0;
	count = 0;
}

/// <summary>
/// �V�[���̍X�V
/// </summary>
void LogoScene::update() {
	//Z�L�[�ŃX�L�b�v
	if (Pad::getIns()->isDown(PadCode::Z)) {
		count = 270;
		state = 2;
	}

	//���S�\�����ԓ��Ȃ�J�E���^�𑝂₷
	if (count < 270) {
		count++;
	}
	//1�ڂ̃��S���\�����I�������2�ڂ�\������
	else if (state == 0) {
		count = 0;
		state = 1;
	}
	//�^�C�g���V�[���ɑJ�ڂ���
	else {
		implRequestScene->requestScene(SCENE_TITLE);
	}
}


/// <summary>
/// �V�[���̕`��
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
/// �V�[���̏I������
/// </summary>
void LogoScene::finalize() {
	ResourceManager::getIns()->release();
}

/// <summary>
/// �V�[����������
/// </summary>
/// <param name="_impl">�C���^�t�F�[�X�ւ̃|�C���^</param>
/// <returns>
/// �V�[���I�u�W�F�N�g
/// </returns>
std::unique_ptr<AbstractScene> LogoScene::create(RequestSceneListener * _impl) {
	return std::move(std::make_unique<LogoScene>(_impl));
}
