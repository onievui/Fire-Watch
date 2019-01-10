//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.h
//!
//! @brief  ゲーム関連のヘッダファイル
//!
//! @date   日付
//!
//! @author 制作者名
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// 多重インクルードの防止 ==================================================
#pragma once




// 定数の定義 ==============================================================
// <システム> ----------------------------------------------------------
const char* const GAME_TITLE = "Sample Game";    // ゲームタイトル


// <画面> --------------------------------------------------------------
const int SCREEN_WIDTH    = 640;    // 画面の幅[pixel]
const int SCREEN_HEIGHT   = 480;    // 画面の高さ[pixel]

const int SCREEN_TOP      = 0;                    // 画面の上端
const int SCREEN_BOTTOM   = SCREEN_HEIGHT;        // 画面の下端
const int SCREEN_LEFT     = 0;                    // 画面の左端
const int SCREEN_RIGHT    = SCREEN_WIDTH;         // 画面の右端

const int SCREEN_CENTER_X = SCREEN_WIDTH  / 2;    // 画面の中央(X座標)
const int SCREEN_CENTER_Y = SCREEN_HEIGHT / 2;    // 画面の中央(Y座標)




// クラスの定義 ============================================================

// <ゲーム> ------------------------------------------------------------
class Game
{
    // データメンバの宣言


	// メンバ関数の宣言
	public:
		// コンストラクタ
		Game();

		// デストラクタ
		~Game();

	public:
		// 操作
		void Initialize(void);
		void Update(void);
		void Render(void);
		void Finalize(void);
};
