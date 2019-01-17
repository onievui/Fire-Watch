#pragma once

#include "Collider.h"
#include "MyMath.h"


/// <summary>
/// ��`���m�̏Փ˔���
/// </summary>
/// <param name="_rect1">��`1</param>
/// <param name="_rect2">��`2</param>
/// <param name="_time">�Փ˂܂ł̎���</param>
/// <param name="_ref_normal">���˖ʂ̖@��</param>
/// <returns>
/// �Փ˂������ǂ���
/// </returns>
bool Collider::collisionRect(RectCollider &_rect1, RectCollider &_rect2, float *_time, float *_ref_normal) {
	//�e�����̏Փ˂���܂ł̎���
	float xmin, xmax, ymin, ymax;
	xmin = xmax = ymin = ymax = -1.f;
	//���W�̌v�Z
	Vector2 pos1 = *_rect1.pos + _rect1.offset;
	Vector2 pos2 = *_rect2.pos + _rect2.offset;
	//_rect1���猩�����Α��x
	Vector2 vel = *_rect1.vel - *_rect2.vel;

	//X�����̏Փ˂���܂ł̎���
	if (!FloatEqual(vel.x ,0.f)) {
		xmin = ((pos2.x - _rect2.width / 2) - (pos1.x + _rect1.width / 2)) / vel.x;
		xmax = ((pos2.x + _rect2.width / 2) - (pos1.x - _rect1.width / 2)) / vel.x;
		if (vel.x < 0) {
			std::swap(xmin, xmax);
		}
	}
	//X�����̑��x��0�̏ꍇ
	else {
		if ((pos1.x + _rect2.width / 2) > (pos2.x - _rect1.width / 2) &&
			(pos1.x - _rect2.width / 2) < (pos2.x + _rect1.width / 2)) {
			xmin = 0.0f;
			xmax = 1.0f;
		}
	}

	//Y�����̏Փ˂���܂ł̎���
	if (!FloatEqual(vel.y, 0.f)) {
		ymin = ((pos2.y - _rect2.height / 2) - (pos1.y + _rect1.height / 2)) / vel.y;
		ymax = ((pos2.y + _rect2.height / 2) - (pos1.y - _rect1.height / 2)) / vel.y;
		if (vel.y < 0) {
			std::swap(ymin, ymax);
		}
	}
	//Y�����̑��x��0�̏ꍇ
	else {
		if ((pos1.y + _rect2.height / 2) > (pos2.y - _rect1.height / 2) &&
			(pos1.y - _rect2.height / 2) < (pos2.y + _rect1.height / 2)) {
			ymin = 0.0f;
			ymax = 1.0f;
		}
	}

	//�Փ˔���
	if (xmin <= 1.0f && xmax >= 0.0f &&
		ymin <= 1.0f && ymax >= 0.0f &&
		xmin <= ymax && ymin <= xmax) {
		//X��������ɏՓ˂��Ă���
		if (xmin > ymin) {
			*_time = xmin;
			if (pos1.x < pos2.x) {
				*_ref_normal = PI;
			}
			else {
				*_ref_normal = 0.f;
			}
		}
		//Y��������ɏՓ˂��Ă���
		else {
			*_time = ymin;
			if (pos1.y < pos2.y) {
				*_ref_normal = PI * 1.5f;
			}
			else {
				*_ref_normal = PI * 0.5f;
			}
		}
		return true;
	}
	return false;
}

/// <summary>
/// ��]��`���m�̏Փ˔���
/// </summary>
/// <param name="_rect_rotate1">��]��`1</param>
/// <param name="_rect_rotate2">��]��`2</param>
/// <returns>
/// �Փ˂������ǂ���
/// </returns>
bool Collider::collisionRectRotate(RectRotateCollider &_rect_rotate1, RectRotateCollider &_rect_rotate2) {
	//���S���W�̌v�Z
	Vector2 pos1 = *_rect_rotate1.pos + _rect_rotate1.offset;
	Vector2 pos2 = *_rect_rotate2.pos + _rect_rotate2.offset;

	//�e���_���W�̌v�Z
	Vector2 vertex1[4];
	Vector2 vertex2[4];
	for (int i = 0; i < 4; ++i) {
		float x = _rect_rotate1.width / 2.f;
		float y = _rect_rotate1.height / 2.f;
		int xc = (i == 0 || i == 3) ? -1 : 1;
		int yc = (i < 2) ? -1 : 1;
		vertex1[i] = Vector2::rotate(Vector2(x*xc, y*yc), *_rect_rotate1.angle) + pos1;
		x = _rect_rotate2.width / 2.f;
		y = _rect_rotate2.height / 2.f;
		vertex2[i] = Vector2::rotate(Vector2(x*xc, y*yc), *_rect_rotate2.angle) + pos2;
	}

	//�����̌�������
	float dummy;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (collisionSegment(vertex1[i], vertex1[(i + 1) % 4], vertex2[j], vertex2[(j + 1) % 4], &dummy)) {
				return true;
			}
		}
	}
	return false;
}

