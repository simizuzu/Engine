#pragma once

#include <string>
#include "BaseScene.h"

/// <summary>
/// �V�[���t�@�N�g���[
/// </summary>
class AbstractSceneFactory
{
public:
	// ���z�f�X�g���N�^
	virtual ~AbstractSceneFactory() = default;
	// �V�[������
	virtual BaseScene* CreateScene(const std::string& sceneName) = 0;
};