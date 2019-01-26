#include "Enemy.h"
#include "RenderManager.h"
#include "ResourceManager.h"


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
}

/// <summary>
/// ����������
/// </summary>
void Enemy::initialize() {
}

/// <summary>
/// �X�V����
/// </summary>
void Enemy::update() {
}

/// <summary>
/// �`�揈��
/// </summary>
void Enemy::draw() {
	int texture_index = textureIndex + (textureAreaIndex < 4 ? textureAreaIndex * 4 : 48 + (textureAreaIndex - 4) * 12);
	RenderManager::getIns()->drawRotaGraphF(pos.x, pos.y, 2.0f, 0.0f, texture->getResource(texture_index), true);
}
