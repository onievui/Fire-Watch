#include "Crossbow.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "MessageManager.h"
#include "ArrowManager.h"
#include "Vector2.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
Crossbow::Crossbow() 
	: bullets(MAX_BULLETS)
	, wait_shot(0)
	, wait_reload(0)
	, texture(ResourceManager::getIns()->getTexture(TextureID::TEXTURE_CROSSBOW)->getResource()) {

}

/// <summary>
/// �X�V����
/// </summary>
void Crossbow::update() {
	//1�񔭎˂��Ƃ̃C���^�[�o��
	if (wait_shot > 0.0f) {
		wait_shot -= 1.0f;
		if (wait_shot <= 0.0f) {
			wait_shot = 0.0f;
		}
	}
	//�����[�h�҂�
	if (wait_reload > 0.0f) {
		wait_reload -= 1.0f;
		if (wait_reload <= 0.0f) {
			wait_reload = 0.0f;
			bullets = MAX_BULLETS;
		}
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void Crossbow::draw() {

}

/// <summary>
/// �U������
/// </summary>
/// <param name="_pos">�U���ʒu</param>
void Crossbow::attack(const Vector2& _pos, const float _angle) {
	//���˂�������A�����[�h���Ȃ�U���ł��Ȃ�
	if (wait_shot <= 0.0f && wait_reload <= 0.0f) {
		//��𔭎�
		ArrowManager* arrow_manager = MessageManager::getIns()->sendMessage<ArrowManager*>(MessageType::GET_ARROW_MANAGER);
		arrow_manager->createArrow(_pos, _angle);
		--bullets;
		wait_shot = SHOT_DELAY;
		if (bullets == 0) {
			wait_reload = RELOAD_TIME;
		}
	}
}
