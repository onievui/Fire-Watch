#pragma once
#include <string>
#include <vector>


template <class T>
class Resource {
protected:
	std::vector<T> resource;
	T              defaultResource;

public:
	Resource(const T& _resource)
		: defaultResource(_resource) {
		resource.clear();
	};
	virtual ~Resource() = default;

public:
	const T& getResource(const int _index = 0) {
		return (int)resource.size() > _index ? resource[_index] : defaultResource;
	}

	bool isValid(const int _index = 0) {
		return resource[_index] != defaultResource;
	}
};

class TextureResource : public Resource<HGRP> {
public:
	static const std::string TEXTURE_DIR;

public:
	TextureResource(const std::string& _filename);
	TextureResource(const std::string& _filename, const int _num, const int _xnum, const int _ynum, const int _width, const int _height);
	TextureResource(TextureResource* _texture, const int _xnum, const int _ynum, const int _width, const int _height,
		const int _offset_x, const int _offset_y, const int _padding);
	virtual ~TextureResource();
};

class AudioResource : public Resource<HSND> {
public:
	static const std::string AUDIO_DIR;

public:
	AudioResource(const std::string& _filename);
	virtual ~AudioResource();
};

class MovieResource : public Resource<HGRP> {
public:
	static const std::string MOVIE_DIR;

public:
	MovieResource(const std::string& _filename);
	virtual ~MovieResource();
};

class FontResource : public Resource<HFNT> {
protected:
	std::string fontName;

protected:
	FontResource(const HFNT resource, const std::string& _fontname);

public:
	FontResource(const std::string& _fontname, const int _size, const int _thick, const int _font_type = -1, const int _char_set = -1, const int _edge_size = -1, const int _italic = FALSE);
	virtual ~FontResource();

public:
	void addFontHandle(const int _size, const int _thick, const int _font_type = -1, const int _char_set = -1, const int _edge_size = -1, const int _italic = FALSE);
};

class FontFileResource : public FontResource
{
public:
	static const std::string FONT_DIR;

protected:
	std::string fileName;

public:
	FontFileResource(const std::string& _filename, const std::string& _fontname, int _size, int _thick, int _font_type = -1, int _char_set = -1, int _edge_size = -1, int _italic = FALSE);
	virtual ~FontFileResource();
};

