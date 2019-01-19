#include "ErrorMessage.h"
#include "ResourceManager.h"
#include "Resource.h"


ResourceManager::ResourceManager() {
	release();
}

void ResourceManager::load(const SceneID _id) {
	switch (_id) {
	case SCENE_LOGO:
		break;
	case SCENE_TITLE:
		break;
	case SCENE_PLAY:
		addTexture(TEXTURE_MAPCHIP_ALL, std::make_shared<TextureResource>("Protected/mapchip1.png"));
		addTexture(TEXTURE_MAPCHIP, std::make_shared<TextureResource>(getTexture(TEXTURE_MAPCHIP_ALL).get(), 11, 1, 64, 64, 4, 4, 4));
		addTexture(TEXTURE_PLAYER, std::make_shared<TextureResource>("Protected/player.png", 12, 3, 4, 48, 48));
		break;
	case SCENE_RESULT:
		break;
	default:
		ErrorMessage("�ǂݍ��݃f�[�^�̑I���ŕs���Ȓl���n����܂���");
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
		ErrorMessage("�摜�̎擾�ŕs���Ȓl���n����܂���");
		return nullptr;
	}
	return textures[index];
}

std::shared_ptr<AudioResource> ResourceManager::getSound(const SoundID _id) {
	int index = soundsIndex[_id];
	if (index == -1) {
		ErrorMessage("���ʉ��̎擾�ŕs���Ȓl���n����܂���");
		return nullptr;
	}
	return sounds[index];
}

std::shared_ptr<AudioResource> ResourceManager::getMusic(const MusicID _id) {
	int index = musicsIndex[_id];
	if (index == -1) {
		ErrorMessage("BGM�̎擾�ŕs���Ȓl���n����܂���");
		return nullptr;
	}
	return musics[index];
}

std::shared_ptr<MovieResource> ResourceManager::getMovie(const MovieID _id) {
	int index = moviesIndex[_id];
	if (index == -1) {
		ErrorMessage("����̎擾�ŕs���Ȓl���n����܂���");
		return nullptr;
	}
	return movies[index];
}

std::shared_ptr<FontResource> ResourceManager::getFontHandle(const FontID _id) {
	int index = fontsIndex[_id];
	if (index == -1) {
		ErrorMessage("�t�H���g�n���h���̎擾�ŕs���Ȓl���n����܂���");
		return nullptr;
	}
	return fonts[index];
}

bool ResourceManager::addTexture(const TextureID _id, const std::shared_ptr<TextureResource> _texture) {
	if (!_texture->isValid()) {
		ErrorMessage("�摜�̓ǂݍ��݂Ɏ��s���܂���");
		return false;
	}
	texturesIndex[_id] = textures.size();
	textures.emplace_back(_texture);
	return true;
}

bool ResourceManager::addSound(const SoundID _id, const std::shared_ptr<AudioResource>& _sound) {
	if (!_sound->isValid()) {
		ErrorMessage("���ʉ��̓ǂݍ��݂Ɏ��s���܂���");
		return false;
	}
	soundsIndex[_id] = sounds.size();
	sounds.emplace_back(_sound);
	return true;
}

bool ResourceManager::addMusic(const MusicID _id, const std::shared_ptr<AudioResource>& _music) {
	if (!_music->isValid()) {
		ErrorMessage("BGM�̓ǂݍ��݂Ɏ��s���܂���");
		return false;
	}
	musicsIndex[_id] = musics.size();
	musics.emplace_back(_music);
	return true;
}

bool ResourceManager::addMovie(const MovieID _id, const std::shared_ptr<MovieResource>& _movie) {
	if (!_movie->isValid()) {
		ErrorMessage("����̓ǂݍ��݂Ɏ��s���܂���");
		return false;
	}
	moviesIndex[_id] = movies.size();
	movies.emplace_back(_movie);
	return true;
}

bool ResourceManager::addFont(const FontID _id, const std::shared_ptr<FontResource>& _font) {
	if (!_font->isValid()) {
		ErrorMessage("�t�H���g�̓ǂݍ��݂Ɏ��s���܂���");
		return false;
	}
	fontsIndex[_id] = fonts.size();
	fonts.emplace_back(_font);
	return true;
}
