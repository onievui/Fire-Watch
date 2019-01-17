//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameLibMath.cpp
//!
//! @brief  数学関連の機能のソースファイル
//!
//! @date   2018/10/20
//!
//! @author onievui
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include "GameLibMath.h"

#include <cmath>
#include <limits>

#include <DxLib.h>




// 関数の定義 ==============================================================

//----------------------------------------------------------------------
//! @brief 角度の単位変換([度]→[ラジアン])
//!
//! @param[in] degree 角度[度]
//!
//! @return 角度[ラジアン]
//----------------------------------------------------------------------
float ToRadians(float degree)
{
	return (degree * DX_PI_F / 180.0f);
}



//----------------------------------------------------------------------
//! @brief 角度の単位変換([ラジアン]→[度])
//!
//! @param[in] radian 角度[ラジアン]
//!
//! @return 角度[度]
//----------------------------------------------------------------------
float ToDegrees(float radian)
{
	return (radian * 180.0f / DX_PI_F);
}



//----------------------------------------------------------------------
//! @brief 指定した値を下限～上限の範囲内に収める(int版)
//!
//! @param[in] x           範囲内に収めたい値の現在値
//! @param[in] lower_limit 下限
//! @param[in] upper_limit 上限
//!
//! @return 下限～上限の範囲内に収めた値
//----------------------------------------------------------------------
int Clamp(int x, int lower_limit, int upper_limit)
{
	if (x < lower_limit)
	{
		return lower_limit;
	}
	else if (x > upper_limit)
	{
		return upper_limit;
	}
	else
	{
		return x;
	}
}



//----------------------------------------------------------------------
//! @brief 指定した値を下限～上限の範囲内に収める(float版)
//!
//! @param[in] x           範囲内に収めたい値の現在値
//! @param[in] lower_limit 下限
//! @param[in] upper_limit 上限
//!
//! @return 下限～上限の範囲内に収めた値
//----------------------------------------------------------------------
float Clamp(float x, float lower_limit, float upper_limit)
{
	if (x < lower_limit)
	{
		return lower_limit;
	}
	else if (x > upper_limit)
	{
		return upper_limit;
	}
	else
	{
		return x;
	}
}



//----------------------------------------------------------------------
//! @brief 浮動小数点数型の誤差を考慮に入れた比較
//!
//! @param[in] a 比較対象の値
//! @param[in] b 比較対象の値
//!
//! @retval true  誤差が指定範囲以内の場合
//! @retval false それ以外の場合
//----------------------------------------------------------------------
bool FloatEquals(float a, float b)
{
	if (std::abs(a - b) <= std::numeric_limits<float>::epsilon())
	{
		return true;
	}
	else
	{
		return false;
	}
}



//----------------------------------------------------------------------
//! @brief 2Dのベクトルの生成
//!
//! @param[in] x ベクトルのX成分
//! @param[in] y ベクトルのY成分
//!
//! @retval 生成された2Dのベクトル
//----------------------------------------------------------------------
Vector2D CreateVector2D(float x, float y)
{
	Vector2D v = { x, y };

	return v;
}



//----------------------------------------------------------------------
//! @brief 2Dのサイズの生成
//!
//! @param[in] width  サイズの幅
//! @param[in] height サイズの高さ
//!
//! @retval 生成された2Dの寸法
//----------------------------------------------------------------------
Size2D CreateSize2D(float width, float height)
{
	Size2D size = { width, height };

	return size;
}



//----------------------------------------------------------------------
//! @brief 2Dの矩形の生成
//!
//! @param[in] x      矩形の左上頂点のX座標
//! @param[in] y      矩形の左上頂点のY座標
//! @param[in] width  矩形の幅
//! @param[in] height 矩形の高さ
//!
//! @retval 生成された2Dの矩形
//----------------------------------------------------------------------
Rect2D CreateRect2D(float x, float y, float width, float height)
{
	Rect2D rect = { x, y, width, height };

	return rect;
}



