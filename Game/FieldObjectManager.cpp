#include "FieldObjectManager.h"
#include "Tent.h"
#include "Bonfire.h"
#include "MessageManager.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
FieldObjectManager::FieldObjectManager() 
	: fieldObjects() {
	initialize();
}

/// <summary>
/// ����������
/// </summary>
void FieldObjectManager::initialize() {
	MessageManager* message_manager = MessageManager::getIns();
	fieldObjects.clear();
	fieldObjects.shrink_to_fit();

	//�e���g�̐���
	fieldObjects.emplace_back(std::make_unique<Tent>());
	fieldObjects[0]->initialize();

	//���΂̐���
	static const Vector2 spawn_offset[3] = {
		{ 0, -4},
		{-4,  3},
		{ 4,  3}
	};
	Vector2 center_grid = message_manager->sendMessage<Vector2>(MessageType::GET_MAP_CENTER_GRID);
	for (const auto& offset : spawn_offset) {
		Vector2 spawn_grid = center_grid + offset;
		Vector2 spawn_pos = message_manager->sendMessage<Vector2>(MessageType::GRID_TO_POS, &spawn_grid);
		fieldObjects.emplace_back(std::make_unique<Bonfire>(spawn_pos, 3600, true));
	}
}

/// <summary>
/// �X�V
/// </summary>
void FieldObjectManager::update() {
	for (const auto& field_object : fieldObjects) {
		field_object->update();
	}
}

/// <summary>
/// �`��
/// </summary>
void FieldObjectManager::draw() {
	for (const auto& field_object : fieldObjects) {
		field_object->draw();
	}
}

/// <summary>
/// ���b�Z�[�W�̎󂯎��
/// </summary>
/// <param name="_type">���b�Z�[�W�^�C�v</param>
/// <param name="_out">�o��</param>
/// <param name="_in">����</param>
/// <returns>
/// �L���ȃ��b�Z�[�W���󂯎�������ǂ���
/// </returns>
bool FieldObjectManager::getMessage(const MessageType _type, void* _out, void* _in) {
	switch (_type) {
	case MessageType::GET_FIELDOBJECTS:
		*(std::vector<std::unique_ptr<FieldObject>>**)_out = &fieldObjects;
		return true;
	default:
		break;
	}
	return false;
}
