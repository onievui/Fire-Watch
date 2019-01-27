#include "ErrorMessage.h"
#include "ShaderManager.h"
#include "ScreenInfo.h"
#include "RenderManager.h"



/// <summary>
/// コンストラクタ
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
			ErrorMessage("シェーダーの読み込みに失敗しました");
		}
	}
}

/// <summary>
/// 更新処理
/// </summary>
void ShaderManager::update() {
	switch (currentShader) {
	case ShaderID::SHADER_NONE:
		break;
	case ShaderID::SHADER_LIGHT:
		break;
	default:
		ErrorMessage("使用中のシェーダーが不正です");
		break;
	}
}

/// <summary>
/// 描画処理
/// </summary>
void ShaderManager::draw() {
	switch (currentShader) {
	case ShaderID::SHADER_NONE:
		break;
	case ShaderID::SHADER_LIGHT:
		drawShaderLight();
		break;
	default:
		ErrorMessage("使用中のシェーダーが不正です");
		break;
	}
}

/// <summary>
/// 使用するシェーダーの設定
/// </summary>
/// <param name="_id">シェーダーID</param>
/// <returns>
/// シェーダーの設定に成功したかどうか
/// </returns>
bool ShaderManager::setShader(const ShaderID _id) {
	if (_id < ShaderID::SHADER_NONE || _id >= ShaderID::SHADER_NUM) {
		ErrorMessage("使用するシェーダーの設定で不正な値が渡されました");
		return false;
	}
	
	if (_id != ShaderID::SHADER_NONE && shaderHandles[_id] == -1) {
		ErrorMessage("読み込まれていないシェーダーを設定しようとしました");
		return false;
	}

	currentShader = _id;
	return true;
}

/// <summary>
/// ライティングシェーダーの描画
/// </summary>
void ShaderManager::drawShaderLight() {
	RenderManager* render_manager = RenderManager::getIns();
	//シェーダーに渡す画像のセット
	SetUseTextureToShader(0, render_manager->getScreen(ScreenType::MapScreen));
	SetUseTextureToShader(1, render_manager->getScreen(ScreenType::LightAlphaScreen));
	//ピクセルシェーダーのセット
	SetUsePixelShader(shaderHandles[ShaderID::SHADER_LIGHT]);
	DrawPrimitive2DToShader(vertex, 4, DX_PRIMTYPE_TRIANGLESTRIP);
}
