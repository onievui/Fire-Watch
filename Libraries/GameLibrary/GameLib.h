//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameLib.h
//!
//! @brief  �Q�[������p���C�u�����̃w�b�_�t�@�C��
//!
//! @date   2018/10/20
//!
//! @author S.Takaki
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once




// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include <DxLib.h>

#include "GameLibAudio.h"
#include "GameLibCollision.h"
#include "GameLibGraphics.h"
#include "GameLibInput.h"
#include "GameLibMath.h"
#include "GameLibScreen.h"
#include "GameLibSystem.h"
#include "GameLibTime.h"




// �^�̒�` ================================================================
typedef int HGRP;    // �O���t�B�b�N�n���h��     
typedef int HSND;    // �T�E���h�n���h��
typedef int HFNT;    // �t�H���g�n���h��
typedef int HNET;    // �l�b�g���[�N�n���h�� 
