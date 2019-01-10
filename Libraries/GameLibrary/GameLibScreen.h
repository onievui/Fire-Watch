//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameLibScreen.h
//!
//! @brief  �X�N���[���֘A�̋@�\�̃w�b�_�t�@�C��
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

// <�Q�[�����> --------------------------------------------------------
class Screen
{
	// �f�[�^�����o�̐錾
	private:
		Size2D  m_size;        // �Q�[����ʂ̃T�C�Y
		Point2D m_position;    // �Q�[����ʂ̍��W


	// �����o�֐��̐錾
	public:
		// �R���X�g���N�^
		Screen();

		// �f�X�g���N�^
		virtual ~Screen();

		// ����
		Point2D WorldToScreenPoint(const Point2D& world_point);
		Point2D ScreenToWorldPoint(const Point2D& screen_point);

		// ����
		const Size2D&  GetScreenSize();
		const Point2D& GetScreenPosition();
		void           SetScreenPosition(const Point2D& position);

		// �v���p�e�B
		float Width();
		float Height();
		float Left();
		float Right();
		float Top();
		float Bottom();
		float CenterX();
		float CenterY();
};
