#pragma once
#include "Vector2.h"


//コライダーの種類
enum ColliderType {
	COLLIDER_TYPE_NONE,
	COLLIDER_TYPE_RECT,
	COLLIDER_TYPE_RECT_ROTATE,
	COLLIDER_TYPE_CIRCLE,
	COLLIDER_TYPE_NUM
};


class RectCollider;
class RectRotateCollider;
class CircleCollider;

//コライダークラス
class Collider {

public:
	const ColliderType type;	//コライダーの種類

public:
	Collider(const ColliderType _type) : type(_type){}
	virtual ~Collider() = default;

	static bool collisionRect(RectCollider &_rect1, RectCollider &_rect2, float *_time, float *_ref_normal);	//矩形同士の当たり判定
	static bool collisionRectRotate(RectRotateCollider &_rect_rotate1, RectRotateCollider &_rect_rotate2);		//回転矩形同士の重なり判定
	static bool collisionCircleRectRotate(CircleCollider &_circle, RectRotateCollider &_rect_rotate);	//円と回転矩形の重なり判定
	static bool collisionCircleRectRotate(CircleCollider &_circle, RectRotateCollider &_rect_rotate, float *_time, float *_ref_normal);	//円と回転矩形の当たり判定
	static bool collisionCirclePoint(CircleCollider &_circle, Vector2 &_point);	//円と点の重なり判定
	static bool collisionSegment(const Vector2 &_p1, const Vector2 &_p2, const Vector2 &_p3, const Vector2 &_p4, float *_time);	//線分同士の衝突判定
	static bool collisionRayCircle(const Vector2 &_ray_pos, const Vector2 &_ray_vec, const Vector2 &_circle_pos, const float _radius, float *_time);	//レイと円の衝突判定
	static bool collisionCircleSegment(const CircleCollider &_circle, Vector2 &_p1, Vector2 &_p2, float *_time);	//線分と円の衝突判定

};

//矩形コライダー
class RectCollider : public Collider {

public:
	Vector2 *pos;	//座標
	Vector2 offset;	//オフセット
	Vector2 *vel;	//速度
	float width;	//横幅
	float height;	//縦幅

public:
	RectCollider(Vector2 *_pos, const Vector2 &_offset, Vector2 *_vel, const float _width, const float _height);
	virtual ~RectCollider() = default;

protected:
	RectCollider(Vector2 *_pos, const Vector2 &_offset, Vector2 *_vel, const float _width, const float _height, const ColliderType _type);

};

//回転矩形コライダー
class RectRotateCollider : public RectCollider {

public:
	float *angle;	//回転量

public:
	RectRotateCollider(Vector2 *_pos, const Vector2 &_offset, Vector2 *_vel, const float _width, const float _height, float *_angle);
	virtual ~RectRotateCollider() = default;

};


//円形コライダー
class CircleCollider : public Collider {

public:
	Vector2 * pos;	//座標
	Vector2 offset;	//オフセット
	Vector2 *vel;	//速度
	float radius;	//半径

public:
	CircleCollider(Vector2 *_pos, const Vector2 &_offset, Vector2 *_vel, const float _radius);
	virtual ~CircleCollider() = default;

};





