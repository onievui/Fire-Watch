#pragma once

#include "Singleton.h"
#include <array>


/// <summary>
/// �L�[���͓ǂݍ��݃N���X
/// </summary>
class Keyboard final : public Singleton<Keyboard> {

	friend Singleton<Keyboard>;

private:
	const static int KEY_MAX = 256;
	std::array<int, KEY_MAX> keyStatePress;	//�L�[�̓��͏��

private:
	Keyboard();

public:
	//�L�[���͏�Ԃ̍X�V
	bool update();

	//�L�[���͏�Ԃ̏�����
	void reset();

	//����L�[�̓��͏�Ԃ�Ԃ�
	int state(const unsigned char _handle) const;

	//����L�[�̉�����Ă��鎞�Ԃ�Ԃ�
	int statePress(const unsigned char _handle) const;

	//����L�[�̉�����Ă��Ȃ����Ԃ�Ԃ�
	int stateRelease(const unsigned char _handle) const;

	//����̃L�[�������Ă��Ȃ���Ԃ��牟�������ǂ�����Ԃ�
	bool isDown(const unsigned char _handle) const;

	//����̃L�[����������Ԃ��痣�������ǂ�����Ԃ�
	bool isUp(const unsigned char _handle) const;

	//�s����̃L�[�������Ă��Ȃ���Ԃ��牟�������ǂ�����Ԃ�
	bool isDownAny() const;

	//2�̓���L�[�̌ォ�牟����Ă���ق��𔻕ʂ���
	int statePressLater(const unsigned char _handle1, const unsigned char _handle2) const;

	//4�̓���L�[�̌ォ�牟����Ă���ق��𔻕ʂ���
	int statePressLater4(const unsigned char _handle1, const unsigned char _handle2, const unsigned char _handle3, const unsigned char _handle4) const;

};