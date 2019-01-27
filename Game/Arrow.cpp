#include "Arrow.h"
#include "ResourceManager.h"
#include "RenderManager.h"
#include "Map.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_pos">�o�����W</param>
/// <param name="_angle">�i�s����</param>
Arrow::Arrow(const Vector2& _pos, const float _angle)
	: state(ArrowState::NORMAL_ARROW)
	, pos(_pos)
	, vel(Vector2::createWithAngleNorm(_angle, 12))
	, angle(_angle)
	, textureIndex()
	, animeCount()
	, collider(RectRotateCollider(&pos, { 0,0 }, &vel, 36, 6, &angle))
	, texture(ResourceManager::getIns()->getTexture(TextureID::TEXTURE_ARROW)) {
	 
}

/// <summary>
/// �X�V����
/// </summary>
void Arrow::update() {
	pos += vel;
	//�R�ď�ԂȂ�A�j���[�V�������s��
	if (state == ArrowState::FIRE_ARROW) {
		++animeCount;
		textureIndex = (animeCount % 30 < 15 ? 1 : 2);
	}

	//�X�e�[�W���ɂ��邩�̔���
	insideAreaCheck();
}

/// <summary>
/// �`�揈��
/// </summary>
void Arrow::draw() {
	//�j�󂳂�Ă��Ȃ���Ε`�悷��
	if (state != ArrowState::DESTROYED) {
		RenderManager* render_manager = RenderManager::getIns();
		render_manager->drawRotaGraphF(pos.x, pos.y, 1.5f, angle + PI * 3 / 4, texture->getResource(textureIndex), true);
		//�R�ď�ԂȂ疾����o��
		if (state == ArrowState::FIRE_ARROW) {
			render_manager->changeScreen(ScreenType::LightAlphaScreen);
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
			render_manager->drawRotaGraphF(pos.x, pos.y, 0.8f, 0.0f, 
				ResourceManager::getIns()->getTexture(TextureID::TEXTURE_LIGHT1)->getResource(), true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			render_manager->changeScreen(ScreenType::MapScreen);
		}
	}
}

/// <summary>
/// �R���C�_�[�̎擾
/// </summary>
/// <returns>
/// �R���C�_�[
/// </returns>
RectRotateCollider* Arrow::getCollider() {
	return &collider;
}

/// <summary>
/// �U���͂̎擾
/// </summary>
/// <returns></returns>
int Arrow::getPower() {
	//�ʏ��ԂȂ�1�_���[�W
	if (state == ArrowState::NORMAL_ARROW) {
		return 1;
	}
	//�R�ď�ԂȂ�1�_���[�W
	else if (state == ArrowState::FIRE_ARROW) {
		return 1;
	}
	return 0;
}

/// <summary>
/// �c���Ă��邩�ǂ����̊m�F
/// </summary>
/// <returns>
/// �c���Ă��邩�ǂ���
/// </returns>
bool Arrow::isAlive() {
	return (state != ArrowState::DESTROYED ? true : false);
}

/// <summary>
/// �G�ƏՓ˂������̏���
/// </summary>
void Arrow::hitEnemy() {
	state = ArrowState::DESTROYED;
}

/// <summary>
/// ���ƏՓ˂������̏���
/// </summary>
void Arrow::hitFire() {
	if (state == ArrowState::NORMAL_ARROW) {
		state = ArrowState::FIRE_ARROW;
	}
}

/// <summary>
/// �X�e�[�W���ɂ��邩�̔���
/// </summary>
void Arrow::insideAreaCheck() {
	//�X�e�[�W�O�Ȃ����
	if (pos.x < 0.0f || pos.x > Map::GRID_COLS*Map::DEFAULT_GRID_SIZE ||
		pos.y < 0.0f || pos.y > Map::GRID_ROWS*Map::DEFAULT_GRID_SIZE) {
		state = ArrowState::DESTROYED;
	}
}
