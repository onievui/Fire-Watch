//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameLibTime.cpp
//!
//! @brief  ���Ԋ֘A�̋@�\�̃\�[�X�t�@�C��
//!
//! @date   2018/10/20
//!
//! @author onievui
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "GameLibTime.h"

#include <DxLib.h>




// <FrameTimer�N���X> **********************************************************
// �����o�֐��̒�` ========================================================
//----------------------------------------------------------------------
//! @brief �f�t�H���g�R���X�g���N�^
//!
//! @param[in] �Ȃ�
//----------------------------------------------------------------------
FrameTimer::FrameTimer()
	: m_frame_delta_time(0.0f)
	, m_frame_rate(0.0f)
	, m_previous_time(0)
	, m_current_time(0)
	, m_start_time(0)
	, m_frame_count(0)
{
}



//----------------------------------------------------------------------
//! @brief �f�X�g���N�^
//----------------------------------------------------------------------
FrameTimer::~FrameTimer()
{
}



//------------------------------------------------------------------
//! @brief �t���[���^�C�}�[�̍X�V
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//------------------------------------------------------------------
void FrameTimer::update()
{
	// ���Ԃ̌v��
	m_previous_time = m_current_time;
	m_current_time  = GetNowHiPerformanceCount();


	// �t���[���̌o�ߎ��Ԃ̍X�V
	m_frame_delta_time = static_cast<float>(m_current_time - m_previous_time) / ONE_SECOND;


	// 1�b���Ƀt���[�����[�g�̍X�V
	m_frame_count++;
	if ((m_current_time - m_start_time) > ONE_SECOND)
	{
		m_frame_rate  = static_cast<float>(m_frame_count * ONE_SECOND) / (m_current_time - m_start_time);
		m_start_time  = m_current_time;
		m_frame_count = 0;
	}
}



//------------------------------------------------------------------
//! @brief �t���[���^�C�}�[�̃��Z�b�g
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//------------------------------------------------------------------
void FrameTimer::Reset()
{
	m_previous_time = 0;
	m_current_time  = 0;
	m_start_time    = 0; 
	m_frame_count   = 0;
}



//------------------------------------------------------------------
//! @brief �t���[���̌o�ߎ��Ԃ̎擾
//!
//! @param[in] �Ȃ�
//!
//! @return �t���[���̌o�ߎ���[s]
//------------------------------------------------------------------
float FrameTimer::GetFrameDeltaTime(void)
{
	return m_frame_delta_time;
}



//------------------------------------------------------------------
//! @brief �t���[�����[�g�̎擾
//!
//! @param[in] �Ȃ�
//!
//! @return �t���[�����[�g[fps]
//------------------------------------------------------------------
float FrameTimer::GetFrameRate(void)
{
	return m_frame_rate;
}
