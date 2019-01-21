#pragma once
#include "Singleton.h"
#include <array>



enum ShaderID {
	SHADER_NONE = -1,
	SHADER_LIGHT,
	SHADER_NUM
};



class ShaderManager : public Singleton<ShaderManager> {

	friend Singleton<ShaderManager>;

private:
	VERTEX2DSHADER vertex[4];
	std::array<int, ShaderID::SHADER_NUM> shaderHandles;
	ShaderID currentShader;

public:
	ShaderManager();

public:
	void update();
	void draw();

public:
	bool setShader(const ShaderID _id);

private:
	void drawShaderLight();
};


