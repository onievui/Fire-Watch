#include "Collision.h"
#include "MessageManager.h"
#include "Collider.h"
#include "Player.h"
#include "Map.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
Collision::Collision() {

}

/// <summary>
/// �X�V
/// </summary>
void Collision::update() {
	MessageManager* message_manager = MessageManager::getIns();
	Player* player = message_manager->sendMessage<Player*>(MessageType::GET_PLAYER);
	RectCollider* player_collider = player->getCollider();
	Map* map = message_manager->sendMessage<Map*>(MessageType::GET_MAP);
	
	//�v���C���[�ƃ}�b�v�̓����蔻��
	for (int i = 0; i < Map::GRID_ROWS; i++) {
		for (int j = 0; j < Map::GRID_COLS; j++) {
			//�ʍs�s�}�X�Ɠ����蔻����s��
			if (!map->isPassable(i, j)) {
				//�Z���̓����蔻��̍쐬
				Vector2 cell_pos = Vector2((i + 0.5f)*Map::DEFAULT_GRID_SIZE, (j + 0.5f)*Map::DEFAULT_GRID_SIZE);
				Vector2 cell_vel = Vector2();
				RectCollider cell_collider = RectCollider(&cell_pos, Vector2(), &cell_vel, 
					(float)Map::DEFAULT_GRID_SIZE, (float)Map::DEFAULT_GRID_SIZE);
				//�Փˏ��i�[�p
				float time, normal;
				if (Collider::collisionRect(*player_collider, cell_collider, &time, &normal)) {
					*player_collider->vel *= 0;
				}
			}
		}
	}
}

