#include "Bonfire.h"
#include "ResourceManager.h"
#include "RenderManager.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_pos"></param>
/// <param name="_life_time"></param>
/// <param name="_is_fire_flag"></param>
Bonfire::Bonfire(const Vector2& _pos, const int _life_time, const bool _is_fire_flag)
	: FieldObject(_pos, RectCollider(&pos, { 0,0 }, &vel, 48, 48), false, ResourceManager::getIns()->getTexture(TextureID::TEXTURE_FIRE))
	, lifeTime(_life_time)
	, power()
	, isFireFlag(_is_fire_flag) {
	initialize();
}

/// <summary>
/// ����������
/// </summary>
void Bonfire::initialize() {
}

/// <summary>
/// �X�V����
/// </summary>
void Bonfire::update() {
	if (isFireFlag) {
		--lifeTime;
		if (lifeTime <= 0) {
			isFireFlag = false;
		}
	}
	animate();
}

/// <summary>
/// �`�揈��
/// </summary>
void Bonfire::draw() {
	RenderManager::getIns()->drawRotaGraphF(pos.x, pos.y, 1.5f, 0.0f, texture->getResource(textureIndex), true);
}

/// <summary>
/// �N���b�N�C�x���g
/// </summary>
void Bonfire::clickEvent() {
}

/// <summary>
/// �A�j���[�V��������
/// </summary>
void Bonfire::animate() {
	if (isFireFlag) {
		++animeCount;
		textureIndex = (animeCount / 10) % 3;
	}
	else {
		animeCount = 0;
		textureIndex = 3;
	}
}

/// <summary>
/// �΂̓_�Ώ�Ԃ�ݒ肷��
/// </summary>
/// <param name="_is_fire_flag">�΂̓_�Ώ��</param>
void Bonfire::setFire(const bool _is_fire_flag) {
	isFireFlag = _is_fire_flag;
}

/// <summary>
/// �_�Β����ǂ���
/// </summary>
/// <returns>
/// �_�Β����ǂ���
/// </returns>
bool Bonfire::isFire() const {
	return isFireFlag;
}
