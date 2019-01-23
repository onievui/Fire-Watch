#pragma once
#include "MessageInterface.h"
#include "Singleton.h"
#include <vector>



/// <summary>
/// ���b�Z�[�W����M����N���X
/// </summary>
class MessageManager : public Singleton<MessageManager> {

	friend Singleton<MessageManager>;

private:
	std::vector<MessageInterface*> watchList;

public:
	/// <summary>
	/// ���b�Z�[�W�̑��M�i�߂�l�L�j
	/// </summary>
	/// <param name="_type">���b�Z�[�W�^�C�v</param>
	/// <param name="_in">���M����f�[�^</param>
	/// <returns>
	/// �󂯎�����f�[�^
	/// </returns>
	template <class T> T sendMessage(const MessageType _type, void* _in = nullptr) {
		T out;
		for (const auto& element : watchList) {
			if (element->getMessage(_type, (void*)&out, _in)) {
				return out;
			}
		}
		return T();
	}

	/// <summary>
	/// ���b�Z�[�W�̑��M�i�߂�l���j
	/// </summary>
	/// <param name="_type">���b�Z�[�W�^�C�v</param>
	/// <param name="_in">���M����f�[�^</param>
	void sendMessage(const MessageType _type, void* _in = nullptr) {
		for (const auto& element : watchList) {
			if (element->getMessage(_type, nullptr, _in)) {
				return;
			}
		}
		return;
	}

public:
	/// <summary>
	/// �Ď�����Ώۂ̒ǉ�
	/// </summary>
	/// <param name="_element">�Ď��Ώ�</param>
	void add(MessageInterface* _element) {
		watchList.emplace_back(_element);
	}

	/// <summary>
	/// �Ď�����Ώۂ̍폜
	/// </summary>
	/// <param name="_element">�Ď��Ώ�</param>
	void remove(MessageInterface* _element) {
		for (auto it = watchList.begin(), end = watchList.end(); it != end; ++it) {
			if (*it == _element) {
				watchList.erase(it);
				return;
			}
		}
	}

	/// <summary>
	/// �Ď��Ώۂ̑S�폜
	/// </summary>
	void reset() {
		watchList.clear();
	}
};
