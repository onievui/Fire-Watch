#pragma once
#include "MessageInterface.h"
#include "Singleton.h"
#include <vector>



/// <summary>
/// メッセージ送受信仲介クラス
/// </summary>
class MessageManager : public Singleton<MessageManager> {

	friend Singleton<MessageManager>;

private:
	std::vector<MessageInterface*> watchList;

public:
	/// <summary>
	/// メッセージの送信（戻り値有）
	/// </summary>
	/// <param name="_type">メッセージタイプ</param>
	/// <param name="_in">送信するデータ</param>
	/// <returns>
	/// 受け取ったデータ
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
	/// メッセージの送信（戻り値無）
	/// </summary>
	/// <param name="_type">メッセージタイプ</param>
	/// <param name="_in">送信するデータ</param>
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
	/// 監視する対象の追加
	/// </summary>
	/// <param name="_element">監視対象</param>
	void add(MessageInterface* _element) {
		watchList.emplace_back(_element);
	}

	/// <summary>
	/// 監視する対象の削除
	/// </summary>
	/// <param name="_element">監視対象</param>
	void remove(MessageInterface* _element) {
		for (auto it = watchList.begin(), end = watchList.end(); it != end; ++it) {
			if (*it == _element) {
				watchList.erase(it);
				return;
			}
		}
	}

	/// <summary>
	/// 監視対象の全削除
	/// </summary>
	void reset() {
		watchList.clear();
	}
};
