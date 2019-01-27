#include "TitleScene.h"
#include "Pad.h"
#include "ResourceManager.h"
#include "Sound.h"
#include "GameMain.h"
#include "ShaderManager.h"
#include "ShareDataManager.h"
#include "RenderManager.h"


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
/// �V�[���̍X�V
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
/// �V�[���̕`��
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
void TitleScene::finalize() {
	ShareDataManager::getIns()->setMap(std::move(map));
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
