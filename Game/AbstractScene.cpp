#include "AbstractScene.h"


/// <summary>
/// �V�[���؂�ւ��C���^�t�F�[�X�̓o�^
/// </summary>
/// <param name="_impl">���X�i�[�ւ̃|�C���^</param>
AbstractScene::AbstractScene(RequestSceneListener *_impl)
	: implRequestScene(_impl) {
}

