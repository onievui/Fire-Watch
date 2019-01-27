#include "Collision.h"
#include "MessageManager.h"
#include "Collider.h"
#include "Player.h"
#include "Map.h"
#include "FieldObject.h"
#include "Arrow.h"
#include "Bonfire.h"
#include "Enemy.h"


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
	using FieldObjects = std::vector<std::unique_ptr<FieldObject>>;
	FieldObjects* field_objects = message_manager->sendMessage<FieldObjects*>(MessageType::GET_FIELDOBJECTS);
	using Arrows = std::vector<std::unique_ptr<Arrow>>;
	Arrows* arrows = message_manager->sendMessage<Arrows*>(MessageType::GET_ARROWS);
	using Enemies = std::vector<std::unique_ptr<Enemy>>;
	Enemies* enemies = message_manager->sendMessage<Enemies*>(MessageType::GET_ENEMIES);

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

	//プレイヤーとフィールドオブジェクトの当たり判定
	for (auto& field_object : *field_objects) {
		//衝突情報格納用
		float time, normal;
		RectCollider* field_object_colider = field_object->getCollider();
		if (Collider::collisionRect(*player_collider, *field_object_colider, &time, &normal)) {
			if (!field_object->isPassabe()) {
				*player_collider->vel *= 0;
			}
		}
	}

	//矢と焚火の当たり判定
	for (auto& arrow : *arrows) {
		for (auto& field_object : *field_objects) {
			//焚火かどうかの確認
			Bonfire* bonfire = dynamic_cast<Bonfire*>(field_object.get());
			if (!bonfire) {
				continue;
			}
			//点火しているかどうかの確認
			if (!bonfire->isFire()) {
				continue;
			}
			//仮の角度格納用変数
			float dummy_angle = 0.0f;
			RectRotateCollider bonfire_collider = RectRotateCollider(bonfire->getCollider(), &dummy_angle);
			if (Collider::collisionRectRotate(*arrow->getCollider(), bonfire_collider)) {
				arrow->hitFire();
			}
		}
	}

	//敵と矢との当たり判定
	for (auto& enemy : *enemies) {
		for (auto& arrow : *arrows) {
			//仮の角度格納用変数
			float dummy_angle = 0.0f;
			RectRotateCollider enemy_collider = RectRotateCollider(enemy->getCollider(), &dummy_angle);
			if (Collider::collisionRectRotate(*arrow->getCollider(), enemy_collider)) {
				enemy->hitArrow(arrow->getPower(), arrow->isFire());
				arrow->hitEnemy();
			}
		}
	}

	//敵とフィールドオブジェクトとの当たり判定
	for (auto& enemy : *enemies) {
		for (auto& field_object : *field_objects) {
			//衝突情報格納用
			float time, normal;
			if (Collider::collisionRect(*enemy->getCollider(), *field_object->getCollider(), &time, &normal)) {
				field_object->hitEnemy();
			}
		}
	}
}

