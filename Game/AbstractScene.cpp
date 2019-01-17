#include "AbstractScene.h"


/// <summary>
/// シーン切り替えインタフェースの登録
/// </summary>
/// <param name="_impl">リスナーへのポインタ</param>
AbstractScene::AbstractScene(RequestSceneListener *_impl)
	: implRequestScene(_impl) {
}