/// <summary>
/// �~�Ɖ�]��`�̏d�Ȃ蔻��
/// </summary>
/// <param name="_circle">�~</param>
/// <param name="_rect_rotate">��]��`</param>
/// <returns>
/// �Փ˂������ǂ���
/// </returns>
bool Collider::collisionCircleRectRotate(CircleCollider &_circle, RectRotateCollider &_rect_rotate) {

	//�I�t�Z�b�g�̌v�Z
	Vector2 circle_pos = *_circle.pos + _circle.offset;
	Vector2 rect_rotate_pos = *_rect_rotate.pos + _rect_rotate.offset;

	//�e���_�Ƃ̔���
	Vector2 vertex[4];
	for (int i = 0; i < 4; ++i) {
		float x = _rect_rotate.width / 2.f;
		float y = _rect_rotate.height / 2.f;
		int xc = (i == 0 || i == 3) ? -1 : 1;
		int yc = (i < 2) ? -1 : 1;
		vertex[i] = Vector2::rotate(Vector2(x*xc, y*yc), *_rect_rotate.angle) + rect_rotate_pos;
		if (collisionCirclePoint(_circle, vertex[i])) {
			return true;
		}
		
	}

	//�e�����Ƃ̔���
	for (int i = 0; i < 4; ++i) {
		Vector2 vec1 = vertex[(i + 1) % 4] - vertex[i];
		Vector2 vec2 = circle_pos - vertex[i];
		Vector2 vec3 = circle_pos - vertex[(i + 1) % 4];
		float cross = Vector2::cross(vec2, vec1);
		float d = cross * cross / Vector2::length(vec1);
		if (d <= _circle.radius*_circle.radius) {
			if (Vector2::dot(vec2, vec1)*Vector2::dot(vec3, vec1) < 0) {
				return true;
			}
		}
	}

	//���O����
	float theta[2];
	for (int i = 0; i<2; i++) {
		Vector2 vec1 = vertex[i * 2 + 1] - vertex[i * 2];
		Vector2 vec2 = circle_pos - vertex[i * 2];
		theta[i] = atan2f(Vector2::cross(vec1, vec2), Vector2::dot(vec1, vec2));
	}

	if (0 <= theta[0] && theta[0] <= PI / 2 &&
		0 <= theta[1] && theta[1] <= PI / 2) {
		return true;
	}

	return false;

}

