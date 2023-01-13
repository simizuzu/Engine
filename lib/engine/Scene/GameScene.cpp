#include "GameScene.h"

GameScene::~GameScene()
{
	delete camera_;
}

void GameScene::Initialize()
{
	input_ = Input::GetInstance();
	camera_ = new Camera();
	camera_->Initialize();


	// スプライト
	titleTex_ = TextureManager::Load("Resources/Texture/title.png");
	titleSprite_ = std::make_unique<Sprite>();
	titleSprite_->Initialize();

	// クラス
	player_ = std::make_unique<Player>();
	railCamera_ = std::make_unique<RailCamera>();
	resultCamera_ = std::make_unique<ResultCamera>();
	stage_ = std::make_unique<Stage>();
	skydome_ = std::make_unique<skydome>();
	objectManager_ = std::make_unique<ObjectManager>();
	speedUpChance_ = std::make_unique<SpeedUpChance>();
	doorManager_ = std::make_unique<DoorManager>();
	goalModel_ = std::make_unique<Goal>();

	player_->Initialize(railCamera_->GetWorldTransformPtr());
	railCamera_->Initialize(Mathematics::Vector3{ 0.0,0.0f,-10.0f }, { 0,0,0 });
	resultCamera_->Initialize(railCamera_->GetWorldTransformPtr());
	stage_->Initialize();
	skydome_->Initialize();
	objectManager_->Initialize(player_.get());
	doorManager_->Initialize(railCamera_->GetVector());
	speedUpChance_->Initialize(railCamera_.get());
	goalModel_->Initialize();

	camera_ = resultCamera_->GetViewProjection();
}

void GameScene::Update()
{
	switch (scene)
	{
	case Scene::title:
		railCamera_->Update(player_->GetCrashFlag(), frequencyInvocationDoor);
		resultCamera_->Update();
		player_->titleUpdate();
		if (input_->TriggerPushKey(DIK_SPACE))
		{
			titleParticleFrg = true;
		}
		if (titleParticleFrg == true)
		{
			titleParticleFrg = false;
			scene = Scene::game;
			camera_ = railCamera_->GetViewProjection();
			railCamera_->reset();
			player_->Update();
			objectManager_->Reset();
			startTime = static_cast<int>(time(NULL));
			nowTime = 0;
		}
		break;
	case Scene::game:
		if (startGameFrg && endGameFrg == false)
		{
			if (isActivationDoor == false)
			{
				if (railCamera_->Update(player_->GetCrashFlag(), frequencyInvocationDoor))
				{
					player_->SetTransform({ 0.0f, -2.0f, 10.0f });
					isActivationDoor = true;
					frequencyInvocationDoor++;
					player_->JumpReset();
				}
				player_->Update();
				objectManager_->Update();
				speedUpChance_->Update(player_.get());
				if (railCamera_->GetLap() >= 1)
				{
					endGameFrg = true;
					endTime = nowTime;
				}
				if (railCamera_->GetIsRapReset())
				{
					railCamera_->lapReset();
					doorManager_->Reset();
					frequencyInvocationDoor = 0;
				}
			}
			else
			{
				doorManager_->Update(frequencyInvocationDoor);
				if (doorManager_->GetMashFlag(frequencyInvocationDoor))
				{
					isActivationDoor = false;
				}
			}
			nowTime = static_cast<int>(time(NULL)) - startTime;
		}
		else if (startGameFrg == false)
		{
			if (4 <= time(NULL) - startTime)
			{
				startGameFrg = true;
				startTime = static_cast<int>(time(NULL));
			}
		}
		if (endGameFrg)
		{

			camera_ = resultCamera_->GetViewProjection();
			scene = Scene::result;
			endGameFrg = false;
			startGameFrg = false;
			railCamera_->setSpeed(1.0f);
			player_->EndGameReset();

			/*numTransform[0].translation = { 830,400,0 };
			numTransform[1].translation = { 900,400,0 };
			numTransform[2].translation = { 970,400,0 };*/

		}
		break;
	case Scene::result:
		railCamera_->Update(player_->GetCrashFlag(), frequencyInvocationDoor);
		player_->titleUpdate();
		resultCamera_->Update();
		if (input_->TriggerPushKey(DIK_SPACE))
		{
			resultParticleFrg = true;
		}
		if (resultParticleFrg == true)
		{
			scene = Scene::title;
			resultParticleFrg = false;

			/*numTransform[0].translation = { 570,55,0 };
			numTransform[1].translation = { 640,55,0 };
			numTransform[2].translation = { 710,55,0 };*/
		}
		break;
	case Scene::door:
		break;
	default:
		break;
	}
	camera_->Update();
}

void GameScene::Draw()
{
	switch (scene)
	{
	case GameScene::Scene::title:
		titleSprite_->DrawSprite(titleTex_, { 380, 120 });
		break;
	case GameScene::Scene::game:
		objectManager_->Draw(camera_);
		goalModel_->Draw(camera_);
		doorManager_->Draw(camera_);
		speedUpChance_->Draw(camera_);
		break;
	case GameScene::Scene::result:
		break;
	case GameScene::Scene::door:
		break;
	default:
		break;
	}
	player_->Draw(camera_);
	stage_->Draw();
	skydome_->Draw();


	switch (scene)
	{
	case GameScene::Scene::title:
		break;
	case GameScene::Scene::game:

		if (isActivationDoor)
		{
			doorManager_->SpriteDraw();
		}
		/*transform_.Update(camera_);
		sprite_->Draw(textureHandle_, transform_);*/

		break;
	case GameScene::Scene::result:

		break;
	case GameScene::Scene::door:
		break;
	default:
		break;
	}
}
