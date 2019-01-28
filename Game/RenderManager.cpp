#include "ErrorMessage.h"
#include "RenderManager.h"



/// <summary>
/// �R���X�g���N�^
/// </summary>
RenderManager::RenderManager() 
	: screens()
	, offsets()
	, currentScreenType((ScreenType)DX_SCREEN_BACK) {
	screensIndex.fill(-1);
}

/// <summary>
/// �X�N���[���̒ǉ�
/// </summary>
/// <param name="_screen_type">�X�N���[���^�C�v</param>
/// <param name="_screen">�X�N���[��</param>
/// <param name="_offset">�I�t�Z�b�g</param>
/// <returns>
/// �ǉ��ɐ����������ǂ���
/// </returns>
bool RenderManager::addScreen(const ScreenType _screen_type, const int _screen, const Vector2& _offset) {
	//�͈͊O���ǂ���
	if (_screen_type < 0 || _screen_type >= ScreenType::Num) {
		return false;
	}
	//�ǉ��ς݂��ǂ���
	if (screensIndex[_screen_type] != -1) {
		return false;
	}
	//�ǉ�����
	screensIndex[_screen_type] = screens.size();
	screens.emplace_back(_screen);
	offsets.emplace_back(_offset);
	return true;
}

/// <summary>
/// �X�N���[���̐؂�ւ�
/// </summary>
/// <param name="_screen_type">�X�N���[���^�C�v</param>
/// <returns>
/// �؂�ւ��ɐ����������ǂ���
/// </returns>
bool RenderManager::changeScreen(const ScreenType _screen_type) {
	if (!canUseScreenType(_screen_type)) {
		ErrorMessage("�X�N���[���̐؂�ւ��Ɏ��s���܂���");
		return false;
	}
	SetDrawScreen(screens[screensIndex[_screen_type]]);
	currentScreenType = _screen_type;
	return true;
}

/// <summary>
/// ��ʂ̔��f
/// </summary>
void RenderManager::flipScreen() {
	SetDrawScreen(DX_SCREEN_BACK);
	DrawGraph(0, 0, screens[screensIndex[currentScreenType]], TRUE);
	SetDrawScreen(screens[screensIndex[currentScreenType]]);
}

/// <summary>
/// �X�N���[���̎擾
/// </summary>
/// <param name="_screen_type">�X�N���[���^�C�v</param>
/// <returns>
/// �X�N���[��
/// </returns>
int RenderManager::getScreen(const ScreenType _screen_type) {
	if (!canUseScreenType(_screen_type)) {
		ErrorMessage("�X�N���[���̎擾�Ɏ��s���܂���");
		return -1;
	}
	return screens[screensIndex[_screen_type]];
}

/// <summary>
/// �I�t�Z�b�g�̐ݒ�
/// </summary>
/// <param name="_screen_type">�X�N���[���^�C�v</param>
/// <param name="_offset">�I�t�Z�b�g</param>
/// <returns>
/// �I�t�Z�b�g�̐ݒ�ɐ����������ǂ���
/// </returns>
bool RenderManager::setScreenOffset(const ScreenType _screen_type, const Vector2& _offset) {
	if (!canUseScreenType(_screen_type)) {
		ErrorMessage("�I�t�Z�b�g�̐ݒ�Ɏ��s���܂���");
		return false;
	}
	offsets[screensIndex[_screen_type]] = _offset;
	return true;
}

/// <summary>
/// �I�t�Z�b�g�̎擾
/// </summary>
/// <param name="_screen_type">�X�N���[���^�C�v</param>
/// <returns>
/// �I�t�Z�b�g
/// </returns>
Vector2 RenderManager::getScreenOffset(const ScreenType _screen_type) {
	if (!canUseScreenType(_screen_type)) {
		ErrorMessage("�I�t�Z�b�g�̎擾�Ɏ��s���܂���");
		return Vector2();
	}
	return offsets[screensIndex[_screen_type]];
}

