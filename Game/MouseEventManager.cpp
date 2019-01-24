#include "MouseEventManager.h"
#include "MessageManager.h"
#include "Mouse.h"
#include "RenderManager.h"



/// <summary>
/// 更新処理
/// </summary>
void MouseEventManager::update() {
	Mouse* mouse = Mouse::getIns();
	MessageManager* message_manager = MessageManager::getIns();
	bool react;
	Vector2 mouse_pos = mouse->getMousePos();
	mouse_pos += RenderManager::getIns()->getScreenOffset(ScreenType::MapScreen);
	//左クリック処理
	if (mouse->isDown(MouseCode::MOUSE_LEFT)) {
		//フィールドオブジェクトに対してクリック判定を行う
		react = message_manager->sendMessage<bool>(MessageType::CLICK_FIELDOBJECTS, &mouse_pos);
		//反応がない場合処理を続ける
		if (!react) {
			//プレイヤーの攻撃処理を行う
			message_manager->sendMessage<bool>(MessageType::PLAYER_ATTACK, &mouse_pos);
		}
	}
	
}
