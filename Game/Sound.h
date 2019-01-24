#pragma once
#include "ResourceManager.h"



class SoundPlayer : public Singleton<SoundPlayer> {

	friend Singleton<SoundPlayer>;

private:
	std::array<int, SoundID::SOUND_NUM>  readySounds;
	std::array<int, MusicID::MUSIC_NUM>  readyMusics;
	std::array<bool, MusicID::MUSIC_NUM> continueMusics;

public:
	SoundPlayer();
	~SoundPlayer() = default;

public:
	void reset();
	void setSound(const SoundID _id);
	void setMusic(const MusicID _id);
	void playSound();
	void playMusic();
	void stopSound(const SoundID _id);
	void stopMusic(const MusicID _id);
	void continueMusic(const MusicID _id);
	void stopAll();

};