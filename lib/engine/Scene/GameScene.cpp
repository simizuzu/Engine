#include "GameScene.h"

void GameScene::Initialize()
{
	GameCamera_ = std::make_unique<GameCamera>();
	GameCamera_->Initialize();
	input_ = Input::GetInstace();

	player_ = std::make_unique<Player>();
	player_->Initialize();

	skydomeModel.reset(Model::LoadFromObj("skydome"));
	groundModel.reset(Model::LoadFromObj("ground"));
	skydomeObject.reset(Object3d::Create());
	groundObject.reset(Object3d::Create());
	skydomeObject->SetModel(skydomeModel.get());
	groundObject->SetModel(groundModel.get());

	skydomeObject->SetScale({1000.0f,1000.0f,1000.0f});

	titleBGM = AudioManager::GetInstance()->LoadAudio("Resources/music/title.mp3", 0.05f);
	gameBGM = AudioManager::GetInstance()->LoadAudio("Resources/music/gameScene.mp3",0.05f);
	AudioManager::GetInstance()->PlayWave(titleBGM, true);
	titleTex = TextureManager::GetInstance()->Load("Resources/Texture/title.png");
	titleBack = std::make_unique<Sprite>();
	titleBack->Initialize();
}

void GameScene::Update()
{
	switch (sceneNum)
	{
	case 0: // �^�C�g���V�[��
		if (input_->TriggerButton(A) || input_->TriggerPushKey(DIK_SPACE))
		{
			sceneNum = 1; // �Q�[���V�[����
		}
		break;

	case 1: // �Q�[���V�[��
		AudioManager::GetInstance()->StopWave(titleBGM);
		AudioManager::GetInstance()->PlayWave(gameBGM, true);

		enemys_.remove_if([](std::shared_ptr<Enemy>& enemy)
			{
				return enemy->IsDead();
			});

		if (enemys_.empty())
		{
			Mathematics::Vector3 position = { -12000.0f,4000.0f,12000.0f }; // ����
			std::unique_ptr<Enemy> enemy_ = std::make_unique<Enemy>();
			enemy_->Initialize();
			enemy_->SetControlPoint(enemy2); // �X�^�[�g�n�_
			enemys_.push_back(std::move(enemy_));

			position = { 12000.0f,2000.0f,12000.0f };//�E��
			enemy_ = std::make_unique<Enemy>();
			enemy_->Initialize();
			enemy_->SetControlPoint(enemy3); // �X�^�[�g�n�_
			enemys_.push_back(std::move(enemy_));

			position = { 12000.0f,4000.0f,-12000.0f };//�E��
			enemy_ = std::make_unique<Enemy>();
			enemy_->Initialize();
			enemy_->SetControlPoint(enemy4); // �X�^�[�g�n�_
			enemys_.push_back(std::move(enemy_));

			position = { -12000.0f,2000.0f,-12000.0f };//����
			enemy_ = std::make_unique<Enemy>();
			enemy_->Initialize();
			enemy_->SetControlPoint(enemy5); // �X�^�[�g�n�_
			enemys_.push_back(std::move(enemy_));

			destroyFlag++;
		}

		if (destroyFlag > 1)
		{
			Reset();
			sceneNum = 3;//�Q�[���N���A�V�[����
		}

		GameCamera_->Update();

		for (std::shared_ptr<Enemy>& enemy : enemys_)
		{
			enemy->Update();
		}

		player_->Update(GameCamera_->GetCamera(), sceneNum);

		Collision();

		skydomeObject->Update(GameCamera_->GetCamera());
		groundObject->Update(GameCamera_->GetCamera());

		break;
	case 2:
		AudioManager::GetInstance()->StopWave(gameBGM);
		if (input_->TriggerButton(A) || input_->TriggerPushKey(DIK_SPACE))
		{
			Reset();
			AudioManager::GetInstance()->StopWave(titleBGM);
			AudioManager::GetInstance()->PlayWave(titleBGM, true);
			sceneNum = 0;//A�{�^���������ƃ^�C�g���V�[����
		}
		break;

	case 3:
		//�Q�[���N���A�V�[��
		AudioManager::GetInstance()->StopWave(gameBGM);
		AudioManager::GetInstance()->StopWave(playerData.fighterSE);
		if (input_->TriggerButton(A) || input_->TriggerPushKey(DIK_SPACE))
		{
			Reset();
			AudioManager::GetInstance()->StopWave(gameClearBGM);
			AudioManager::GetInstance()->PlayWave(titleBGM, true);
			sceneNum = 0;//A�{�^���������ƃ^�C�g���V�[����
		}
		break;
	}
}

void GameScene::Draw()
{
	switch (sceneNum)
	{
	case 0: // �^�C�g���V�[��
		titleBack->DrawSprite(titleTex, { 0.0f,0.0f });

		break;

	case 1: // �Q�[���V�[��
		// �V��
		skydomeObject->Draw();
		// �n��
		groundObject->Draw();
		// �v���C���[
		player_->Draw();
		// �G
		for (std::shared_ptr<Enemy>& enemy : enemys_)
		{
			enemy->Draw();
		}
		break;

	case 2:
		break;

	case 3:
		break;
	}

}

GameScene* GameScene::GetInstance()
{
	static GameScene instance;
	return &instance;
}

int GameScene::GetSceneNum()
{
	return sceneNum;
}

void GameScene::SetSceneNum(int sceneNumber)
{
	sceneNumber = sceneNum;
}

void GameScene::Collision()
{
	collisionManager_->ListClear();

	//�R���C�_�[�����X�g�ɓo�^
	//���L����
	collisionManager_->ColliderSet(player_.get());

	//�G�L�����̂��ׂ�
	for (const std::shared_ptr<Enemy>& enemy : enemys_)
	{
		collisionManager_->ColliderSet(enemy.get());
	}

	//�Փ˔���
	collisionManager_->CheckCollisions();
}

void GameScene::Reset()
{
	enemys_.clear();
	destroyFlag = 0;

	gameCamera->SetPos({ 0.0f, 4000.0f, -5000.0f });
	player_.reset();
	player_ = std::make_unique<Player>();
	Mathematics::Vector3 pos = { 0.0f, -18.0f, 30.0f };
	player_->Initialize();

	// �e�𐶐����A������
	Mathematics::Vector3 position = { 0.0f,4000.0f,8000.0f };
	std::shared_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
	newEnemy->Initialize();
	newEnemy->SetControlPoint(enemy1);
	//�e��o�^����
	enemys_.push_back(std::move(newEnemy));
}
