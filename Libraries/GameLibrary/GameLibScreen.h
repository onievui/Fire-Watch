//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameLibScreen.h
//!
//! @brief  スクリーン関連の機能のヘッダファイル
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

// <ゲーム画面> --------------------------------------------------------
class Screen
{
	// データメンバの宣言
	private:
		Size2D  m_size;        // ゲーム画面のサイズ
		Point2D m_position;    // ゲーム画面の座標


	// メンバ関数の宣言
	public:
		// コンストラクタ
		Screen();

		// デストラクタ
		virtual ~Screen();

		// 操作
		Point2D WorldToScreenPoint(const Point2D& world_point);
		Point2D ScreenToWorldPoint(const Point2D& screen_point);

		// 属性
		const Size2D&  GetScreenSize();
		const Point2D& GetScreenPosition();
		void           SetScreenPosition(const Point2D& position);

		// プロパティ
		float Width();
		float Height();
		float Left();
		float Right();
		float Top();
		float Bottom();
		float CenterX();
		float CenterY();
};
