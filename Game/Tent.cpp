#include "Tent.h"
#include "ResourceManager.h"
#include "RenderManager.h"
#include "MessageManager.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
Tent::Tent()
	: FieldObject({ 0,0 }, RectCollider(&pos, { 0,0 }, &vel, 48, 48), false, ResourceManager::getIns()->getTexture(TextureID::TEXTURE_TENT)) {
	initialize();
}

/// <summary>
/// ������
/// </summary>
void Tent::initialize() {
	pos = MessageManager::getIns()->sendMessage<Vector2>(MessageType::GET_MAP_CENTER_POS);
}

/// <summary>
/// �X�V
/// </summary>
void Tent::update() {

}

/// <summary>
/// �`��
/// </summary>
void Tent::draw() {
	RenderManager::getIns()->drawRotaGraphF(pos.x, pos.y, 1.5f, 0.0f, texture->getResource(), true);
}

/// <summary>
/// �N���b�N�C�x���g
/// </summary>
void Tent::clickEvent() {

}