//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.cpp
//!
//! @brief  �Q�[���֘A�̃\�[�X�t�@�C��
//!
//! @date   ���t
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
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



// <Game�N���X> ****************************************************************


// �����o�֐��̒�` ========================================================
//------------------------------------------------------------------
//! @brief �f�t�H���g�R���X�g���N�^
//!
//! @param[in] �Ȃ�
//------------------------------------------------------------------
Game::Game() {

}



//------------------------------------------------------------------
//! @brief �f�X�g���N�^
//------------------------------------------------------------------
Game::~Game() {

}



//----------------------------------------------------------------------
//! @brief �Q�[���̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
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
//! @brief �Q�[���̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
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
//! @brief �Q�[���̕`�揈��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void Game::render(void) {
	nowScene->render();
}



//----------------------------------------------------------------------
//! @brief �Q�[���̏I������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void Game::finalize(void) {

}

//----------------------------------------------------------------------
//! @brief �V�[���̐؂�ւ��v��
//!
//! @param[in] _id �v������V�[��ID
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void Game::requestScene(const SceneID _id) {
	if (_id <= SCENE_NONE || _id >= SCENE_NUM) {
		MessageBox(NULL, "�V�[���̐؂�ւ��v���ŕs���Ȓl���n����܂���", "", MB_OK);
		return;
	}
	nextScene = _id;
}

//----------------------------------------------------------------------
//! @brief �V�[���̒ǉ�
//!
//! @param[in] _id �ǉ�����V�[��ID
//!                   _scene_factory_method �V�[�������֐�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void Game::addScene(const SceneID _id, SceneFactoryMethod _scene_factory_method) {
	if (_id <= SCENE_NONE || _id >= SCENE_NUM) {
		MessageBox(NULL, "�V�[���̒ǉ��ŕs���ȃV�[��ID���n����܂���", "", MB_OK);
		return;
	}
	if (_scene_factory_method == nullptr) {
		MessageBox(NULL, "�V�[���̒ǉ��ŕs���Ȑ����֐����n����܂���", "", MB_OK);
		return;
	}

	sceneFactoryMethods[_id] = _scene_factory_method;
}

//----------------------------------------------------------------------
//! @brief �V�[���̐؂�ւ�����
//!
//! @param[in] _id ���̃V�[��ID
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void Game::changeScene(void) {
	nowScene->finalize();
	if (nextScene <= SCENE_NONE || nextScene >= SCENE_NUM) {
		MessageBox(NULL, "�V�[���̒ǐ؂�ւ������ŕs���ȃV�[��ID���n����܂���", "", MB_OK);
		return;
	}
	nowScene = sceneFactoryMethods[nextScene](this);
	nextScene = SCENE_NONE;
}
