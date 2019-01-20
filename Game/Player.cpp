#include "ErrorMessage.h"
#include "Player.h"
#include "ResourceManager.h"
#include "RenderManager.h"
#include "MessageManager.h"
#include "Pad.h"



const float Player::MOVE_SPEED = 4.0f;	//�v���C���[�̈ړ����x




/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player()
	: Character({ 0,0 }, RectCollider(&pos, { 0,0 }, &vel, 48, 48), ResourceManager::getIns()->getTexture(TextureID::TEXTURE_PLAYER)) {
	initialize();
}

/// <summary>
/// ���b�Z�[�W�̎󂯎��
/// </summary>
/// <param name="_type">���b�Z�[�W�̎��</param>
/// <param name="_out">�o��</param>
/// <param name="_in">����</param>
/// <returns>
/// �L���ȃ��b�Z�[�W���󂯎�������ǂ���
/// </returns>
bool Player::getMessage(const MessageType _type, void* _out, void* _in) {
	switch (_type) {
	case MessageType::GET_PLAYER:
		*(Player**)_out = this;
		return true;
	case MessageType::GET_PLAYER_POS:
		*(Vector2*)_out = pos;
		return true;
	default:
		break;
	}
	return false;
}

/// <summary>
/// ������
/// </summary>
void Player::initialize() {
	pos = MessageManager::getIns()->sendMessage<Vector2>(MessageType::GET_MAP_CENTER_POS);
	pos.y += 50.0f;
}

/// <summary>
/// �X�V
/// </summary>
void Player::update() {
	move();
	animate();
}

/// <summary>
/// �`��
/// </summary>
void Player::draw() {
	RenderManager::getIns()->drawRotaGraphF(pos.x, pos.y, 1.f, 0.f, texture->getResource(textureIndex), true);
	DrawFormatString(0, 30, ColorCode::COLOR_BLACK, "x=%f,y=%f", pos.x, pos.y);
}

/// <summary>
/// �ړ�����
/// </summary>
void Player::move() {
	pos += vel;
	vel = { 0,0 };
	switch (Pad::getIns()->statePressLater4(PadCode::A, PadCode::D, PadCode::W, PadCode::S)) {
	case 0:
		animeCount = 0;
		break;
	case 1:
		vel.x = -MOVE_SPEED;
		direction = Direction::DIRECTION_LEFT;
		++animeCount;
		break;
	case 2:
		vel.x = MOVE_SPEED;
		direction = Direction::DIRECTION_RIGHT;
		++animeCount;
		break;
	case 3:
		vel.y = -MOVE_SPEED;
		direction = Direction::DIRECTION_UP;
		++animeCount;
		break;
	case 4:
		vel.y = MOVE_SPEED;
		direction = Direction::DIRECTION_DOWN;
		++animeCount;
		break;
	default:
		ErrorMessage("�v���C���[�̈ړ����͂ŕs���Ȓl���n����܂���");
		break;
	}
}

/// <summary>
/// �A�j���[�V��������
/// </summary>
void Player::animate() {
	textureIndex = (int)direction * 3 + (animeCount / 10) % 3;
}