//----------------------------------------------------------------------
//! @brief 2Dの範囲の生成
//!
//! @param[in] left   範囲の左端
//! @param[in] top    範囲の上端
//! @param[in] right  範囲の右端
//! @param[in] bottom 範囲の下端
//!
//! @retval 生成された2Dの範囲
//----------------------------------------------------------------------
Bounds2D CreateBounds2D(float left, float top, float right, float bottom)
{
	Bounds2D bounds = { left, top, right, bottom };

	return bounds;
}



//----------------------------------------------------------------------
//! @brief 2Dの点の生成
//!
//! @param[in] x 点のX座標
//! @param[in] y 点のY座標
//!
//! @retval 生成された2Dの点
//----------------------------------------------------------------------
Point2D CreatePoint2D(float x, float y)
{
	Point2D point = { x, y };

	return point;
}



//----------------------------------------------------------------------
//! @brief 2Dの直線の生成
//!
//! @param[in] p 直線の通る点
//! @param[in] v 方向ベクトル 
//!
//! @retval 生成された2Dの直線
//----------------------------------------------------------------------
Line2D CreateLine2D(Point2D p, Vector2D v)
{
	Line2D line = { p, v };

	return line;
}



//----------------------------------------------------------------------
//! @brief 2Dの直線の生成
//!
//! @param[in] px 直線の通る点のX座標
//! @param[in] py 直線の通る点のY座標
//! @param[in] vx 方向ベクトルのX成分
//! @param[in] vy 方向ベクトルのY成分
//!
//! @retval 生成された2Dの直線
//----------------------------------------------------------------------
Line2D CreateLine2D(float px, float py, float vx, float vy)
{
	Line2D line = CreateLine2D(CreatePoint2D(px, py), CreateVector2D(vx, vy));

	return line;
}



//----------------------------------------------------------------------
//! @brief 2Dの線分の生成
//!
//! @param[in] start 線分の始点
//! @param[in] end   線分の終点
//!
//! @retval 生成された2Dの線分
//----------------------------------------------------------------------
Segment2D CreateSegment2D(Point2D start, Point2D end)
{
	Segment2D segment = { start, end };

	return segment;
}



//----------------------------------------------------------------------
//! @brief 2Dの線分の生成
//!
//! @param[in] sx 線分の始点のX座標
//! @param[in] sy 線分の始点のY座標
//! @param[in] ex 線分の終点のX座標
//! @param[in] ey 線分の終点のY座標
//!
//! @retval 生成された2Dの線分
//----------------------------------------------------------------------
Segment2D CreateSegment2D(float sx, float sy, float ex, float ey)
{
	Segment2D segment = CreateSegment2D(CreatePoint2D(sx, sy), CreatePoint2D(ex, ey));

	return segment;
}



//----------------------------------------------------------------------
//! @brief 2Dの円の生成
//!
//! @param[in] center 円の中心座標
//! @param[in] radius 円の半径
//!
//! @retval 生成された2Dの円
//----------------------------------------------------------------------
Circle2D CreateCircle2D(Point2D center, float radius)
{
	Circle2D circle = { center, radius };

	return circle;
}



//----------------------------------------------------------------------
//! @brief 2Dの円の生成
//!
//! @param[in] cx     円の中心のX座標
//! @param[in] cy     円の中心のY座標
//! @param[in] radius 円の半径
//!
//! @retval 生成された2Dの円
//----------------------------------------------------------------------
Circle2D CreateCircle2D(float cx, float cy, float radius)
{
	Circle2D circle = CreateCircle2D(CreatePoint2D(cx, cy), radius);

	return circle;
}



//----------------------------------------------------------------------
//! @brief 2Dの三角形の生成
//!
//! @param[in] p1 三角形の1つめの頂点の座標
//! @param[in] p2 三角形の2つめの頂点の座標
//! @param[in] p3 三角形の3つめの頂点の座標
//!
//! @retval 生成された2Dの三角形
//----------------------------------------------------------------------
Triangle2D CreateTriangle2D(Point2D p1, Point2D p2, Point2D p3)
{
	Triangle2D triangle = { p1, p2, p3 };

	return triangle;
}



