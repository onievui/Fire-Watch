#include "Sound.h"



SoundPlayer::SoundPlayer() {
	reset();
}

void SoundPlayer::reset() {
	readySounds.fill(-1);
	readyMusics.fill(-1);
	continueMusics.fill(false);
}

void SoundPlayer::setSound(const SoundID _id) {
	if (_id < 0 || _id >= SoundID::SOUND_NUM) {
		MessageBox(NULL, "効果音のセットで不正な値が渡されました", "", MB_OK);
		return;
	}
	readySounds[_id] = 1;
}

void SoundPlayer::setMusic(const MusicID _id) {
	if (_id < 0 || _id >= MusicID::MUSIC_NUM) {
		MessageBox(NULL, "BGMのセットで不正な値が渡されました", "", MB_OK);
		return;
	}
	readyMusics[_id] = 1;
}

void SoundPlayer::playSound() {
	for (int i = 0; i < SoundID::SOUND_NUM; ++i) {
		if (readySounds[i] > 0) {
			std::shared_ptr<AudioResource> sound = ResourceManager::getIns()->getSound((SoundID)i);
			if (sound->isValid()) {
				PlaySoundMem(sound->getResource(), DX_PLAYTYPE_BACK);
				readySounds[i] = 0;
			}
		}
	}
}

void SoundPlayer::playMusic() {
	for (int i = 0; i < MusicID::MUSIC_NUM; ++i) {
		if (readyMusics[i] > 0) {
			std::shared_ptr<AudioResource> music = ResourceManager::getIns()->getMusic((MusicID)i);
			if (music->isValid()) {
				PlaySoundMem(music->getResource(), DX_PLAYTYPE_LOOP, !continueMusics[i]);
				readyMusics[i] = 0;
				continueMusics[i] = false;
			}
		}
	}
}

void SoundPlayer::stopSound(const SoundID _id) {
	if (_id < 0 || _id >= SoundID::SOUND_NUM) {
		MessageBox(NULL, "効果音の停止で不正な値が渡されました", "", MB_OK);
		return;
	}
	std::shared_ptr<AudioResource> sound = ResourceManager::getIns()->getSound(_id);
	if (sound->isValid()) {
		StopSoundMem(sound->getResource());
	}
}

void SoundPlayer::stopMusic(const MusicID _id) {
	if (_id < 0 || _id >= MusicID::MUSIC_NUM) {
		MessageBox(NULL, "BGMの停止で不正な値が渡されました", "", MB_OK);
		return;
	}
	std::shared_ptr<AudioResource> music = ResourceManager::getIns()->getMusic(_id);
	if (music->isValid()) {
		StopSoundMem(music->getResource());
	}
}

void SoundPlayer::continueMusic(const MusicID _id) {
	if (_id < 0 || _id >= MusicID::MUSIC_NUM) {
		MessageBox(NULL, "BGMの再開で不正な値が渡されました", "", MB_OK);
		return;
	}
	readyMusics[_id] = 1;
	continueMusics[_id] = true;
}

void SoundPlayer::stopAll() {
	ResourceManager *resource_manager = ResourceManager::getIns();
	for (int i = 0; i < SoundID::SOUND_NUM; ++i) {
		if (readySounds[i] != -1) {
			std::shared_ptr<AudioResource> sound = ResourceManager::getIns()->getSound((SoundID)i);
			if (sound->isValid()) {
				StopSoundMem(sound->getResource());
			}
		}
	}
	for (int i = 0; i < MusicID::MUSIC_NUM; ++i) {
		if (readyMusics[i] != -1) {
			std::shared_ptr<AudioResource> music = ResourceManager::getIns()->getMusic((MusicID)i);
			if (music->isValid()) {
				StopSoundMem(music->getResource());
			}
		}
	}
}
