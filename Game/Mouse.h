#pragma once
#include "Singleton.h"
#include "Vector2.h"
#include <array>


/// <summary>
/// Mouse�N���X�pID
/// </summary>
enum MouseCode {
	MOUSE_LEFT     = MOUSE_INPUT_LEFT,
	MOUSE_RIGHT    = MOUSE_INPUT_RIGHT,
	MOUSE_MIDDLE   = MOUSE_INPUT_MIDDLE,
	MOUSE_BUTTON_4 = MOUSE_INPUT_4,
	MOUSE_BUTTON_5 = MOUSE_INPUT_5,
	MOUSE_BUTTON_6 = MOUSE_INPUT_6,
	MOUSE_BUTTON_7 = MOUSE_INPUT_7,
	MOUSE_BUTTON_8 = MOUSE_INPUT_8,
};

class Mouse : public Singleton<Mouse> {

	friend Singleton<Mouse>;

private:
	const static int MOUSE_INPUT_NUM = 8;
	std::array<int, MOUSE_INPUT_NUM> mouseStatePress;	//�}�E�X�̓��͏��
	Vector2 mousePos;
	int wheel;


private:
	Mouse();
	~Mouse() = default;

public:
	//�}�E�X�̓��͏�Ԃ̍X�V
	void update();

	//�}�E�X�̓��͏�Ԃ̍X�V
	void reset();

	//�}�E�X���W�̎擾
	Vector2 getMousePos() const;

	//�}�E�X���W�̐ݒ�
	void setMousePos(const Vector2& _pos);

	//�}�E�X�z�C�[���̉�]�ʂ̎擾
	int getMouseWheelRotVol() const;

	//����{�^���̓��͏�Ԃ�Ԃ�
	int state(const MouseCode _id) const;

	//����{�^���̉�����Ă��鎞�Ԃ�Ԃ�
	int statePress(const MouseCode _id) const;

	//����{�^���̉�����Ă��Ȃ����Ԃ�Ԃ�
	int stateRelease(const MouseCode _id) const;

	//����̃{�^���������Ă��Ȃ���Ԃ��牟�������ǂ�����Ԃ�
	bool isDown(const MouseCode _id) const;

	//����̃{�^������������Ԃ��痣�������ǂ�����Ԃ�
	bool isUp(const MouseCode _id) const;

	//�s����̃{�^���������Ă��Ȃ���Ԃ��牟�������ǂ�����Ԃ�
	bool isDownAny() const;

	//2�̓���{�^���̌ォ�牟����Ă���ق��𔻕ʂ���
	int statePressLater(const MouseCode _id1, const MouseCode _id2) const;

	//4�̓���{�^���̌ォ�牟����Ă���ق��𔻕ʂ���
	int statePressLater4(const MouseCode _id1, const MouseCode _id2, const MouseCode _id3, const MouseCode _id4) const;

};
