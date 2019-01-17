#pragma once

#include "AbstractScene.h"
#include "ScreenInfo.h"
#include <memory>






/// <summary>
/// �Q�[���N���X
/// </summary>
class Game : public RequestSceneListener {

private:
	using SceneFactoryMethod = std::unique_ptr<AbstractScene>(*)(RequestSceneListener *_impl);	//�V�[�������֐�

	std::unique_ptr<AbstractScene> nowScene;	                //���݂̃V�[��
	SceneID nextScene;							                //���Ɏ��s����V�[��
	SceneFactoryMethod sceneFactoryMethods[SceneID::SCENE_NUM];	//�V�[�������֐��̃|�C���^

public:
	Game();
	~Game();

	void changeScene();	//�V�[���؂�ւ�

public:
	void initialize(void);
	void update(void);
	void render(void);
	void finalize(void);

	void requestScene(const SceneID _id) override; 	//�V�[���؂�ւ��v��

private:
	void addScene(const SceneID _id, SceneFactoryMethod _scene_factory_method);
};
