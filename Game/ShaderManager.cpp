#include "ErrorMessage.h"
#include "ShaderManager.h"
#include "ScreenInfo.h"
#include "RenderManager.h"



/// <summary>
/// �R���X�g���N�^
/// </summary>
ShaderManager::ShaderManager() 
	: vertex()
	, shaderHandles()
	, currentShader(ShaderID::SHADER_NONE) {
	for (int i = 0; i < 4; i++) {
		vertex[i].pos = VGet((i % 2)*(float)SCREEN_WIDTH, (i / 2)*(float)SCREEN_HEIGHT, 0);
		vertex[i].rhw = 1.0f;
		vertex[i].dif = GetColorU8(255, 255, 255, 255);
		vertex[i].spc = GetColorU8(0, 0, 0, 0);
		vertex[i].u = vertex[i].su = (float)(i % 2);
		vertex[i].v = vertex[i].sv = (float)(i / 2);
	}

	shaderHandles[ShaderID::SHADER_LIGHT] = LoadPixelShader("Resources/Shaders/LightShader.pso");

	for (const auto& load : shaderHandles) {
		if (load == -1) {
			ErrorMessage("�V�F�[�_�[�̓ǂݍ��݂Ɏ��s���܂���");
		}
	}
}

/// <summary>
/// �X�V����
/// </summary>
void ShaderManager::update() {
	switch (currentShader) {
	case ShaderID::SHADER_NONE:
		break;
	case ShaderID::SHADER_LIGHT:
		break;
	default:
		ErrorMessage("�g�p���̃V�F�[�_�[���s���ł�");
		break;
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void ShaderManager::draw() {
	switch (currentShader) {
	case ShaderID::SHADER_NONE:
		break;
	case ShaderID::SHADER_LIGHT:
		drawShaderLight();
		break;
	default:
		ErrorMessage("�g�p���̃V�F�[�_�[���s���ł�");
		break;
	}
}

/// <summary>
/// �g�p����V�F�[�_�[�̐ݒ�
/// </summary>
/// <param name="_id">�V�F�[�_�[ID</param>
/// <returns>
/// �V�F�[�_�[�̐ݒ�ɐ����������ǂ���
/// </returns>
bool ShaderManager::setShader(const ShaderID _id) {
	if (_id < ShaderID::SHADER_NONE || _id >= ShaderID::SHADER_NUM) {
		ErrorMessage("�g�p����V�F�[�_�[�̐ݒ�ŕs���Ȓl���n����܂���");
		return false;
	}
	
	if (_id != ShaderID::SHADER_NONE && shaderHandles[_id] == -1) {
		ErrorMessage("�ǂݍ��܂�Ă��Ȃ��V�F�[�_�[��ݒ肵�悤�Ƃ��܂���");
		return false;
	}

	currentShader = _id;
	return true;
}

/// <summary>
/// ���C�e�B���O�V�F�[�_�[�̕`��
/// </summary>
void ShaderManager::drawShaderLight() {
	RenderManager* render_manager = RenderManager::getIns();
	//�V�F�[�_�[�ɓn���摜�̃Z�b�g
	SetUseTextureToShader(0, render_manager->getScreen(ScreenType::MapScreen));
	SetUseTextureToShader(1, render_manager->getScreen(ScreenType::LightAlphaScreen));
	//�s�N�Z���V�F�[�_�[�̃Z�b�g
	SetUsePixelShader(shaderHandles[ShaderID::SHADER_LIGHT]);
	DrawPrimitive2DToShader(vertex, 4, DX_PRIMTYPE_TRIANGLESTRIP);
}
