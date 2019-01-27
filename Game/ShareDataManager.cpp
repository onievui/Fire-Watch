#include "ShareDataManager.h"



/// <summary>
/// �R���X�g���N�^
/// </summary>
ShareDataManager::ShareDataManager() {
	initialize();
}

/// <summary>
/// �f�[�^�̏�����
/// </summary>
void ShareDataManager::initialize() {
	map = nullptr;
	killCount = -1;
	liveTime = -1;
}

/// <summary>
/// �}�b�v�̕ۑ�
/// </summary>
/// <param name="_map">�}�b�v�I�u�W�F�N�g</param>
void ShareDataManager::setMap(std::unique_ptr<Map>&& _map) {
	map = std::move(_map);
}

/// <summary>
/// �}�b�v�̎擾
/// </summary>
/// <returns></returns>
std::unique_ptr<Map> ShareDataManager::getMap() {
	return std::move(map);
}

/// <summary>
/// �v���C�f�[�^�̕ۑ�
/// </summary>
/// <param name="_kill_count">�L����</param>
/// <param name="_live_time">��������</param>
void ShareDataManager::setPlayData(const int _kill_count, const int _live_time) {
	killCount = _kill_count;
	liveTime = _live_time;
}

int ShareDataManager::getKillCount() {
	return killCount;
}

int ShareDataManager::getLiveTime() {
	return liveTime;
}
