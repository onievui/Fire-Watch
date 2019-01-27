#include "Enemy.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "MessageManager.h"



/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_pos">�o�����W</param>
/// <param name="_collider_offset">�R���C�_�[�̃I�t�Z�b�g</param>
/// <param name="_collider_size">�R���C�_�[�̃T�C�Y</param>
/// <param name="_texture">�e�N�X�`��</param>
/// <param name="_texture_area_index">�e�N�X�`�����̎g�p�͈̓C���f�b�N�X</param>
Enemy::Enemy(const Vector2& _pos, const Vector2& _collider_offset, const Vector2& _collider_size,
	const std::shared_ptr<TextureResource>& _texture, const int _texture_area_index)
	: Character(_pos, RectCollider(&pos, _collider_offset, &vel, _collider_size.x, _collider_size.y), _texture)
	, textureAreaIndex(_texture_area_index)
	, targetPos() {
	initialize();
}

/// <summary>
/// ����������
/// </summary>
void Enemy::initialize() {
	targetPos = MessageManager::getIns()->sendMessage<Vector2*>(MessageType::GET_PLAYER_POS_PTR);
}

/// <summary>
/// �X�V����
/// </summary>
void Enemy::update() {
	pos += vel;
	vel = { 0,0 };
	vel = Vector2::createWithAngleNorm(Vector2::atan2fbyVec2(pos, *targetPos), 0.5f);
	animate();
}

/// <summary>
/// �`�揈��
/// </summary>
void Enemy::draw() {
	int texture_index = (textureIndex % 3) + (textureIndex / 3) * 12 + (textureAreaIndex < 4 ? textureAreaIndex * 3 : 48 + (textureAreaIndex - 4) * 3);
	RenderManager::getIns()->drawRotaGraph(pos.x, pos.y, 1.0f, 0.0f, texture->getResource(texture_index), true);
	//�e�X�g�R�[�h
	Vector2 offset = pos + collider.offset - RenderManager::getIns()->getScreenOffset(ScreenType::MapScreen);
	DrawBoxAA(offset.x - collider.width / 2, offset.y - collider.height / 2, offset.x + collider.width / 2, offset.y + collider.height / 2, ColorCode::COLOR_BLUE, 0);
}

/// <summary>
/// �A�j���[�V��������
/// </summary>
void Enemy::animate() {
	//���x����������Z�o
	float face = Vector2::vector2ToAngle(vel) + PI / 4;

	//�E����
	if (face >= 0.0f && face < PI / 2) {
		direction = Direction::DIRECTION_RIGHT;
		textureIndex = 3;
	}
	//������
	else if (face >= 0.0f && face < PI) {
		direction = Direction::DIRECTION_DOWN;
		textureIndex = 6;
	}
	//�����
	else if (face < 0.0f && face >= -PI / 2) {
		direction = Direction::DIRECTION_UP;
		textureIndex = 0;
	}
	//������
	else {
		direction = Direction::DIRECTION_LEFT;
		textureIndex = 9;
	}

	textureIndex += (animeCount % 45) / 15;

	//�����Ă���ԃA�j���[�V����������
	if (FloatEqual(vel.x, 0.0f) && FloatEqual(vel.y, 0.0f)) {
		animeCount = 0;
	}
	else {
		++animeCount;
	}
}
