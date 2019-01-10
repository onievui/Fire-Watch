//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameLibInput.h
//!
//! @brief  入力関連の機能のヘッダファイル
//!
//! @date   2018/10/20
//!
//! @author S.Takaki
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// 多重インクルードの防止 ==================================================
#pragma once




// ヘッダファイルの読み込み ================================================
#include "GameLibMath.h"




// クラスの定義 ============================================================

// <入力デバイス> ------------------------------------------------------
class InputDevice
{
	// データメンバの宣言
	protected:
		int m_current_state;
		int m_last_state;


	// メンバ関数の宣言
	public:
		// コンストラクタ
		InputDevice();

		// デストラクタ
		virtual ~InputDevice();

		// 操作
		virtual void Update() = 0;    // 更新

		bool IsButtonDown(int button);         // 指定されたボタンが押されているかどうかを判断
		bool IsButtonUp(int button);           // 指定されたボタンが押されていないかどうかを判断
		bool IsButtonPressed(int button);      // 指定されたボタンが押されたかどうかを判断
		bool IsButtonReleased(int button);     // 指定されたボタンが離されたかどうかを判断
};



// <ジョイパッド> ------------------------------------------------------
class Joypad final :public InputDevice
{
	int m_id;    // ジョイパッドの識別子

	// メンバ関数の宣言
	public:
		// コンストラクタ
		Joypad(int pad_id = DX_INPUT_KEY_PAD1);

		// デストラクタ
		~Joypad();

		// 操作
		void Update() override;    // 更新
};



// <マウス> ------------------------------------------------------------
class Mouse final :public InputDevice
{
	// 静的データメンバの宣言
	private:
		Point2D m_position;


	// メンバ関数の宣言
	public:
		// コンストラクタ
		Mouse();

		// デストラクタ
		~Mouse();

		// 操作
		void Update() override;    // 更新
		
		// 属性
		const Point2D& GetPosition();    // カーソルの座標の取得
};
