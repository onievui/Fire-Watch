#pragma once

#include "Singleton.h"
#include <array>
#include <algorithm>


/// <summary>
/// Pad�N���X�pID
/// </summary>
enum PadCode {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	Z,
	X,
	C,
	SPACE,
	RETURN,
	LSHIFT,
	TAB,
};

/// <summary>
/// �W���C�p�b�h�y�уL�[�{�[�h�̓��͓ǂݍ��݃N���X
/// </summary>
class Pad final : public Singleton<Pad> {

	friend Singleton<Pad>;

private:
	const static int PAD_KEY_NUM = 16;
	std::array<int, PAD_KEY_NUM> padId;			//�{�^���̊��蓖��
	std::array<int, PAD_KEY_NUM> padStatePress;	//�p�b�h�̓��͏��

private:
	Pad();
	~Pad() = default;

	//�p�b�h�ƃL�[�{�[�h�̓��͏�Ԃ����킹��
	void mergeKeyboardAll();

	//���͏�Ԃ����킹�鏈��
	void mergeKeyboard(const PadCode _id, const unsigned char _handle);

public:
	//�p�b�h�̓��͏�Ԃ̍X�V
	bool update();

	//�p�b�h�̓��͏�Ԃ̏�����
	void reset();

	//����{�^���̓��͏�Ԃ�Ԃ�
	int state(const PadCode _id) const;

	//����{�^���̉�����Ă��鎞�Ԃ�Ԃ�
	int statePress(const PadCode _id) const;

	//����{�^���̉�����Ă��Ȃ����Ԃ�Ԃ�
	int stateRelease(const PadCode _id) const;

	//����̃{�^���������Ă��Ȃ���Ԃ��牟�������ǂ�����Ԃ�
	bool isDown(const PadCode _id) const;

	//����̃{�^������������Ԃ��痣�������ǂ�����Ԃ�
	bool isUp(const PadCode _id) const;

	//�s����̃{�^���������Ă��Ȃ���Ԃ��牟�������ǂ�����Ԃ�
	bool isDownAny() const;

	//2�̓���{�^���̌ォ�牟����Ă���ق��𔻕ʂ���
	int statePressLater(const PadCode _id1, const PadCode _id2) const;

	//4�̓���{�^���̌ォ�牟����Ă���ق��𔻕ʂ���
	int statePressLater4(const PadCode _id1, const PadCode _id2, const PadCode _id3, const PadCode _id4) const;

};