/// <summary>
/// �~�Ɖ�]��`�̏Փ˔���
/// </summary>
/// <param name="_circle">�~</param>
/// <param name="_rect_rotate">��]��`</param>
/// <param name="_time">�Փ˂܂ł̎���</param>
/// <param name="_ref_normal">���˖ʂ̖@��</param>
/// <returns>
/// �Փ˂������ǂ���
/// </returns>
bool Collider::collisionCircleRectRotate(CircleCollider &_circle, RectRotateCollider &_rect_rotate, float *_time, float *_ref_normal) {

	//�I�t�Z�b�g�̌v�Z
	Vector2 circle_pos = *_circle.pos + _circle.offset;
	Vector2 rect_rotate_pos = *_rect_rotate.pos + _rect_rotate.offset;

	//���Α��x�̌v�Z
	Vector2 vel = *_circle.vel - *_rect_rotate.vel;

	//�����Ƃ̔���p�����蔻��
	CircleCollider circle(&circle_pos, Vector2(0, 0), &vel, _circle.radius);

	//�e�����Ƃ̏Փ˂���܂ł̎���
	float t_a, t_b;
	t_a = t_b = -1.f;

	//�Փˏ��
	bool is_collision = false;

	//�e���_���W�Ƃ̋����̌v�Z
	Vector2 vertex[4];
	float vertex_distance[4];
	int min_distance_index = 0;
	for (int i = 0; i < 4; ++i) {
		float x = _rect_rotate.width / 2.f;
		float y = _rect_rotate.height / 2.f;
		int xc = (i == 0 || i == 3) ? -1 : 1;
		int yc = (i < 2) ? -1 : 1;
		vertex[i] = Vector2::rotate(Vector2(x*xc, y*yc), *_rect_rotate.angle) + rect_rotate_pos;
		vertex_distance[i] = Vector2::distanceSquare(circle_pos, vertex[i]);
		if (vertex_distance[i] < vertex_distance[min_distance_index]) {
			min_distance_index = i;
		}
	}

	//��]��`�̍����ɋ߂��ꍇ
	if (vertex_distance[0] < vertex_distance[1]) {
		if (collisionCircleSegment(circle, vertex[0], vertex[3], &t_a)) {
			*_time = t_a;
			*_ref_normal = *_rect_rotate.angle + PI;
			is_collision = true;
		}
	}
	//��]��`�̉E���ɋ߂��ꍇ
	else {
		if (collisionCircleSegment(circle, vertex[1], vertex[2], &t_a)) {
			*_time = t_a;
			*_ref_normal = *_rect_rotate.angle;
			is_collision = true;
		}
	}

	//��]��`�̏㑤�ɋ߂��ꍇ
	if (vertex_distance[1] < vertex_distance[2]) {
		if (collisionCircleSegment(circle, vertex[0], vertex[1], &t_b)) {
			if (!is_collision || t_b < t_a) {
				*_time = t_b;
				*_ref_normal = *_rect_rotate.angle + PI * 3 / 2;
				is_collision = true;
			}
		}
	}
	//��]��`�̉����ɋ߂��ꍇ
	else {
		if (collisionCircleSegment(circle, vertex[2], vertex[3], &t_b)) {
			if (!is_collision || t_b < t_a) {
				*_time = t_b;
				*_ref_normal = *_rect_rotate.angle + PI / 2;
				is_collision = true;
			}
		}
	}

	//�p�ɓ��������ꍇ
	if (is_collision && FloatEqual(t_a, t_b)) {
		*_ref_normal = *_rect_rotate.angle + PI * 5 / 4 + PI / 2 * min_distance_index;
	}

	return is_collision;

	/*
	//�p�^�[��2

	//Vector2 circle_pos = Vector2::rotate(*_circle.pos + _circle.offset, -*_rect_rotate.angle, *_rect_rotate.pos + _rect_rotate.offset);
	//Vector2 circle_vel = Vector2::rotate(*_circle.vel, -*_rect_rotate.angle);
	//Vector2 rect_rotate_vel = Vector2::rotate(*_rect_rotate.vel, -*_rect_rotate.angle);

	////�~���ߎ�������`�ɕϊ�
	//RectCollider rect1(&circle_pos, _circle.offset, &circle_vel, _circle.radius*2, _circle.radius*2);

	////��]��`����`�ɕϊ�
	//RectCollider rect2(_rect_rotate.pos, _rect_rotate.offset, &rect_rotate_vel, _rect_rotate.width, _rect_rotate.height);

	////DrawBoxAA(rect1.pos->x - rect1.width / 2, rect1.pos->y - rect1.height / 2, rect1.pos->x + rect1.width / 2, rect1.pos->y + rect1.height / 2, COLOR_BLUE, true);
	////DrawBoxAA(rect2.pos->x - rect2.width / 2, rect2.pos->y - rect2.height / 2, rect2.pos->x + rect2.width / 2, rect2.pos->y + rect2.height / 2, COLOR_BLUE, true);
	////DrawLineAA(rect1.pos->x, rect1.pos->y, rect2.pos->x, rect2.pos->y, COLOR_RED);
	////DrawLineAA(_circle.pos->x, _circle.pos->y, _rect_rotate.pos->x, _rect_rotate.pos->y, COLOR_GREEN);
	////if (*_rect_rotate.angle != 0)
	////	DrawLineAA(rect1.pos->x, rect1.pos->y, rect1.pos->x + rect1.vel->x*10, rect1.pos->y + rect1.vel->y*10, COLOR_PURPLE);

	////�����蔻����s��
	//if (collisionRect(rect1, rect2, _time, _ref_normal)) {
	//	*_ref_normal += *_rect_rotate.angle;
	//	return true;
	//}
	//return false;
	*/
}

