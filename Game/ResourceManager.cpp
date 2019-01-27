#include "ErrorMessage.h"
#include "ResourceManager.h"
#include "Resource.h"


ResourceManager::ResourceManager() {
	release();
}

void ResourceManager::load(const SceneID _id) {
	switch (_id) {
	case SCENE_LOGO:
		addTexture(TEXTURE_LOGO, std::make_shared<TextureResource>("Protected/Logo.png"));
		addTexture(TEXTURE_LOGO2, std::make_shared<TextureResource>("Protected/Logo2.png"));
		break;
	case SCENE_TITLE:
		break;
	case SCENE_PLAY:
		addTexture(TEXTURE_MAPCHIP, std::make_shared<TextureResource>("Protected/tile.png", 6, 6, 1, 32, 32));
		addTexture(TEXTURE_PLAYER, std::make_shared<TextureResource>("Protected/player.png", 12, 3, 4, 48, 48));
		addTexture(TEXTURE_ENEMY1, std::make_shared<TextureResource>("Protected/enemy1.png", 96, 12, 8, 48, 64));
		addTexture(TEXTURE_TENT, std::make_shared<TextureResource>("Protected/tent2.png"));
		addTexture(TEXTURE_FIRE, std::make_shared<TextureResource>("Protected/fire.png", 4, 4, 1, 32, 32));
		addTexture(TEXTURE_CROSSBOW, std::make_shared<TextureResource>("Protected/cross_bow.png"));
		addTexture(TEXTURE_LIGHT1, std::make_shared<TextureResource>("light3.png"));
		addTexture(TEXTURE_FLASHLIGHT, std::make_shared<TextureResource>("flashlight2.png"));
		addTexture(TEXTURE_ARROW, std::make_shared<TextureResource>("Protected/arrow.png", 3, 3, 1, 32, 32));
		break;
	case SCENE_RESULT:
		break;
	default:
		ErrorMessage("読み込みデータの選択で不正な値が渡されました");
		break;
	}
}

void ResourceManager::release() {
	textures.clear();
	textures.shrink_to_fit();
	texturesIndex.fill(-1);
	sounds.clear();
	sounds.shrink_to_fit();
	soundsIndex.fill(-1);
	musics.clear();
	musics.shrink_to_fit();
	musicsIndex.fill(-1);
	movies.clear();
	movies.shrink_to_fit();
	moviesIndex.fill(-1);
	fonts.clear();
	fonts.shrink_to_fit();
	fontsIndex.fill(-1);
}

std::shared_ptr<TextureResource> ResourceManager::getTexture(const TextureID _id) {
	int index = texturesIndex[_id];
	if (index == -1) {
		ErrorMessage("画像の取得で不正な値が渡されました");
		return nullptr;
	}
	return textures[index];
}

std::shared_ptr<AudioResource> ResourceManager::getSound(const SoundID _id) {
	int index = soundsIndex[_id];
	if (index == -1) {
		ErrorMessage("効果音の取得で不正な値が渡されました");
		return nullptr;
	}
	return sounds[index];
}

std::shared_ptr<AudioResource> ResourceManager::getMusic(const MusicID _id) {
	int index = musicsIndex[_id];
	if (index == -1) {
		ErrorMessage("BGMの取得で不正な値が渡されました");
		return nullptr;
	}
	return musics[index];
}

std::shared_ptr<MovieResource> ResourceManager::getMovie(const MovieID _id) {
	int index = moviesIndex[_id];
	if (index == -1) {
		ErrorMessage("動画の取得で不正な値が渡されました");
		return nullptr;
	}
	return movies[index];
}

std::shared_ptr<FontResource> ResourceManager::getFontHandle(const FontID _id) {
	int index = fontsIndex[_id];
	if (index == -1) {
		ErrorMessage("フォントハンドルの取得で不正な値が渡されました");
		return nullptr;
	}
	return fonts[index];
}

bool ResourceManager::addTexture(const TextureID _id, const std::shared_ptr<TextureResource> _texture) {
	if (!_texture->isValid()) {
		ErrorMessage("画像の読み込みに失敗しました");
		return false;
	}
	texturesIndex[_id] = textures.size();
	textures.emplace_back(_texture);
	return true;
}

bool ResourceManager::addSound(const SoundID _id, const std::shared_ptr<AudioResource>& _sound) {
	if (!_sound->isValid()) {
		ErrorMessage("効果音の読み込みに失敗しました");
		return false;
	}
	soundsIndex[_id] = sounds.size();
	sounds.emplace_back(_sound);
	return true;
}

bool ResourceManager::addMusic(const MusicID _id, const std::shared_ptr<AudioResource>& _music) {
	if (!_music->isValid()) {
		ErrorMessage("BGMの読み込みに失敗しました");
		return false;
	}
	musicsIndex[_id] = musics.size();
	musics.emplace_back(_music);
	return true;
}

bool ResourceManager::addMovie(const MovieID _id, const std::shared_ptr<MovieResource>& _movie) {
	if (!_movie->isValid()) {
		ErrorMessage("動画の読み込みに失敗しました");
		return false;
	}
	moviesIndex[_id] = movies.size();
	movies.emplace_back(_movie);
	return true;
}

bool ResourceManager::addFont(const FontID _id, const std::shared_ptr<FontResource>& _font) {
	if (!_font->isValid()) {
		ErrorMessage("フォントの読み込みに失敗しました");
		return false;
	}
	fontsIndex[_id] = fonts.size();
	fonts.emplace_back(_font);
	return true;
}

