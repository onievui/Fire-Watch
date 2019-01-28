#include "Enemy.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "MessageManager.h"



/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_AI">AI�^�C�v</param>
/// <param name="_hp">�o�����W</param>
/// <param name="_pos">�o�����W</param>
/// <param name="_collider_offset">�R���C�_�[�̃I�t�Z�b�g</param>
/// <param name="_collider_size">�R���C�_�[�̃T�C�Y</param>
/// <param name="_texture">�e�N�X�`��</param>
/// <param name="_texture_area_index">�e�N�X�`�����̎g�p�͈̓C���f�b�N�X</param>
Enemy::Enemy(std::unique_ptr<EnemyAI>&& _AI, const int _hp, const Vector2& _pos,  const Vector2& _collider_offset, const Vector2& _collider_size,
	const std::shared_ptr<TextureResource>& _texture, const int _texture_area_index)
	: Character(_pos, RectCollider(&pos, _collider_offset, &vel, _collider_size.x, _collider_size.y), _texture)
	, myAI(std::move(_AI))
	, isDestroyFlag(false)
	, isFire(false)
	, hp(_hp)
	, textureAreaIndex(_texture_area_index) {
	initialize();
}

/// <summary>
/// ����������
/// </summary>
void Enemy::initialize() {
	myAI->initialize(this);
}

/// <summary>
/// �X�V����
/// </summary>
void Enemy::update() {
	//�����Ă���Ԃ̂ݏ���
	if (isAliveFlag) {
		pos += vel;
		vel = { 0,0 };
		myAI->update();
		animate();
	}
	//����ł���Ԃ̂ݏ���
	else {
		if (animeCount >= (isFire ? 120 : 60)) {
			isDestroyFlag = true;
		}
		++animeCount;
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void Enemy::draw() {
	int texture_index = (textureIndex % 3) + (textureIndex / 3) * 12 + (textureAreaIndex < 4 ? textureAreaIndex * 3 : 48 + (textureAreaIndex - 4) * 3);
	//����ł���Ԃ͐F���Â�����
	if (!isAliveFlag) {
		RenderManager* render_manager = RenderManager::getIns();
		int r, g, b;
		GetDrawBright(&r, &g, &b);
		float rate = animeCount / (isFire ? 120.0f : 60.0f);
		if (!isFire) {
			SetDrawBright((int)(r*(1.0f - (0.75f)*rate)), (int)(g*(1.0f - (0.9f)*rate)), (int)(b*(1.0f - (0.75f)*rate)));
		}
		else {
			SetDrawBright(r, (int)(g*(1.0f - (0.9f)*rate)), (int)(b*(1.0f - (0.9f)*rate)));
		}
		render_manager->drawRotaGraph(pos.x, pos.y, 1.0f, 0.0f, texture->getResource(texture_index), true);
		SetDrawBright(r, g, b);
		if (isFire) {
			render_manager->changeScreen(ScreenType::LightAlphaScreen);
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
			render_manager->drawRotaGraphF(pos.x, pos.y, 0.8f*(1.0f-rate) + 0.4f, 0.0f,
				ResourceManager::getIns()->getTexture(TextureID::TEXTURE_LIGHT1)->getResource(), true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			render_manager->changeScreen(ScreenType::MapScreen);
		}
	}
	else {
		RenderManager::getIns()->drawRotaGraph(pos.x, pos.y, 1.0f, 0.0f, texture->getResource(texture_index), true);
	}
	//�����蔻��m�F�p
	//Vector2 offset = pos + collider.offset - RenderManager::getIns()->getScreenOffset(ScreenType::MapScreen);
	//DrawBoxAA(offset.x - collider.width / 2, offset.y - collider.height / 2, offset.x + collider.width / 2, offset.y + collider.height / 2, ColorCode::COLOR_BLUE, 0);
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

/// <summary>
/// ��Ƃ̏Փˏ���
/// </summary>
/// <param name="_damage">�_���[�W</param>
/// <param name="_isFireArrow">��R�ď�Ԃ��ǂ���</param>
void Enemy::hitArrow(const int _damage, const bool _isFireArrow) {
	hp -= _damage;
	if (hp <= 0) {
		animeCount = 0;
		isAliveFlag = false;
		if (_isFireArrow) {
			isFire = true;
		}
	}
	
}

bool Enemy::isDestroy() {
	return isDestroyFlag;
}
