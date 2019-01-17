#pragma once
#include "Vector2.h"


//�R���C�_�[�̎��
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

//�R���C�_�[�N���X
class Collider {

public:
	const ColliderType type;	//�R���C�_�[�̎��

public:
	Collider(const ColliderType _type) : type(_type){}
	virtual ~Collider() = default;

	static bool collisionRect(RectCollider &_rect1, RectCollider &_rect2, float *_time, float *_ref_normal);	//��`���m�̓����蔻��
	static bool collisionRectRotate(RectRotateCollider &_rect_rotate1, RectRotateCollider &_rect_rotate2);		//��]��`���m�̏d�Ȃ蔻��
	static bool collisionCircleRectRotate(CircleCollider &_circle, RectRotateCollider &_rect_rotate);	//�~�Ɖ�]��`�̏d�Ȃ蔻��
	static bool collisionCircleRectRotate(CircleCollider &_circle, RectRotateCollider &_rect_rotate, float *_time, float *_ref_normal);	//�~�Ɖ�]��`�̓����蔻��
	static bool collisionCirclePoint(CircleCollider &_circle, Vector2 &_point);	//�~�Ɠ_�̏d�Ȃ蔻��
	static bool collisionSegment(const Vector2 &_p1, const Vector2 &_p2, const Vector2 &_p3, const Vector2 &_p4, float *_time);	//�������m�̏Փ˔���
	static bool collisionRayCircle(const Vector2 &_ray_pos, const Vector2 &_ray_vec, const Vector2 &_circle_pos, const float _radius, float *_time);	//���C�Ɖ~�̏Փ˔���
	static bool collisionCircleSegment(const CircleCollider &_circle, Vector2 &_p1, Vector2 &_p2, float *_time);	//�����Ɖ~�̏Փ˔���

};

//��`�R���C�_�[
class RectCollider : public Collider {

public:
	Vector2 *pos;	//���W
	Vector2 offset;	//�I�t�Z�b�g
	Vector2 *vel;	//���x
	float width;	//����
	float height;	//�c��

public:
	RectCollider(Vector2 *_pos, const Vector2 &_offset, Vector2 *_vel, const float _width, const float _height);
	virtual ~RectCollider() = default;

protected:
	RectCollider(Vector2 *_pos, const Vector2 &_offset, Vector2 *_vel, const float _width, const float _height, const ColliderType _type);

};

//��]��`�R���C�_�[
class RectRotateCollider : public RectCollider {

public:
	float *angle;	//��]��

public:
	RectRotateCollider(Vector2 *_pos, const Vector2 &_offset, Vector2 *_vel, const float _width, const float _height, float *_angle);
	virtual ~RectRotateCollider() = default;

};


//�~�`�R���C�_�[
class CircleCollider : public Collider {

public:
	Vector2 * pos;	//���W
	Vector2 offset;	//�I�t�Z�b�g
	Vector2 *vel;	//���x
	float radius;	//���a

public:
	CircleCollider(Vector2 *_pos, const Vector2 &_offset, Vector2 *_vel, const float _radius);
	virtual ~CircleCollider() = default;

};





