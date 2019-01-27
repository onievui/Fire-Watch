#include "ResultScene.h"
#include "Pad.h"
#include "ShareDataManager.h"
#include "GameMain.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "ShaderManager.h"


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
	map = std::move(ShareDataManager::getIns()->getMap());
	state = 0;
	fadeCount = 0;

}

/// <summary>
/// �V�[���̍X�V
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
/// �V�[���̕`��
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


	//�V�F�[�_�[�̎g�p(���C�g�̔��f)
	ShaderManager::getIns()->draw();

	//�}�b�v�𗠉�ʂɔ��f
	render_manager->flipScreen();

	render_manager->changeScreen(ScreenType::BackScreen);
	if (state == 0 && fadeCount >= 180) {
		DrawFormatStringF(SCREEN_CENTER_X - GetDrawFormatStringWidth("press Z key") / 2.f, SCREEN_CENTER_Y + 100, COLOR_WHITE, "press Z key");
	}


	render_manager->clearScreen(ScreenType::MapScreen);
	render_manager->clearScreen(ScreenType::LightAlphaScreen);
}

/// <summary>
/// �V�[���̏I������
/// </summary>
void ResultScene::finalize() {
	ResourceManager::getIns()->release();
	RenderManager::getIns()->deleteScreen(ScreenType::MapScreen);
	RenderManager::getIns()->deleteScreen(ScreenType::LightAlphaScreen);
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
