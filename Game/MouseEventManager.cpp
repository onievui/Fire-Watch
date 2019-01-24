#include "MouseEventManager.h"
#include "MessageManager.h"
#include "Mouse.h"
#include "RenderManager.h"



/// <summary>
/// �X�V����
/// </summary>
void MouseEventManager::update() {
	Mouse* mouse = Mouse::getIns();
	MessageManager* message_manager = MessageManager::getIns();
	bool react;
	Vector2 mouse_pos = mouse->getMousePos();
	mouse_pos += RenderManager::getIns()->getScreenOffset(ScreenType::MapScreen);
	//���N���b�N����
	if (mouse->isDown(MouseCode::MOUSE_LEFT)) {
		//�t�B�[���h�I�u�W�F�N�g�ɑ΂��ăN���b�N������s��
		react = message_manager->sendMessage<bool>(MessageType::CLICK_FIELDOBJECTS, &mouse_pos);
		//�������Ȃ��ꍇ�����𑱂���
		if (!react) {
			//�v���C���[�̍U���������s��
			message_manager->sendMessage<bool>(MessageType::PLAYER_ATTACK, &mouse_pos);
		}
	}
	
}
