#include "FieldObjectManager.h"
#include "Tent.h"


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
	fieldObjects.clear();
	fieldObjects.shrink_to_fit();
	//�e���g�̐���
	fieldObjects.emplace_back(std::make_unique<Tent>());
	fieldObjects[0]->initialize();
}

/// <summary>
/// �X�V
/// </summary>
void FieldObjectManager::update() {
	for (auto& field_object : fieldObjects) {
		field_object->update();
	}
}

/// <summary>
/// �`��
/// </summary>
void FieldObjectManager::draw() {
	for (auto& field_object : fieldObjects) {
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
