#include "FieldObject.h"



/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_pos">���W</param>
/// <param name="_collider">�R���C�_�[</param>
/// <param name="_is_passable">�ʉ߉\��</param>
/// <param name="_texture">�e�N�X�`��</param>
FieldObject::FieldObject(const Vector2& _pos, const RectCollider& _collider, const bool _is_passable, const std::shared_ptr<TextureResource>& _texture) 
	: pos(_pos)
	, vel()
	, collider(_collider)
	, isPassableFlag(_is_passable)
	, texture(_texture)
	, textureIndex()
	, animeCount() {
}

/// <summary>
/// �ʉ߉\���ǂ���
/// </summary>
/// <returns>
/// �ʉ߉\���ǂ���
/// </returns>
bool FieldObject::isPassabe() const {
	return isPassableFlag;
}

/// <summary>
/// �R���C�_�[�擾
/// </summary>
/// <returns>
/// �R���C�_�[
/// </returns>
RectCollider* FieldObject::getCollider() {
	return &collider;
}

/// <summary>
/// ���W�̃|�C���^�̎擾
/// </summary>
/// <returns>
/// ���W�̃|�C���^
/// </returns>
Vector2* FieldObject::getPosPtr() {
	return &pos;
}
