//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameLibInput.h
//!
//! @brief  ���͊֘A�̋@�\�̃w�b�_�t�@�C��
//!
//! @date   2018/10/20
//!
//! @author S.Takaki
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once




// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "GameLibMath.h"




// �N���X�̒�` ============================================================

// <���̓f�o�C�X> ------------------------------------------------------
class InputDevice
{
	// �f�[�^�����o�̐錾
	protected:
		int m_current_state;
		int m_last_state;


	// �����o�֐��̐錾
	public:
		// �R���X�g���N�^
		InputDevice();

		// �f�X�g���N�^
		virtual ~InputDevice();

		// ����
		virtual void Update() = 0;    // �X�V

		bool IsButtonDown(int button);         // �w�肳�ꂽ�{�^����������Ă��邩�ǂ����𔻒f
		bool IsButtonUp(int button);           // �w�肳�ꂽ�{�^����������Ă��Ȃ����ǂ����𔻒f
		bool IsButtonPressed(int button);      // �w�肳�ꂽ�{�^���������ꂽ���ǂ����𔻒f
		bool IsButtonReleased(int button);     // �w�肳�ꂽ�{�^���������ꂽ���ǂ����𔻒f
};



// <�W���C�p�b�h> ------------------------------------------------------
class Joypad final :public InputDevice
{
	int m_id;    // �W���C�p�b�h�̎��ʎq

	// �����o�֐��̐錾
	public:
		// �R���X�g���N�^
		Joypad(int pad_id = DX_INPUT_KEY_PAD1);

		// �f�X�g���N�^
		~Joypad();

		// ����
		void Update() override;    // �X�V
};



// <�}�E�X> ------------------------------------------------------------
class Mouse final :public InputDevice
{
	// �ÓI�f�[�^�����o�̐錾
	private:
		Point2D m_position;


	// �����o�֐��̐錾
	public:
		// �R���X�g���N�^
		Mouse();

		// �f�X�g���N�^
		~Mouse();

		// ����
		void Update() override;    // �X�V
		
		// ����
		const Point2D& GetPosition();    // �J�[�\���̍��W�̎擾
};