/// <summary>
/// �~�Ɠ_�̏d�Ȃ蔻��
/// </summary>
/// <param name="_circle">�~</param>
/// <param name="_point">�_</param>
/// <returns>
/// �Փ˂������ǂ���
/// </returns>
bool Collider::collisionCirclePoint(CircleCollider &_circle, Vector2 &_point) {
	Vector2 circle_pos = *_circle.pos + _circle.offset;
	if (Vector2::distanceSquare(circle_pos, _point) <= _circle.radius*_circle.radius) {
		return true;
	}
	return false;
}

/// <summary>
/// �������m�̏Փ˔���
/// </summary>
/// <param name="_p1">����1�̎n�_</param>
/// <param name="_p2">����1�̏I�_</param>
/// <param name="_p3">����2�̎n�_</param>
/// <param name="_p4">����2�̏I�_</param>
/// <param name="_time">����1���Փ˂���܂ł̎���</param>
/// <returns>
/// �Փ˂������ǂ���
/// </returns>
bool Collider::collisionSegment(const Vector2 &_p1, const Vector2 &_p2, const Vector2 &_p3, const Vector2 &_p4, float *_time) {

	//��������
	float d1 = Vector2::cross(_p4 - _p3, _p1 - _p3);
	float d2 = Vector2::cross(_p4 - _p3, _p2 - _p3);
	float d3 = Vector2::cross(_p2 - _p1, _p3 - _p1);
	float d4 = Vector2::cross(_p2 - _p1, _p4 - _p1);
	if (d1*d2 > 0.f || d3 * d4 > 0.f) {
		return false;
	}
	//�������꒼����ɂ��邩�̊m�F
	if (FloatEqual(d1, 0.f) && FloatEqual(d2, 0.f) && FloatEqual(d3, 0.f) && FloatEqual(d4, 0.f)) {
		float dot1 = Vector2::dot(_p1 - _p3, _p2 - _p3);
		float dot2 = Vector2::dot(_p1 - _p4, _p2 - _p4);
		if (dot1 <= 0.f || dot2 <= 0.f) {
			*_time = 0.f;
			return true;
		}
		return false;
	}
	d1 = fabsf(d1);
	d2 = fabsf(d2);
	*_time = d1 / (d1 + d2);

	return true;

}

/// <summary>
/// ���C�Ɖ~�̏Փ˔���
/// </summary>
/// <param name="_ray_pos">���C�̎n�_</param>
/// <param name="_ray_vec">���C�̕����x�N�g��</param>
/// <param name="_circle_pos">�~�̒��S���W</param>
/// <param name="_radius">�~�̔��a</param>
/// <param name="_time">�Փ˂���܂ł̎���</param>
/// <returns>
/// �Փ˂������ǂ���
/// </returns>
bool Collider::collisionRayCircle(const Vector2 &_ray_pos, const Vector2 &_ray_vec, const Vector2 &_circle_pos, const float _radius, float *_time) {
	//�G���[�`�F�b�N
	if (_radius < 0.f) {
		return false;
	}
	if (FloatEqual(_ray_vec.x, 0.f) && FloatEqual(_ray_vec.y, 0.f)) {
		return false;
	}

	//�I�t�Z�b�g�̌v�Z
	Vector2 ray_pos = _ray_pos - _circle_pos;

	//���C�̕����x�N�g���̐��K��
	Vector2 ray_vec = Vector2::normalize(_ray_vec);

	// �W�����Z�o
	float dot = Vector2::dot(ray_pos, ray_vec);
	float s = dot * dot - Vector2::dot(ray_pos, ray_pos) + _radius * _radius;
	
	//�덷�̏C��
	if (FloatEqual(s, 0.f)) {
		s = 0.f;
	}
	if (s < 0.0f) {
		return false;
	}

	//�Փ˂���܂ł̎���
	*_time = -dot - sqrtf(s);
	
	return true;
}

