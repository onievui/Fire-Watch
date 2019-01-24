#include "FlashLight.h"
#include "ResourceManager.h"
#include "RenderManager.h"



/// <summary>
/// �R���X�g���N�^
/// </summary>
FlashLight::FlashLight() 
	: battery() 
	, isLighting() 
	, texture(ResourceManager::getIns()->getTexture(TextureID::TEXTURE_FLASHLIGHT)->getResource()) {
	initialize();
}

/// <summary>
/// ����������
/// </summary>
void FlashLight::initialize() {
	battery = MAX_BATTERY;
	isLighting = false;
}

/// <summary>
/// �X�V����
/// </summary>
void FlashLight::update() {
	if (isLighting && battery > 0.0f) {
		battery -= BATTERY_DRAIN_SPEED;
		if (battery <= 0.0f) {
			isLighting = false;
		}
	}
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="_pos">�t���b�V�����C�g�̍��W</param>
/// <param name="_angle">�t���b�V�����C�g�̊p�x</param>
void FlashLight::draw(const Vector2& _pos, const float _angle) {
	//�I�t�Ȃ�`�悵�Ȃ�
	if (!isLighting) {
		return;
	}
	RenderManager* render_manager = RenderManager::getIns();
	render_manager->changeScreen(ScreenType::LightAlphaScreen);

	float light_power = 1.0f - (1.0f - battery / 100.0f)*(1.0f - battery / 100.0f);
	Vector2 draw_pos = _pos + Vector2::createWithAngleNorm(_angle, 172 + 10);

	SetDrawBlendMode(DX_BLENDMODE_ADD, (int)(255*light_power));
	render_manager->drawRotaGraphF(draw_pos.x, draw_pos.y, 1.5f, _angle, texture, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	render_manager->changeScreen(ScreenType::MapScreen);
}

/// <summary>
/// �I���I�t�̐؂�ւ�
/// </summary>
void FlashLight::switchLight() {
	if (battery <= 0.0f) {
		isLighting = false;
		return;
	}
	isLighting = !isLighting;
}

/// <summary>
/// �o�b�e���[�̒ǉ�
/// </summary>
/// <param name="_add_battery">�ǉ�����o�b�e���[��</param>
void FlashLight::addBattery(const float _add_battery) {
	battery += _add_battery;
	if (battery > MAX_BATTERY) {
		battery = MAX_BATTERY;
	}
}
