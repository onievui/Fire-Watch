#include "ErrorMessage.h"
#include "Player.h"
#include "ResourceManager.h"
#include "RenderManager.h"
#include "MessageManager.h"
#include "Pad.h"
#include "Mouse.h"
#include <cmath>




/// <summary>
/// コンストラクタ
/// </summary>
Player::Player()
	: Character({ 0,0 }, RectCollider(&pos, { 0,0 }, &vel, 48, 48), ResourceManager::getIns()->getTexture(TextureID::TEXTURE_PLAYER)) 
	, flashLight() {
	initialize();
}

/// <summary>
/// メッセージの受け取り
/// </summary>
/// <param name="_type">メッセージの種類</param>
/// <param name="_out">出力</param>
/// <param name="_in">入力</param>
/// <returns>
/// 有効なメッセージを受け取ったかどうか
/// </returns>
bool Player::getMessage(const MessageType _type, void* _out, void* _in) {
	switch (_type) {
	case MessageType::GET_PLAYER:
		*(Player**)_out = this;
		return true;
	case MessageType::GET_PLAYER_POS:
		*(Vector2*)_out = pos;
		return true;
	case MessageType::PLAYER_ATTACK:
		*(bool*)_out = attack((Vector2*)_in);
		return true;
	default:
		break;
	}
	return false;
}

/// <summary>
/// 初期化
/// </summary>
void Player::initialize() {
	MessageManager* message_manager = MessageManager::getIns();
	Vector2 start_grid = message_manager->sendMessage<Vector2>(MessageType::GET_MAP_CENTER_GRID);
	start_grid.y += 2.0f;
	pos = MessageManager::getIns()->sendMessage<Vector2>(MessageType::GRID_TO_POS, &start_grid);
	flashLight.initialize();
}

/// <summary>
/// 更新
/// </summary>
void Player::update() {
	move();
	animate();
	controllFlashLight();
	crossbow.update();
}

/// <summary>
/// 描画
/// </summary>
void Player::draw() {
	RenderManager::getIns()->drawRotaGraphF(pos.x, pos.y, 1.f, 0.f, texture->getResource(textureIndex), true);
	crossbow.draw();
}

/// <summary>
/// フラッシュライトの描画
/// </summary>
void Player::drawFlashLight() {
	Vector2 mouse_pos = Mouse::getIns()->getMousePos();
	mouse_pos += RenderManager::getIns()->getScreenOffset(ScreenType::MapScreen);
	float mouse_direction = Vector2::atan2fbyVec2(pos, mouse_pos);
	flashLight.draw(pos, mouse_direction);
}

bool Player::attack(const Vector2* _mouse_pos) {
	crossbow.attack(pos,Vector2::atan2fbyVec2(pos,*_mouse_pos));

	return true;
}

/// <summary>
/// 移動処理
/// </summary>
void Player::move() {
	Pad* pad = Pad::getIns();
	//速度の反映
	pos += vel;
	vel = { 0,0 };
	//移動操作受付
	bool will_move_horizontal = false, will_move_vertical = false;
	PadCode horizontal_pressed_pad_code, vertical_pressed_pad_code;
	//横移動
	switch (pad->statePressLater(PadCode::A, PadCode::D)) {
	case 0:
		break;
	case 1:
		vel.x = -MOVE_SPEED;
		will_move_horizontal = true;
		horizontal_pressed_pad_code = PadCode::A;
		break;
	case 2:
		vel.x = MOVE_SPEED;
		will_move_horizontal = true;
		horizontal_pressed_pad_code = PadCode::D;
		break;
	default:
		ErrorMessage("プレイヤーの移動入力で不正な値が渡されました");
		break;
	}
	//縦移動
	switch (pad->statePressLater(PadCode::W, PadCode::S)) {
	case 0:
		break;
	case 1:
		vel.y = -MOVE_SPEED;
		will_move_vertical = true;
		vertical_pressed_pad_code = PadCode::W;
		break;
	case 2:
		vel.y = MOVE_SPEED;
		will_move_vertical = true;
		vertical_pressed_pad_code = PadCode::S;
		break;
	default:
		ErrorMessage("プレイヤーの移動入力で不正な値が渡されました");
		break;
	}

	//入力があったら
	if (will_move_horizontal || will_move_vertical) {
		++animeCount;
		//斜め移動の場合、速度調整
		if (will_move_horizontal&&will_move_vertical) {
			
			vel /= std::sqrtf(2.0f);
		}
		//向きの設定
		else {
			if (will_move_horizontal) {
				if (horizontal_pressed_pad_code == PadCode::A) {
					direction = Direction::DIRECTION_LEFT;
				}
				else {
					direction = Direction::DIRECTION_RIGHT;
				}
			}
			else {
				if (vertical_pressed_pad_code == PadCode::W) {
					direction = Direction::DIRECTION_UP;
				}
				else {
					direction = Direction::DIRECTION_DOWN;
				}
			}
		}
	}
	else {
		animeCount = 0;
	}

}

/// <summary>
/// フラッシュライトの操作
/// </summary>
void Player::controllFlashLight() {
	if (Mouse::getIns()->isDown(MouseCode::MOUSE_RIGHT)) {
		flashLight.switchLight();
	}
	flashLight.update();
}

/// <summary>
/// アニメーション処理
/// </summary>
void Player::animate() {
	textureIndex = (int)direction * 3 + (animeCount / 10) % 3;
}