/// <summary>
/// �~�Ɛ����̏Փ˔���
/// </summary>
/// <param name="_circle">�~</param>
/// <param name="_p1">�����̎n�_</param>
/// <param name="_p2">�����̏I�_</param>
/// <param name="_time">�Փ˂���܂ł̎���</param>
/// <returns>
/// �Փ˂������ǂ���
/// </returns>
bool Collider::collisionCircleSegment(const CircleCollider & _circle, Vector2 & _p1, Vector2 & _p2, float * _time) {

	//�Փ˂������̔���
	bool is_collision = false;

	//�Փ˂܂ł̎���
	float t0, t1, t2, t3;

	//�ʒu�֌W�̔c��
	float cross = Vector2::cross(*_circle.pos - _p1, _p2 - _p1);

	//�~�ɋ߂������̌v�Z
	Vector2 p3, p4, translate;
	if (cross >= 0) {
		translate = Vector2::createWithAngleNorm(Vector2::vector2ToAngle(_p2 - _p1) - PI / 2, _circle.radius+1);
	}
	else {
		translate = Vector2::createWithAngleNorm(Vector2::vector2ToAngle(_p2 - _p1) + PI / 2, _circle.radius+1);
	}
	p3 = _p1 + translate;
	p4 = _p2 + translate;

	//DrawLineAA(p3.x, p3.y, p4.x, p4.y, COLOR_BLUE, 3);

	//�o�O�΍�̐����Ƃ̏Փ˔���
	if (collisionSegment(*_circle.pos, *_circle.pos + *_circle.vel, _p1, _p2, &t0)) {
		is_collision = true;
		*_time = t0;
	}

	//�߂������Ƃ̏Փ˔���
	if (collisionSegment(*_circle.pos, *_circle.pos + *_circle.vel, p3, p4, &t1)) {
		if (!is_collision || t1 < *_time) {
			is_collision = true;
			*_time = t1;
		}
	}

	//�n�_�Ƃ̏Փ˔���
	if (collisionRayCircle(*_circle.pos, *_circle.vel, _p1, _circle.radius, &t2)) {
		if (t2 <= 1.f && t2 >= 0.f) {
			if (!is_collision || t2 < *_time) {
				is_collision = true;
				*_time = t2;
			}
		}
	}

	//�I�_�Ƃ̏Փ˔���
	if (collisionRayCircle(*_circle.pos, *_circle.vel, _p2, _circle.radius, &t3)) {
		if (t3 <= 1.f && t3 >= 0.f) {
			if (!is_collision || t3 < *_time) {
				is_collision = true;
				*_time = t3;
			}
		}
	}


	return is_collision;




	////�Փ˂܂ł̎���
	//float t0 = 0, t1 = 0;

	////��_�̍��W
	//Vector2 cross_point;

	////�����̃x�N�g��
	//Vector2 seg_vec = _p2 - _p1;

	////X������0�̃x�N�g��������Ȃ�
	//if (FloatEqual(_circle.vel->x, 0) || FloatEqual(seg_vec.x, 0)) {
	//	//������X�����̃x�N�g����0�Ȃ�
	//	if (FloatEqual(_circle.vel->x, 0) && FloatEqual(seg_vec.x, 0)) {
	//		//�Փ˂��Ă��Ȃ�
	//		*_time = -1.f;
	//		return false;
	//	}
	//	//�~��X�����x�N�g����0�Ȃ�
	//	if (FloatEqual(_circle.vel->x, 0)) {
	//		//��_�̍��W�����߂�
	//		cross_point = { _circle.pos->x,(seg_vec.y / seg_vec.x)*(_circle.pos->x - _p1.x) + _p1.y };
	//		t0 = (cross_point.y - _circle.pos->y) / _circle.vel->y;
	//		t1 = (cross_point.x - _p1.x) / seg_vec.x;
	//	}
	//	//�p�h����X�����x�N�g����0�Ȃ�
	//	else {
	//		//��_�̍��W�����߂�
	//		cross_point = { _p1.x,(_circle.vel->y / _circle.vel->x)*(_p1.x - _circle.pos->x) + _circle.pos->y };
	//		t0 = (cross_point.x - _circle.pos->x) / _circle.vel->x;
	//		t1 = (cross_point.y - _p1.y) / seg_vec.y;
	//	}
	//	//��_�������̒��ɂ��邩�ǂ���
	//	if (t0 < 0 || t0 > 1 || t1 < 0 || t1 > 1) {
	//		//�Փ˂��Ă��Ȃ�
	//		*_time = -1.f;
	//		return false;
	//	}
	//	else {
	//		//�~���̐�����������܂ł̎��Ԃ��Փ˂���܂ł̎���
	//		*_time = t0;
	//	}
	//}
	//else {
	//	//�����̌X�������߂�
	//	float a0 = _circle.vel->y / _circle.vel->x;
	//	float a1 = seg_vec.y / seg_vec.x;

	//	//�X�������s���ǂ���
	//	if (FloatEqual(a0, a1) || FloatEqual(a0, -a1)) {
	//		//�Փ˂��Ă��Ȃ�
	//		*_time = -1.f;
	//		return false;
	//	}
	//	//��_�̍��W�����߂�
	//	cross_point.x = (a0*_circle.pos->x - a1 * _p1.x + _p1.y - _circle.pos->y) / (a0 - a1);
	//	cross_point.y = a0 * (cross_point.x - _circle.pos->x) + _circle.pos->y;

	//	t0 = (cross_point.x - _circle.pos->x) / _circle.vel->x;
	//	t1 = (cross_point.x - _p1.x) / seg_vec.x;
	//	//��_�������̒��ɂ��邩�ǂ���
	//	if (t0 < 0 || t0 > 1 || t1 < 0 || t1 > 1) {
	//		//�Փ˂��Ă��Ȃ�
	//		*_time = 1.f;
	//		return false;
	//	}
	//	else {
	//		//�~���̐�����������܂ł̎��Ԃ��Փ˂���܂ł̎���
	//		*_time = t0;
	//	}
	//}
	//return true;
}


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_pos">���W�̃|�C���^</param>
/// <param name="_offset">�I�t�Z�b�g</param>
/// <param name="_vel">���x�̃|�C���^</param>
/// <param name="_width">����</param>
/// <param name="_height">�c��</param>
RectCollider::RectCollider(Vector2 *_pos, const Vector2 &_offset, Vector2 *_vel, const float _width, const float _height) 
	: Collider(COLLIDER_TYPE_RECT)
	, pos(_pos)
	, offset(_offset)
	, vel(_vel)
	, width(_width)
	, height(_height) {
	
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_pos">���W�̃|�C���^</param>
/// <param name="_offset">�I�t�Z�b�g</param>
/// <param name="_vel">���x�̃|�C���^</param>
/// <param name="_width">����</param>
/// <param name="_height">�c��</param>
/// <param name="_type">�����蔻��̎��</param>
RectCollider::RectCollider(Vector2 * _pos, const Vector2 & _offset, Vector2 * _vel, const float _width, const float _height, const ColliderType _type)
	: Collider(_type)
	, pos(_pos)
	, offset(_offset)
	, vel(_vel)
	, width(_width)
	, height(_height) {
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_pos">���W�̃|�C���^</param>
/// <param name="_offset">�I�t�Z�b�g</param>
/// <param name="_vel">���x�̃|�C���^</param>
/// <param name="_width">����</param>
/// <param name="_height">�c��</param>
/// <param name="_angle">�p�x�̃|�C���^</param>
RectRotateCollider::RectRotateCollider(Vector2 *_pos, const Vector2 &_offset, Vector2 *_vel, const float _width, const float _height, float *_angle)
	: RectCollider(_pos, _offset, _vel, _width, _height, COLLIDER_TYPE_RECT_ROTATE)
	, angle(_angle) {

}

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_pos">���W�̃|�C���^</param>
/// <param name="_offset">�I�t�Z�b�g</param>
/// <param name="_vel">���x�̃|�C���^</param>
/// <param name="_radius">���a</param>
CircleCollider::CircleCollider(Vector2 *_pos, const Vector2 &_offset, Vector2 *_vel, const float _radius) 
	: Collider(COLLIDER_TYPE_CIRCLE)
	, pos(_pos)
	, offset(_offset)
	, vel(_vel)
	, radius(_radius) {

}

