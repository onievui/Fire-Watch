//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameLibMath.h
//!
//! @brief  数学関連の機能のヘッダファイル
//!
//! @date   2018/10/20
//!
//! @author onievui
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// 多重インクルードの防止 ==================================================
#pragma once




// 型の定義 ================================================================

// <2Dのベクトル> ------------------------------------------------------
struct Vector2D
{
	float x;    // X成分
	float y;    // Y成分
};


// <2Dのサイズ> --------------------------------------------------------
struct Size2D
{
	float width;     // 幅
	float height;    // 高さ
};


// <2Dの矩形> ----------------------------------------------------------
struct Rect2D
{
	float x;         // 左上頂点のX座標
	float y;         // 左上頂点のY座標
	float width;     // 幅
	float height;    // 高さ
};


// <2Dの範囲> ----------------------------------------------------------
struct Bounds2D
{
	float left;      // 左端
	float top;       // 上端
	float right;     // 右端
	float bottom;    // 下端
};


// <基本形状> ----------------------------------------------------------
// 2Dの点
using Point2D = Vector2D;


// 2Dの直線
struct Line2D
{
	Point2D  p;    // 直線の通る点
	Vector2D v;    // 方向ベクトル
};


// 2Dの線分
struct Segment2D
{
	Point2D  start;    // 始点
	Point2D  end;      // 終点
};


// 2Dの円
struct Circle2D
{
	Point2D center;    // 中心座標
	float   radius;    // 半径
};


// 2Dの三角形
struct Triangle2D
{
	Point2D vertices[3];    // 頂点
};


// 2Dの箱形
struct Box2D
{
	Point2D center;    // 中心座標
	Size2D  size;      // サイズ
};


// 2Dのカプセル
struct Capsule2D
{
	Segment2D segment;    // 線分
	float     radius;     // 半径
};




// 関数の宣言 ==============================================================

// <角度の単位変換> ----------------------------------------------------

// [度]から[ラジアン]への単位変換
float ToRadians(float degree);

// [ラジアン]から[度]への単位変換
float ToDegrees(float radian);



// <数値> --------------------------------------------------------------

// 指定した値を下限～上限の範囲内に収める
int   Clamp(int   x, int   lower_limit, int   upper_limit);
float Clamp(float x, float lower_limit, float upper_limit);

// 浮動小数点数型の誤差を考慮に入れた比較
bool FloatEquals(float a, float b);



// <生成> --------------------------------------------------------------
// 2Dのベクトルの生成
Vector2D CreateVector2D(float x, float y);

// 2Dのサイズの生成
Size2D CreateSize2D(float width, float height);

// 2Dの矩形の生成
Rect2D CreateRect2D(float x, float y, float width, float height);

// 2Dの範囲の生成
Bounds2D CreateBounds2D(float left, float top, float right, float bottom);

// 2Dの点の生成
Point2D CreatePoint2D(float x, float y);

// 2Dの直線の生成
Line2D CreateLine2D(Point2D p, Vector2D v);
Line2D CreateLine2D(float px, float py, float vx, float vy);

// 2Dの線分の生成
Segment2D CreateSegment2D(Point2D start, Point2D end);
Segment2D CreateSegment2D(float sx, float sy, float ex, float ey);

// 2Dの円の生成
Circle2D CreateCircle2D(Point2D center, float radius);
Circle2D CreateCircle2D(float cx, float cy, float radius);

// 2Dの三角形の生成
Triangle2D CreateTriangle2D(Point2D p1, Point2D p2, Point2D p3);
Triangle2D CreateTriangle2D(float x1, float y1, float x2, float y2, float x3, float y3);

// 2Dの箱形の生成
Box2D CreateBox2D(Point2D center, Size2D size);
Box2D CreateBox2D(float cx, float cy, float width, float height);

// 2Dのカプセルの生成
Capsule2D CreateCapsule2D(Segment2D segment, float radius);
Capsule2D CreateCapsule2D(Point2D p1, Point2D p2, float radius);
Capsule2D CreateCapsule2D(float x1, float y1, float x2, float y2, float radius);
