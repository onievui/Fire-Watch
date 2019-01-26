#pragma once

#include "Singleton.h"
#include "SceneID.h"
#include "Resource.h"
#include "ResourceID.h"
#include <vector>
#include <array>


typedef int HGRP;    //グラフィックハンドル     
typedef int HSND;    //サウンドハンドル
typedef int HMOV;    //ムービーグラフィックハンドル    
typedef int HFNT;    //フォントハンドル





/// <summary>
/// リソース管理クラス
/// </summary>
class ResourceManager final : public Singleton<ResourceManager> {

	friend Singleton<ResourceManager>;

private:
	std::vector<std::shared_ptr<TextureResource>> textures;
	std::array<int, TEXTURE_NUM>                  texturesIndex;
	std::vector<std::shared_ptr<AudioResource>>   sounds;
	std::array<int, SOUND_NUM>                    soundsIndex;
	std::vector<std::shared_ptr<AudioResource>>   musics;
	std::array<int, MUSIC_NUM>                    musicsIndex;
	std::vector<std::shared_ptr<MovieResource>>   movies;
	std::array<int, MOVIE_NUM>                    moviesIndex;
	std::vector<std::shared_ptr<FontResource>>    fonts;
	std::array<int, FONT_NUM>                     fontsIndex;


public:
	ResourceManager();
	~ResourceManager() = default;

public:
	void load(const SceneID _id);
	void release();
	std::shared_ptr<TextureResource> getTexture(const TextureID _id);
	std::shared_ptr<AudioResource> getSound(const SoundID _id);
	std::shared_ptr<AudioResource> getMusic(const MusicID _id);
	std::shared_ptr<MovieResource> getMovie(const MovieID _id);
	std::shared_ptr<FontResource> getFontHandle(const FontID _id);

private:
	bool addTexture(const TextureID _id, const std::shared_ptr<TextureResource> _texture);
	bool addSound(const SoundID _id, const std::shared_ptr<AudioResource>& _sound);
	bool addMusic(const MusicID _id, const std::shared_ptr<AudioResource>& _music);
	bool addMovie(const MovieID _id, const std::shared_ptr<MovieResource>& _movie);
	bool addFont(const FontID _id, const std::shared_ptr<FontResource>& _font);
};




