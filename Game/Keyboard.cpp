#include "Keyboard.h"



/// <summary>
/// �R���X�g���N�^
/// </summary>
Keyboard::Keyboard() {
	reset();
}

/// <summary>
/// �L�[��t�̍X�V
/// </summary>
/// <returns>
///  true�F����I��
///  false�F�ُ�I��
/// </returns>
bool Keyboard::update() {
	char getAllKeyState[KEY_MAX];
	GetHitKeyStateAll(getAllKeyState);

	for (int i = 0; i < KEY_MAX; ++i) {
		if (getAllKeyState[i] == 1) {
			if (keyStatePress[i] < 0) {
				keyStatePress[i] = 0;
			}
			++keyStatePress[i];
		}
		else {
			if (keyStatePress[i] > 0) {
				keyStatePress[i] = 0;
			}
			--keyStatePress[i];
		}
	}
	return true;
}

/// <summary>
/// �L�[���͏�Ԃ̏�����
/// </summary>
void Keyboard::reset() {
	keyStatePress.fill(0);
}

/// <summary>
/// ����L�[�̓��͏�Ԃ�Ԃ�
/// </summary>
/// <param name="_handle">����L�[�̃n���h��</param>
/// <returns>
/// ����L�[�̓��͏��
/// </returns>
int Keyboard::state(const unsigned char _handle) const {
	return keyStatePress[_handle];
}

/// <summary>
/// ����L�[�̉�����Ă��鎞�Ԃ�Ԃ�
/// </summary>
/// <param name="_handle">����L�[�̃n���h��</param>
/// <returns>
/// ����L�[�̓��̓t���[����
/// </returns>
int Keyboard::statePress(const unsigned char _handle) const {
	return keyStatePress[_handle] > 0 ? keyStatePress[_handle] : 0;
}

/// <summary>
/// ����L�[�̉�����Ă��Ȃ����Ԃ�Ԃ�
/// </summary>
/// <param name="_handle">����L�[�̃n���h��</param>
/// <returns>
/// ����L�[�����͂���Ă��Ȃ��t���[����
/// </returns>
int Keyboard::stateRelease(const unsigned char _handle) const {
	return keyStatePress[_handle] < 0 ? -keyStatePress[_handle] : 0;
}

/// <summary>
/// ����̃L�[�������Ă��Ȃ���Ԃ��牟�������ǂ�����Ԃ�
/// </summary>
/// <param name="_handle">����L�[�̃n���h��</param>
/// <returns>
/// true�F���������� false�F����������łȂ�
/// </returns>
bool Keyboard::isDown(const unsigned char _handle) const {
	return keyStatePress[_handle] == 1 ? true : false;
}

/// <summary>
/// ����̃L�[��������Ă����Ԃ��痣�������ǂ�����Ԃ�
/// </summary>
/// <param name="_handle">����L�[�̃n���h��</param>
/// <returns>
/// true�F���������� false�F����������łȂ�
/// </returns>
bool Keyboard::isUp(const unsigned char _handle) const {
	return keyStatePress[_handle] == -1 ? true : false;
}

/// <summary>
/// �s����̃L�[�������Ă��Ȃ���Ԃ��牟�������ǂ�����Ԃ�
/// </summary>
/// <returns>
/// true�F���������� false�F����������łȂ�
/// </returns>
bool Keyboard::isDownAny() const {
	for (auto &key_state : keyStatePress) {
		if (key_state == 1) {
			return true;
		}
	}
	return false;
}

/// <summary>
/// 2�̓���L�[�̌ォ�牟����Ă���ق��𔻕ʂ���
/// </summary>
/// <param name="_handle1">����L�[1�̃n���h��</param>
/// <param name="_handle2">����L�[2�̃n���h��</param>
/// <returns>
/// later 0:�ǂ����������Ă��Ȃ� 1:��P���� 2:��Q����
/// </returns>
int Keyboard::statePressLater(const unsigned char _handle1, const unsigned char _handle2) const {
	//�f�t�H���g�͉���������Ă��Ȃ����
	int later = 0;

	//�e�L�[�̓��͏��
	int key_state1, key_state2;

	key_state1 = statePress(_handle1);
	key_state2 = statePress(_handle2);

	if (key_state1 > 0) {	//��Ԗڂ�������Ă�����
		if (key_state2 > 0 && key_state2 < key_state1) {		//��Ԗڂ���ɉ�����Ă�����
			later = 2;
		}
		else {
			later = 1;
		}
	}
	else if (key_state2 > 0) {	//��Ԗڂ�������Ă�����
		later = 2;
	}

	return later;
}

/// <summary>
/// 4�̓���L�[�̌ォ�牟����Ă���ق��𔻕ʂ���
/// </summary>
/// <param name="_handle1">����L�[1�̃n���h��</param>
/// <param name="_handle2">����L�[2�̃n���h��</param>
/// <param name="_handle3">����L�[3�̃n���h��</param>
/// <param name="_handle4">����L�[4�̃n���h��</param>
/// <returns>
/// later 0:�������������Ă��Ȃ� 1:��P���� 2:��Q���� 3:��R���� 4:��S����
/// </returns>
int Keyboard::statePressLater4(const unsigned char _handle1, const unsigned char _handle2, const unsigned char _handle3, const unsigned char _handle4) const {
	//�f�t�H���g�͉���������Ă��Ȃ����
	int later = 0;

	//�{�^���������ꂽ����
	int shortest = 999999;

	//�e�L�[�̓��͏��
	int key_state[4];

	key_state[0] = statePress(_handle1);
	key_state[1] = statePress(_handle2);
	key_state[2] = statePress(_handle3);
	key_state[3] = statePress(_handle4);

	for (int i = 0; i < 4; i++) {
		if (key_state[i] && key_state[i] < shortest) {
			later = i + 1;
			shortest = key_state[i];
		}
	}
	return later;
}

