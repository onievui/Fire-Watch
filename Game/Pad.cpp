#include "Pad.h"
#include "Keyboard.h"
#include <algorithm>

using namespace std;


/// <summary>
/// �p�b�h�̏�����
/// </summary>
Pad::Pad() {
	padId[PadCode::DOWN]    = 0;
	padId[PadCode::LEFT]    = 1;
	padId[PadCode::RIGHT]   = 2;
	padId[PadCode::UP]      = 3;
	padId[PadCode::Z]       = 4;
	padId[PadCode::X]       = 5;
	padId[PadCode::C]       = 6;
	padId[PadCode::SPACE]   = 7;
	padId[PadCode::RETURN]  = 8;
	padId[PadCode::LSHIFT] = 9;
	padId[PadCode::TAB]     = 10;

	reset();
}

/// <summary>
/// �p�b�h�̓��͏�Ԃ̍X�V
/// </summary>
/// <returns>
/// true�F����I��
/// false�F�ُ�I��
/// </returns>
bool Pad::update()
{
	int padInput;
	padInput = GetJoypadInputState(DX_INPUT_PAD1);
	for (int i = 0; i<16; i++) {
		if (padInput & (1 << i)) {
			if (padStatePress[i] < 0) {
				padStatePress[i] = 0;
			}
			++padStatePress[i];
		}
		else {
			if (padStatePress[i] > 0) {
				padStatePress[i] = 0;
			}
			--padStatePress[i];
		}
	}
	Keyboard::getIns()->update();
	mergeKeyboardAll();

	return false;
}

/// <summary>
/// �p�b�h�̓��͏�Ԃ̏�����
/// </summary>
void Pad::reset() {
	padStatePress.fill(0);
	Keyboard::getIns()->reset();
}

/// <summary>
/// �p�b�h�ƃL�[�{�[�h�̓��͏�Ԃ����킹��
/// </summary>
void Pad::mergeKeyboardAll() {
	mergeKeyboard(PadCode::LEFT,   KEY_INPUT_LEFT);
	mergeKeyboard(PadCode::RIGHT,  KEY_INPUT_RIGHT);
	mergeKeyboard(PadCode::UP,     KEY_INPUT_UP);
	mergeKeyboard(PadCode::DOWN,   KEY_INPUT_DOWN);
	mergeKeyboard(PadCode::Z,      KEY_INPUT_Z);
	mergeKeyboard(PadCode::X,      KEY_INPUT_X);
	mergeKeyboard(PadCode::C,      KEY_INPUT_C);
	mergeKeyboard(PadCode::SPACE,  KEY_INPUT_SPACE);
	mergeKeyboard(PadCode::RETURN, KEY_INPUT_RETURN);
	mergeKeyboard(PadCode::LSHIFT, KEY_INPUT_LSHIFT);
	mergeKeyboard(PadCode::TAB,    KEY_INPUT_TAB);
}

/// <summary>
/// ���͏�Ԃ����킹�鏈��
/// </summary>
/// <param name="_id">����{�^����ID</param>
/// <param name="_handle">����L�[�̃n���h��</param>
void Pad::mergeKeyboard(const PadCode _id, const unsigned char _handle) {
	int pad_state = padStatePress[padId[_id]];
	int key_state = Keyboard::getIns()->state(_handle);
	padStatePress[padId[_id]] = max(pad_state, key_state);
}

/// <summary>
/// ����{�^���̓��͏�Ԃ�Ԃ�
/// </summary>
/// <param name="_id">����{�^����ID</param>
/// <returns>
/// ����{�^���̓��͏��
/// </returns>
int Pad::state(const PadCode _id) const {
	return padStatePress[padId[_id]];
}

/// <summary>
/// ����{�^���̉�����Ă��鎞�Ԃ�Ԃ�
/// </summary>
/// <param name="_id">����{�^����ID</param>
/// <returns>
/// ����{�^���̓��̓t���[����
/// </returns>
int Pad::statePress(const PadCode _id) const {
	return padStatePress[padId[_id]] > 0 ? padStatePress[padId[_id]] : 0;
}

/// <summary>
/// ����{�^���̉�����Ă��Ȃ����Ԃ�Ԃ�
/// </summary>
/// <param name="_id">����{�^����ID</param>
/// <returns>
/// ����{�^�������͂���Ă��Ȃ��t���[����
/// </returns>
int Pad::stateRelease(const PadCode _id) const {
	return padStatePress[padId[_id]] < 0 ? -padStatePress[padId[_id]] : 0;
}

/// <summary>
/// ����̃{�^���������Ă��Ȃ���Ԃ��牟�������ǂ�����Ԃ�
/// </summary>
/// <param name="_id">����{�^����ID</param>
/// <returns>
/// true�F���������� false�F����������łȂ�
/// </returns>
bool Pad::isDown(const PadCode _id) const {
	return padStatePress[padId[_id]] == 1 ? true : false;
}

/// <summary>
/// ����̃{�^����������Ă����Ԃ��痣�������ǂ�����Ԃ�
/// </summary>
/// <param name="_id">����{�^����ID</param>
/// <returns>
/// true�F���������� false�F����������łȂ�
/// </returns>
bool Pad::isUp(const PadCode _id) const {
	return padStatePress[padId[_id]] == -1 ? true : false;
}

/// <summary>
/// �s����̃{�^���������Ă��Ȃ���Ԃ��牟�������ǂ�����Ԃ�
/// </summary>
/// <returns>
/// true�F���������� false�F����������łȂ�
/// </returns>
bool Pad::isDownAny() const {
	for (auto &pad_state : padStatePress) {
   		if (pad_state == 1) {
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
int Pad::statePressLater(const PadCode _id1, const PadCode _id2) const {
	//�f�t�H���g�͉���������Ă��Ȃ����
	int later = 0;

	//�e�{�^���̓��͏��
	int pad_state1, pad_state2;

	pad_state1 = padStatePress[padId[_id1]];
	pad_state2 = padStatePress[padId[_id2]];

	if (pad_state1 > 0) {	//��Ԗڂ�������Ă�����
		if (pad_state2 > 0 && pad_state2 < pad_state1) {		//��Ԗڂ���ɉ�����Ă�����
			later = 2;
		}
		else {
			later = 1;
		}
	}
	else if (pad_state2 > 0) {	//��Ԗڂ�������Ă�����
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
int Pad::statePressLater4(const PadCode _id1, const PadCode _id2, const PadCode _id3, const PadCode _id4) const {
	//�f�t�H���g�͉���������Ă��Ȃ����
	int later = 0;

	//�{�^���������ꂽ����
	int shortest = 999999;

	//�e�{�^���̓��͏��
	int pad_state[4];

	pad_state[0] = padStatePress[padId[_id1]];
	pad_state[1] = padStatePress[padId[_id2]];
	pad_state[2] = padStatePress[padId[_id3]];
	pad_state[3] = padStatePress[padId[_id4]];

	for (int i = 0; i < 4; i++) {
		if (pad_state[i] && pad_state[i] < shortest) {
			later = i + 1;
			shortest = pad_state[i];
		}
	}
	return later;
}

