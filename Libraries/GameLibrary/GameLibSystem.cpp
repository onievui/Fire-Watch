//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameLibSystem.cpp
//!
//! @brief  �V�X�e���֘A�̋@�\�̃\�[�X�t�@�C��
//!
//! @date   2018/10/20
//!
//! @author S.Takaki
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "GameLibSystem.h"

#include <DxLib.h>




// �֐��̒�` ==============================================================

//----------------------------------------------------------------------
//! @brief �Q�[���̏I��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void ExitGame(void)
{
	PostQuitMessage(0);
}