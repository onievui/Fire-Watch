#pragma once
#include "MessageInterface.h"
#include "Singleton.h"
#include <vector>



class MessageManager : public Singleton<MessageManager> {

	friend Singleton<MessageManager>;

private:
	std::vector<MessageInterface*> watchList;

public:
	template <class T> T sendMessage(const MessageType _type) {
		T out;
		for (auto& element : watchList) {
			if (element->getMessage(_type, (void*)&out, nullptr)) {
				return out;
			}
		}
		return T();
	}

	template <class T> T sendMessage(const MessageType _type, void* _in) {
		T out;
		for (auto& element : watchList) {
			if (element->getMessage(_type, (void*)&out, _in)) {
				return out;
			}
		}
		return T();
	}

public:
	void add(MessageInterface* _element) {
		watchList.emplace_back(_element);
	}

	void reset() {
		watchList.clear();
	}
};