//----------------------------------------------------------------------
//! @brief 2Dの三角形の生成
//!
//! @param[in] x1 三角形の1つめの頂点のX座標
//! @param[in] y1 三角形の1つめの頂点のY座標
//! @param[in] x2 三角形の2つめの頂点のX座標
//! @param[in] y2 三角形の2つめの頂点のY座標
//! @param[in] x3 三角形の3つめの頂点のX座標 
//! @param[in] y3 三角形の3つめの頂点のY座標 
//!
//! @retval 生成された2Dの三角形
//----------------------------------------------------------------------
Triangle2D CreateTriangle2D(float x1, float y1, float x2, float y2, float x3, float y3)
{
	Triangle2D triangle = CreateTriangle2D(CreatePoint2D(x1, y1), CreatePoint2D(x2, y2), CreatePoint2D(x3, y3));

	return triangle;
}



//----------------------------------------------------------------------
//! @brief 2Dの箱形の生成
//!
//! @param[in] center 箱形の中心座標
//! @param[in] size   箱形のサイズ
//!
//! @retval 生成された2Dの箱形
//----------------------------------------------------------------------
Box2D CreateBox2D(Point2D center, Size2D size)
{
	Box2D box = { center, size };

	return box;
}



//----------------------------------------------------------------------
//! @brief 2Dの箱型の生成
//!
//! @param[in] cx     箱形の中心のX座標
//! @param[in] cy     箱形の中心のY座標
//! @param[in] width  箱形の幅
//! @param[in] height 箱形の高さ
//!
//! @retval 生成された2Dの箱形
//----------------------------------------------------------------------
Box2D CreateBox2D(float cx, float cy, float width, float height)
{
	Box2D box = CreateBox2D(CreatePoint2D(cx, cy), CreateSize2D(width, height));

	return box;
}



//----------------------------------------------------------------------
//! @brief 2Dのカプセルの生成
//!
//! @param[in] segment カプセルの両端の円の中心を結ぶ線分
//! @param[in] radius  カプセルの両端の円の半径
//!
//! @retval 生成された2Dのカプセル
//----------------------------------------------------------------------
Capsule2D CreateCapsule2D(Segment2D segment, float radius)
{
	Capsule2D capsule = { segment, radius };

	return capsule;
}



//----------------------------------------------------------------------
//! @brief 2Dのカプセルの生成
//!
//! @param[in] p1     カプセルの一方の円の中心座標
//! @param[in] p2     カプセルのもう一方の円の中心座標
//! @param[in] radius カプセルの両端の円の半径
//!
//! @retval 生成された2Dのカプセル
//----------------------------------------------------------------------
Capsule2D CreateCapsule2D(Point2D p1, Point2D p2, float radius)
{
	Capsule2D capsule = CreateCapsule2D(CreateSegment2D(p1, p2), radius);

	return capsule;
}



//----------------------------------------------------------------------
//! @brief 2Dのカプセルの生成
//!
//! @param[in] x1     カプセルの一方の円の中心のX座標
//! @param[in] y1     カプセルの一方の円の中心のY座標
//! @param[in] x2     カプセルのもう一方の円の中心のX座標
//! @param[in] y2     カプセルのもう一方の円の中心のY座標
//! @param[in] radius カプセルの両端の円の半径
//!
//! @retval 生成された2Dのカプセル
//----------------------------------------------------------------------
Capsule2D CreateCapsule2D(float x1, float y1, float x2, float y2, float radius)
{
	Capsule2D capsule = CreateCapsule2D(CreateSegment2D(CreatePoint2D(x1, y1), CreatePoint2D(x2, y2)), radius);

	return capsule;
}
