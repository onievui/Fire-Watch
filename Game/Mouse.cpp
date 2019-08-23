#include "Mouse.h"



/// <summary>
/// �R���X�g���N�^
/// </summary>
Mouse::Mouse() {
	reset();
}



/// <summary>
/// �}�E�X�̓��͏�Ԃ̍X�V
/// </summary>
void Mouse::update() {
	int x, y, mouseInput, getWheel;

	//�}�E�X�̓��͏�Ԃ̎擾
	mouseInput = GetMouseInput();
	//�z�C�[���̓��͏�Ԃ̎擾
	getWheel = GetMouseWheelRotVol();
	//�}�E�X���W�̎擾
	GetMousePoint(&x, &y);
	//���͏�Ԃ̍X�V
	for (int i = 0; i < MOUSE_INPUT_NUM; ++i) {
		if (mouseInput & MouseCode(i)) {
			if (mouseStatePress[i] < 0) {
				mouseStatePress[i] = 0;
			}
			++mouseStatePress[i];
		}
		else {
			if (mouseStatePress[i] > 0) {
				mouseStatePress[i] = 0;
			}
			--mouseStatePress[i];
		}
	}
	//�}�E�X���W�̍X�V
	mousePos = Vector2((float)x, (float)y);
}

/// <summary>
/// �}�E�X�̓��͏�Ԃ̏�����
/// </summary>
void Mouse::reset() {
	mouseStatePress.fill(-1);
	mousePos = { 0,0 };
	wheel = 0;
}

/// <summary>
/// �}�E�X�J�[�\���̕\���ݒ�
/// </summary>
/// <param name="_is_use">�}�E�X�J�[�\����\�����邩�ǂ���</param>
/// <returns>
/// 0 : ����
/// -1 : �G���[
/// </returns>
int Mouse::setMouseDispFlag(const bool _is_use) {
	return SetMouseDispFlag(_is_use);
}

/// <summary>
/// �}�E�X���W�̎擾
/// </summary>
/// <returns>
/// �}�E�X���W
/// </returns>
Vector2 Mouse::getMousePos() const {
	return mousePos;
}

/// <summary>
/// �}�E�X���W�̐ݒ�
/// </summary>
/// <param name="_pos">�ړ���̍��W</param>
void Mouse::setMousePos(const Vector2& _pos) {
	mousePos = _pos;
}

/// <summary>
/// �}�E�X�z�C�[���̉�]�ʂ̎擾
/// </summary>
/// <returns>
/// �}�E�X�z�C�[���̉�]��
/// </returns>
int Mouse::getMouseWheelRotVol() const {
	return wheel;
}

/// <summary>
/// ����{�^���̓��͏�Ԃ�Ԃ�
/// </summary>
/// <param name="_id">����{�^����ID</param>
/// <returns>
/// ����{�^���̓��͏��
/// </returns>
int Mouse::state(const MouseCode _id) const {
	return mouseStatePress[_id];
}

/// <summary>
/// ����{�^���̉�����Ă��鎞�Ԃ�Ԃ�
/// </summary>
/// <param name="_id">����{�^����ID</param>
/// <returns>
/// ����{�^���̓��̓t���[����
/// </returns>
int Mouse::statePress(const MouseCode _id) const {
	return mouseStatePress[_id] > 0 ? mouseStatePress[_id] : 0;
}

/// <summary>
/// ����{�^���̉�����Ă��Ȃ����Ԃ�Ԃ�
/// </summary>
/// <param name="_id">����{�^����ID</param>
/// <returns>
/// ����{�^�������͂���Ă��Ȃ��t���[����
/// </returns>
int Mouse::stateRelease(const MouseCode _id) const {
	return mouseStatePress[_id] < 0 ? -mouseStatePress[_id] : 0;
}

/// <summary>
/// ����̃{�^���������Ă��Ȃ���Ԃ��牟�������ǂ�����Ԃ�
/// </summary>
/// <param name="_id">����{�^����ID</param>
/// <returns>
/// true�F���������� false�F����������łȂ�
/// </returns>
bool Mouse::isDown(const MouseCode _id) const {
	return mouseStatePress[_id] == 1 ? true : false;
}

/// <summary>
/// ����̃{�^����������Ă����Ԃ��痣�������ǂ�����Ԃ�
/// </summary>
/// <param name="_id">����{�^����ID</param>
/// <returns>
/// true�F���������� false�F����������łȂ�
/// </returns>
bool Mouse::isUp(const MouseCode _id) const {
	return mouseStatePress[_id] == -1 ? true : false;
}

/// <summary>
/// �s����̃{�^���������Ă��Ȃ���Ԃ��牟�������ǂ�����Ԃ�
/// </summary>
/// <returns>
/// true�F���������� false�F����������łȂ�
/// </returns>
bool Mouse::isDownAny() const {
	for (auto &mouse_state : mouseStatePress) {
		if (mouse_state == 1) {
			return true;
		}
	}
	return false;
}

/// <summary>
/// 2�̓���{�^���̌ォ�牟����Ă���ق��𔻕ʂ���
/// </summary>
/// <param name="_id1">����{�^��1��ID</param>
/// <param name="_id2">����{�^��2��ID</param>
/// <returns>
/// later 0:�ǂ����������Ă��Ȃ� 1:��P���� 2:��Q����
/// </returns>
int Mouse::statePressLater(const MouseCode _id1, const MouseCode _id2) const {
	//�f�t�H���g�͉���������Ă��Ȃ����
	int later = 0;

	//�e�{�^���̓��͏��
	int mouse_state1, mouse_state2;

	mouse_state1 = mouseStatePress[_id1];
	mouse_state2 = mouseStatePress[_id2];

	if (mouse_state1 > 0) {	//��Ԗڂ�������Ă�����
		if (mouse_state2 > 0 && mouse_state2 < mouse_state1) {		//��Ԗڂ���ɉ�����Ă�����
			later = 2;
		}
		else {
			later = 1;
		}
	}
	else if (mouse_state2 > 0) {	//��Ԗڂ�������Ă�����
		later = 2;
	}

	return later;
}

/// <summary>
/// 4�̓���{�^���̌ォ�牟����Ă���ق��𔻕ʂ���
/// </summary>
/// <param name="_id1">����{�^��1��ID</param>
/// <param name="_id2">����{�^��2��ID</param>
/// <param name="_id3">����{�^��3��ID</param>
/// <param name="_id4">����{�^��4��ID</param>
/// <returns>
/// later 0:�������������Ă��Ȃ� 1:��P���� 2:��Q���� 3:��R���� 4:��S����
/// </returns>
int Mouse::statePressLater4(const MouseCode _id1, const MouseCode _id2, const MouseCode _id3, const MouseCode _id4) const {
	//�f�t�H���g�͉���������Ă��Ȃ����
	int later = 0;

	//�{�^���������ꂽ����
	int shortest = 999999;

	//�e�{�^���̓��͏��
	int mouse_state[4];

	mouse_state[0] = mouseStatePress[_id1];
	mouse_state[1] = mouseStatePress[_id2];
	mouse_state[2] = mouseStatePress[_id3];
	mouse_state[3] = mouseStatePress[_id4];

	for (int i = 0; i < 4; i++) {
		if (mouse_state[i] > 0 && mouse_state[i] < shortest) {
			later = i + 1;
			shortest = mouse_state[i];
		}
	}
	return later;
}



