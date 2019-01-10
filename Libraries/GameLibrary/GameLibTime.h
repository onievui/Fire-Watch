//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameLibTime.h
//!
//! @brief  時間関連の機能のヘッダファイル
//!
//! @date   2018/10/20
//!
//! @author S.Takaki
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// 多重インクルードの防止 ==================================================
#pragma once




// クラスの定義 ============================================================

// <フレームタイマー> --------------------------------------------------
class FrameTimer final
{
	// クラス定数
	private:
		static const int ONE_SECOND = 1000000;    // 1秒 (=1,000,000μ秒)


	// 静的データメンバの宣言
	private:
		float    m_frame_delta_time;    // フレームの経過時間[μs]
		float    m_frame_rate;          // フレームレート[fps]
		LONGLONG m_previous_time;       // 前回の計測時間
		LONGLONG m_current_time;        // 現在の計測時間
		LONGLONG m_start_time;          // フレームレート計測開始時間
		int      m_frame_count;         // フレーム数


	// メンバ関数の宣言
	public:
		// コンストラクタ
		FrameTimer();

		// デストラクタ
		~FrameTimer();

		// 操作
		void Reset();     // リセット
		void Update();    // 更新

		// 属性
		float GetFrameDeltaTime(void);    // フレームの経過時間の取得
		float GetFrameRate(void);		  // フレームレートの取得
};
