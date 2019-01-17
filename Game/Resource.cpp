#include "Resource.h"

const std::string TextureResource::TEXTURE_DIR = "Resources/Textures/";
const std::string AudioResource::AUDIO_DIR = "Resources/Audio/";
const std::string MovieResource::MOVIE_DIR = "Resources/Movies/";
const std::string FontFileResource::FONT_DIR = "Resources/Fonts/";

TextureResource::TextureResource(const std::string& _filename)
	: Resource(-1) {
	resource.emplace_back(LoadGraph((TEXTURE_DIR + _filename).c_str()));
	if (resource.back() == defaultResource) {
		MessageBox(NULL, "‰æ‘œ‚Ì“Ç‚İ‚İ‚É¸”s‚µ‚Ü‚µ‚½", "", MB_OK);
	}
}

TextureResource::TextureResource(const std::string& _filename, const int _num, const int _xnum, const int _ynum, const int _width, const int _height)
	: Resource(-1) {
	resource.resize(_num);
	LoadDivGraph((TEXTURE_DIR + _filename).c_str(), _num, _xnum, _ynum, _width, _height, resource.data());
	if (resource.back() == defaultResource) {
		MessageBox(NULL, "‰æ‘œ‚Ì•ªŠ„“Ç‚İ‚İ‚É¸”s‚µ‚Ü‚µ‚½", "", MB_OK);
	}
}

TextureResource::TextureResource(TextureResource* _texture, const int _xnum, const int _ynum, const int _width, const int _height,
	const int _offset_x, const int _offset_y, const int _padding) 
	: Resource(-1) {
	for (int i = 0; i < _ynum; ++i) {
		for (int j = 0; j < _xnum; j++) {
			resource.emplace_back(DerivationGraph(_offset_x + (_width + _padding)*j, _offset_y + (_height + _padding)*i, _width, _height, _texture->resource[0]));
		}
	}
}

TextureResource::~TextureResource() {
	for (auto &data : resource) {
		if (data != defaultResource) {
			DeleteGraph(data);
		}
	}
}

AudioResource::AudioResource(const std::string& _filename)
	: Resource(-1) {
	resource.emplace_back(LoadSoundMem((AUDIO_DIR + _filename).c_str()));
	if (resource.back() == defaultResource) {
		MessageBox(NULL, "‰¹º‚Ì“Ç‚İ‚İ‚É¸”s‚µ‚Ü‚µ‚½", "", MB_OK);
	}
}

AudioResource::~AudioResource() {
	for (auto &data : resource) {
		if (data != defaultResource) {
			DeleteSoundMem(data);
		}
	}
}

MovieResource::MovieResource(const std::string& _filename)
	: Resource(-1) {
	resource.emplace_back(LoadGraph((MOVIE_DIR + _filename).c_str()));
	if (resource.back() == defaultResource) {
		MessageBox(NULL, "“®‰æ‚Ì“Ç‚İ‚İ‚É¸”s‚µ‚Ü‚µ‚½", "", MB_OK);
	}
}

MovieResource::~MovieResource() {
	for (auto &data : resource) {
		if (data != defaultResource) {
			DeleteGraph(data);
		}
	}
}

FontResource::FontResource(const HFNT resource, const std::string& _fontname)
	: Resource(resource) 
	, fontName(_fontname) {
}

FontResource::FontResource(const std::string& _fontname, const int _size, const int _thick, const int _font_type, const int _char_set, const int _edge_size, const int _italic) 
	: FontResource(-1, _fontname) {
	addFontHandle(_size, _thick, _font_type, _char_set, _edge_size, _italic);
} 

FontResource::~FontResource() {
	for (auto &data : resource) {
		if (data != defaultResource) {
			DeleteFontToHandle(data);
		}
	}
}

void FontResource::addFontHandle(const int _size, const int _thick, const int _font_type, const int _char_set, const int _edge_size, const int _italic) {
	resource.emplace_back(CreateFontToHandle(fontName.c_str(), _size, _thick, _font_type, _char_set, _edge_size, _italic));
	if (resource.back() == defaultResource) {
		MessageBox(NULL, "ƒtƒHƒ“ƒgƒnƒ“ƒhƒ‹‚Ì¶¬‚É¸”s‚µ‚Ü‚µ‚½", "", MB_OK);
	}
}

FontFileResource::FontFileResource(const std::string& _filename, const std::string& _fontname, int _size, int _thick, int _font_type, int _char_set, int _edge_size, int _italic) 
	: FontResource(-1, _fontname)
	, fileName(_filename) {
	if (AddFontResourceEx((FONT_DIR + fileName).c_str(), FR_PRIVATE, NULL) > 0) {
		addFontHandle(_size, _thick, _font_type, _char_set, _edge_size, _italic);
	}
	else {
		MessageBox(NULL, "ƒtƒHƒ“ƒg‚Ì“Ç‚İ‚İ‚É¸”s‚µ‚Ü‚µ‚½", "", MB_OK);
		fileName = "";
	}
}

FontFileResource::~FontFileResource() {
	if (fileName != "") {
		RemoveFontResourceEx((FONT_DIR + fileName).c_str(), FR_PRIVATE, NULL);
	}
}
