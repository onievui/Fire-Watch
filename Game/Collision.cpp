#include "Collision.h"
#include "MessageManager.h"
#include "Collider.h"
#include "Player.h"
#include "Map.h"


/// <summary>
/// コンストラクタ
/// </summary>
Collision::Collision() {

}

/// <summary>
/// 更新
/// </summary>
void Collision::update() {
	MessageManager* message_manager = MessageManager::getIns();
	Player* player = message_manager->sendMessage<Player*>(MessageType::GET_PLAYER);
	RectCollider* player_collider = player->getCollider();
	Map* map = message_manager->sendMessage<Map*>(MessageType::GET_MAP);
	
	//プレイヤーとマップの当たり判定
	for (int i = 0; i < Map::GRID_ROWS; i++) {
		for (int j = 0; j < Map::GRID_COLS; j++) {
			//通行不可マスと当たり判定を行う
			if (!map->isPassable(i, j)) {
				//セルの当たり判定の作成
				Vector2 cell_pos = Vector2((i + 0.5f)*Map::DEFAULT_GRID_SIZE, (j + 0.5f)*Map::DEFAULT_GRID_SIZE);
				Vector2 cell_vel = Vector2();
				RectCollider cell_collider = RectCollider(&cell_pos, Vector2(), &cell_vel, 
					(float)Map::DEFAULT_GRID_SIZE, (float)Map::DEFAULT_GRID_SIZE);
				//衝突情報格納用
				float time, normal;
				if (Collider::collisionRect(*player_collider, cell_collider, &time, &normal)) {
					*player_collider->vel *= 0;
				}
			}
		}
	}
}

