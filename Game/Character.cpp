#include "Character.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_pos"></param>
/// <param name="_collider"></param>
/// <param name="_texture"></param>
Character::Character(const Vector2& _pos, const RectCollider& _collider, const std::shared_ptr<TextureResource>& _texture) 
	: isAlive(true)
	, pos(_pos)
	, vel()
	, collider(_collider)
	, texture(_texture)
	, direction(Direction::DIRECTION_DOWN)
	, textureIndex()
	, animeCount() {
}

/// <summary>
/// �R���C�_�[�̎擾
/// </summary>
/// <returns>
/// �R���C�_�[
/// </returns>
RectCollider* Character::getCollider() {
	return &collider;
}
