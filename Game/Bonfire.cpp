#include "Bonfire.h"
#include "ResourceManager.h"
#include "RenderManager.h"
#include <algorithm>


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
	power = 60;
}

/// <summary>
/// �X�V����
/// </summary>
void Bonfire::update() {
	if (isFireFlag) {
		lifeTime -= 1;
		power = (std::min)(lifeTime, 1800) / 1800.0f * 0.8f + 0.2f;
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
	RenderManager* render_manager = RenderManager::getIns();
	//�摜�̕`��
	render_manager->drawRotaGraphF(pos.x, pos.y, 1.5f, 0.0f, texture->getResource(textureIndex), true);
	//���C�g�̕`��
	render_manager->changeScreen(ScreenType::LightAlphaScreen);
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	if (isFireFlag) {	
		render_manager->drawRotaGraphF(pos.x, pos.y, 4.5f * power, 0.0f, ResourceManager::getIns()->getTexture(TextureID::TEXTURE_LIGHT1)->getResource(), true);
	}
	//�_�Β��łȂ��Ƃ����I�u�W�F�N�g����������x�ɕ\��
	else {
		render_manager->drawRotaGraphF(pos.x, pos.y, 0.25f, 0.0f, ResourceManager::getIns()->getTexture(TextureID::TEXTURE_LIGHT1)->getResource(), true);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	render_manager->changeScreen(ScreenType::MapScreen);
}

/// <summary>
/// �N���b�N�C�x���g
/// </summary>
void Bonfire::clickEvent() {
	//�_�Ώ�Ԃ�؂�ւ���
	if (lifeTime <= 0.0f) {
		isFireFlag = false;
		return;
	}
	isFireFlag = !isFireFlag;
}

/// <summary>
/// �G�Ƃ̏Փˏ���
/// </summary>
void Bonfire::hitEnemy() {
	isFireFlag = false;
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
