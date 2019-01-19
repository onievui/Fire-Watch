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
		T ret;
		for (auto& element : watchList) {
			if (element->getMessage(_type, (void**)&ret)) {
				return ret;
			}
		}
		return T();
	}

public:
	void add(MessageInterface* _element) {
		watchList.emplace_back(_element);
	}
};
