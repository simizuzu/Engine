#include "SceneFactory.h"
#include "TitleScene.h"
#include "GameScene.h"

BaseScene* SceneFactory::CreateScene(const std::string& sceneName)
{
    // ���̃V�[���𐶐�
    BaseScene* newScene = nullptr;

    if (sceneName == "TITLE") {
        newScene = new TitleScene();
    }
    else if (sceneName == "GAMEPLAY") {
        newScene = new GameScene();
    }

    return newScene;
}
