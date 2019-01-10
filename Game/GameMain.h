//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.h
//!
//! @brief  �Q�[���֘A�̃w�b�_�t�@�C��
//!
//! @date   ���t
//!
//! @author ����Җ�
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once




// �萔�̒�` ==============================================================
// <�V�X�e��> ----------------------------------------------------------
const char* const GAME_TITLE = "Sample Game";    // �Q�[���^�C�g��


// <���> --------------------------------------------------------------
const int SCREEN_WIDTH    = 640;    // ��ʂ̕�[pixel]
const int SCREEN_HEIGHT   = 480;    // ��ʂ̍���[pixel]

const int SCREEN_TOP      = 0;                    // ��ʂ̏�[
const int SCREEN_BOTTOM   = SCREEN_HEIGHT;        // ��ʂ̉��[
const int SCREEN_LEFT     = 0;                    // ��ʂ̍��[
const int SCREEN_RIGHT    = SCREEN_WIDTH;         // ��ʂ̉E�[

const int SCREEN_CENTER_X = SCREEN_WIDTH  / 2;    // ��ʂ̒���(X���W)
const int SCREEN_CENTER_Y = SCREEN_HEIGHT / 2;    // ��ʂ̒���(Y���W)




// �N���X�̒�` ============================================================

// <�Q�[��> ------------------------------------------------------------
class Game
{
    // �f�[�^�����o�̐錾


	// �����o�֐��̐錾
	public:
		// �R���X�g���N�^
		Game();

		// �f�X�g���N�^
		~Game();

	public:
		// ����
		void Initialize(void);
		void Update(void);
		void Render(void);
		void Finalize(void);
};