/// <summary>
/// ��ʂ̃N���A
/// </summary>
/// <param name="_screen_type">�X�N���[���^�C�v</param>
void RenderManager::clearScreen(const ScreenType _screen_type) {
	if (!canUseScreenType(_screen_type)) {
		ErrorMessage("�L���łȂ��X�N���[�����N���A���悤�Ƃ��܂���");
	}
	else {
		if (currentScreenType == _screen_type) {
			ClearDrawScreen();
		}
		else {
			ScreenType pre_screen_type = currentScreenType;
			if (changeScreen(_screen_type)) {
				ClearDrawScreen();
				currentScreenType = pre_screen_type;
			}
		}
	}
}

/// <summary>
/// �X�N���[���̍폜
/// </summary>
/// <param name="_screen_type">�X�N���[���^�C�v</param>
/// <returns>
/// �폜�ɐ����������ǂ���
/// </returns>
bool RenderManager::deleteScreen(const ScreenType _screen_type) {
	if (!canUseScreenType(_screen_type)) {
		ErrorMessage("�L���łȂ��X�N���[�����폜���悤�Ƃ��܂���");
		return false;
	}
	if (screens[screensIndex[_screen_type]] == DX_SCREEN_BACK) {
		return false;
	}

	DeleteGraph(screens[screensIndex[_screen_type]]);
	//�Ō���̃f�[�^���폜����ꍇ
	//if (screensIndex[_screen_type] == screens.size() - 1) {
	//	screensIndex[_screen_type] = -1;
	//	screens.erase(screens.end());
	//	offsets.erase(offsets.end());
	//}
	////�Ō���łȂ��f�[�^���폜����ꍇ
	//else {
		int delete_index = screensIndex[_screen_type];
		//�ʒu�����炷
		for (auto& index : screensIndex) {
			if (index > delete_index) {
				--index;
			}
		}
		screensIndex[_screen_type] = -1;
		screens.erase(screens.begin() + delete_index);
		offsets.erase(offsets.begin() + delete_index);
	//}

	//�I�𒆂̃X�N���[�����폜�����ꍇ�̏���
	if (currentScreenType == _screen_type) {
		currentScreenType = ScreenType(-1);
		SetDrawScreen(DX_SCREEN_BACK);
	}
	return true;
}

/// <summary>
/// �g�p�\�ȂȃX�N���[���^�C�v���ǂ���
/// </summary>
/// <param name="_screen_type">�X�N���[���^�C�v</param>
/// <returns>
/// �g�p�\���ǂ���
/// </returns>
bool RenderManager::canUseScreenType(const ScreenType _screen_type) {
	if (_screen_type < 0 || _screen_type >= ScreenType::Num) {
		return false;
	}
	if (screensIndex[_screen_type] == -1) {
		return false;
	}
	return true;
}


void RenderManager::drawCircleAA(const float _x, const float _y, const float _r, const int _pos_num, const unsigned int _color, const int _fill_flag, const float _thickness) {
	Vector2 offset = offsets[screensIndex[currentScreenType]];
	DrawCircleAA(_x - offset.x, _y - offset.y, _r, _pos_num, _color, _fill_flag, _thickness);
}

void RenderManager::drawExtendGraphF(const float _x1, const float _y1, const float _x2, const float _y2, const int _handle, const int _trans_flag) const {
	Vector2 offset = offsets[screensIndex[currentScreenType]];
	DrawExtendGraphF(_x1 - offset.x, _y1 - offset.y, _x2 - offset.x, _y2 - offset.y, _handle, _trans_flag);
}

void RenderManager::drawRotaGraphF(const float _x, const float _y, const float _exrate, const float _angle, int _handle, const int _trans_flag, const int _reverse_x_flag, const int _reverse_y_flag) const {
	Vector2 offset = offsets[screensIndex[currentScreenType]];
	DrawRotaGraphF(_x - offset.x, _y - offset.y, _exrate, _angle, _handle, _trans_flag, _reverse_x_flag, _reverse_y_flag);
}

void RenderManager::drawRotaGraph(const float _x, const float _y, const float _exrate, const float _angle, int _handle, const int _trans_flag, const int _reverse_x_flag, const int _reverse_y_flag) const {
	Vector2 offset = offsets[screensIndex[currentScreenType]];
	DrawRotaGraph((int)(_x - offset.x), (int)(_y - offset.y), _exrate, _angle, _handle, _trans_flag, _reverse_x_flag, _reverse_y_flag);
}