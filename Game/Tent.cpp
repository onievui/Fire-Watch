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
	RenderManager* render_manager = RenderManager::getIns();
	render_manager->drawRotaGraphF(pos.x, pos.y, 3.0f, 0.0f, texture->getResource(), true);
	render_manager->changeScreen(ScreenType::LightAlphaScreen);
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	render_manager->drawRotaGraphF(pos.x, pos.y, 0.4f, 0.0f, ResourceManager::getIns()->getTexture(TextureID::TEXTURE_LIGHT1)->getResource(), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	render_manager->changeScreen(ScreenType::MapScreen);
}

/// <summary>
/// �N���b�N�C�x���g
/// </summary>
void Tent::clickEvent() {

}
