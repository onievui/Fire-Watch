#include "ArrowManager.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
ArrowManager::ArrowManager()
	: arrows() {
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
bool ArrowManager::getMessage(const MessageType _type, void* _out, void* _in) {
	switch (_type) {
	case MessageType::GET_ARROW_MANAGER:
		*(ArrowManager**)_out = this;
		return true;
	case MessageType::GET_ARROWS:
		*(std::vector<std::unique_ptr<Arrow>>**)_out = &arrows;
		return true;
	default:
		break;
	}
	return false;
}

/// <summary>
/// �X�V����
/// </summary>
void ArrowManager::update() {
	for (const auto& arrow : arrows) {
		arrow->update();
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void ArrowManager::draw() {
	for (const auto& arrow : arrows) {
		arrow->draw();
	}
}

/// <summary>
/// ��̐���
/// </summary>
/// <param name="_pos">�o��������W</param>
/// <param name="_angle">�i�s����</param>
void ArrowManager::createArrow(const Vector2& _pos, const float _angle) {
	arrows.emplace_back(std::make_unique<Arrow>(_pos, _angle));
}
