#include "FieldObjectManager.h"
#include "Tent.h"


/// <summary>
/// コンストラクタ
/// </summary>
FieldObjectManager::FieldObjectManager() 
	: fieldObjects() {
	initialize();
}

/// <summary>
/// 初期化処理
/// </summary>
void FieldObjectManager::initialize() {
	fieldObjects.clear();
	fieldObjects.shrink_to_fit();
	//テントの生成
	fieldObjects.emplace_back(std::make_unique<Tent>());
	fieldObjects[0]->initialize();
}

/// <summary>
/// 更新
/// </summary>
void FieldObjectManager::update() {
	for (auto& field_object : fieldObjects) {
		field_object->update();
	}
}

/// <summary>
/// 描画
/// </summary>
void FieldObjectManager::draw() {
	for (auto& field_object : fieldObjects) {
		field_object->draw();
	}
}

/// <summary>
/// メッセージの受け取り
/// </summary>
/// <param name="_type">メッセージタイプ</param>
/// <param name="_out">出力</param>
/// <param name="_in">入力</param>
/// <returns>
/// 有効なメッセージを受け取ったかどうか
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
