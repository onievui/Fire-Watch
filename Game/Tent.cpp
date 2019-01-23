#include "Tent.h"
#include "ResourceManager.h"
#include "RenderManager.h"
#include "MessageManager.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
Tent::Tent()
	: FieldObject({ 0,0 }, RectCollider(&pos, { 0,0 }, &vel, 72, 72), false, ResourceManager::getIns()->getTexture(TextureID::TEXTURE_TENT)) {
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
	RenderManager::getIns()->drawRotaGraphF(pos.x, pos.y, 3.0f, 0.0f, texture->getResource(), true);
	RenderManager::getIns()->changeScreen(ScreenType::LightAlphaScreen);
	RenderManager::getIns()->drawCircleAA(pos.x, pos.y, 48, 48, ColorCode::COLOR_WHITE);
	RenderManager::getIns()->changeScreen(ScreenType::MapScreen);
}

/// <summary>
/// �N���b�N�C�x���g
/// </summary>
void Tent::clickEvent() {

}
