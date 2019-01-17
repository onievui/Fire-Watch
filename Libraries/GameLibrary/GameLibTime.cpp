//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameLibTime.cpp
//!
//! @brief  時間関連の機能のソースファイル
//!
//! @date   2018/10/20
//!
//! @author onievui
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include "GameLibTime.h"

#include <DxLib.h>




// <FrameTimerクラス> **********************************************************
// メンバ関数の定義 ========================================================
//----------------------------------------------------------------------
//! @brief デフォルトコンストラクタ
//!
//! @param[in] なし
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
//! @brief デストラクタ
//----------------------------------------------------------------------
FrameTimer::~FrameTimer()
{
}



//------------------------------------------------------------------
//! @brief フレームタイマーの更新
//!
//! @param[in] なし
//!
//! @return なし
//------------------------------------------------------------------
void FrameTimer::update()
{
	// 時間の計測
	m_previous_time = m_current_time;
	m_current_time  = GetNowHiPerformanceCount();


	// フレームの経過時間の更新
	m_frame_delta_time = static_cast<float>(m_current_time - m_previous_time) / ONE_SECOND;


	// 1秒毎にフレームレートの更新
	m_frame_count++;
	if ((m_current_time - m_start_time) > ONE_SECOND)
	{
		m_frame_rate  = static_cast<float>(m_frame_count * ONE_SECOND) / (m_current_time - m_start_time);
		m_start_time  = m_current_time;
		m_frame_count = 0;
	}
}



//------------------------------------------------------------------
//! @brief フレームタイマーのリセット
//!
//! @param[in] なし
//!
//! @return なし
//------------------------------------------------------------------
void FrameTimer::Reset()
{
	m_previous_time = 0;
	m_current_time  = 0;
	m_start_time    = 0; 
	m_frame_count   = 0;
}



//------------------------------------------------------------------
//! @brief フレームの経過時間の取得
//!
//! @param[in] なし
//!
//! @return フレームの経過時間[s]
//------------------------------------------------------------------
float FrameTimer::GetFrameDeltaTime(void)
{
	return m_frame_delta_time;
}



//------------------------------------------------------------------
//! @brief フレームレートの取得
//!
//! @param[in] なし
//!
//! @return フレームレート[fps]
//------------------------------------------------------------------
float FrameTimer::GetFrameRate(void)
{
	return m_frame_rate;
}
