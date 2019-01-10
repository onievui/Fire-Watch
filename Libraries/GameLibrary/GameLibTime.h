//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameLibTime.h
//!
//! @brief  ���Ԋ֘A�̋@�\�̃w�b�_�t�@�C��
//!
//! @date   2018/10/20
//!
//! @author S.Takaki
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once




// �N���X�̒�` ============================================================

// <�t���[���^�C�}�[> --------------------------------------------------
class FrameTimer final
{
	// �N���X�萔
	private:
		static const int ONE_SECOND = 1000000;    // 1�b (=1,000,000�ʕb)


	// �ÓI�f�[�^�����o�̐錾
	private:
		float    m_frame_delta_time;    // �t���[���̌o�ߎ���[��s]
		float    m_frame_rate;          // �t���[�����[�g[fps]
		LONGLONG m_previous_time;       // �O��̌v������
		LONGLONG m_current_time;        // ���݂̌v������
		LONGLONG m_start_time;          // �t���[�����[�g�v���J�n����
		int      m_frame_count;         // �t���[����


	// �����o�֐��̐錾
	public:
		// �R���X�g���N�^
		FrameTimer();

		// �f�X�g���N�^
		~FrameTimer();

		// ����
		void Reset();     // ���Z�b�g
		void Update();    // �X�V

		// ����
		float GetFrameDeltaTime(void);    // �t���[���̌o�ߎ��Ԃ̎擾
		float GetFrameRate(void);		  // �t���[�����[�g�̎擾
};
