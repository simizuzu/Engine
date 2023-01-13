#include "Player.h"
#include <cassert>

void Player::Initialize(Mathematics::Vector3 pos, PlayerData data)
{
	// �V���O���g��
	input_ = Input::GetInstace();

	// NULL�|�C���^�`�F�b�N
	assert(model);

	playerObject_.reset(Object3d::Create());
	playerObject_->SetModel(model.get());

	playerObject_->SetScale({ 1.0f,1.0f,1.0f });
}

void Player::Update(Camera* camera,INT32& sceneNum)
{
	// �s���]��
	playerObject_->Update(camera);

	if (initflag)
	{
		AudioManager::GetInstance()->PlayWave(fighterSE, true);
		initflag = false;
	}

	oldTranslation_ = GetWorldPosition();

	if (animationFlag == false)
	{
		PlayerMove(sceneNum);
		Rotate();
		transform_->Update(camera_->GetThirdPersonCamera());
	}
	UpdateOBB(*transform_);

	//�̗͂�0�ȉ��ɂȂ�����
	if (hp <= 0)
	{
		//�Q�[���I�[�o�[�V�[��
		if (animationFlag == false)
		{
			AudioManager::GetInstance()->StopWave(fighterSE);
		}
		animationFlag = true;
		if (animationFlag == true)
		{
			alpha += 1.0f / 60;
		}

		if (alpha >= 1.0f)
		{
			animationFlag = false;
			AudioManager::GetInstance()->PlayWave(gameOverScene, true);
			uint32_t gameScene = AudioManager::GetInstance()->LoadAudio("Resources/sano/gameScene.mp3");
			AudioManager::GetInstance()->StopWave(gameScene);
			sceneNum = 2;
		}
	}

	silenPullUp->Update(silenPullUpTransform);
	silenReturn->Update(silenReturnTransform);

	WorldPos = camera_->GetWorldPosition();
	velocity2 = { 0, 0, 5000.0f };
	tmp = velocity2 = AliceMathF::Vec3Mat4Mul(velocity2, camera_->GetFirstPersonTransform()->matWorld);

	tmpTrasn.translation = WorldPos;
	tmpTrasn.TransUpdate(camera_->GetThirdPersonCamera());

	//�I������
	if (GetWorldPosition().x <= -11600 || GetWorldPosition().x >= 11600 || GetWorldPosition().z <= -11600 || GetWorldPosition().z >= 11600)
	{
		animationFlag = true;
		if (animationFlag == true)
		{
			alpha += 1.0f / 100;
		}

		if (alpha >= 1.0f)
		{
			animationFlag = false;
			AudioManager::GetInstance()->StopWave(fighterSE);
			AudioManager::GetInstance()->PlayWave(gameOverScene, true);
			sceneNum = 2;
		}
	}

	if (GetWorldPosition().y >= 11600 || GetWorldPosition().y <= 0)
	{
		animationFlag = true;
		if (animationFlag == true)
		{
			alpha += 1.0f / 60;
		}

		if (alpha >= 1.0f)
		{
			animationFlag = false;
			AudioManager::GetInstance()->StopWave(fighterSE);
			AudioManager::GetInstance()->PlayWave(gameOverScene, true);
			sceneNum = 2;
		}
	}

	if (damageFlag == true)
	{
		damageAlpha -= 0.5f / 60;
		if (damageAlpha <= 0)
		{
			damageFlag = false;
		}
	}
	else
	{
		damageAlpha = 0.5f;
	}

	sceneChange->Update(sceneChangeTransform, { 1.0,1.0,1.0,alpha });
	damageEffect->Update(damageEffectTransform, { 1.0,1.0,1.0,damageAlpha });
}

void Player::Draw()
{
	playerObject_->Draw();
	if (input_->TriggerPushKey(DIK_SPACE))
	{
		
	}
}

void Player::PlayerMove(INT32& sceneNum)
{
	//���ړ�
	//�R���g���[���[����
	Complement(transform_->position.x, -input_->GetLeftStickVec({ 1.0f,1.0f }).x * 30, 40);
	//�L�[�{�[�h����
	Complement(transform_->position.x, input_->GetKeyTime(DIK_A) / 254.0f * 30, 40);
	Complement(transform_->position.x, -input_->GetKeyTime(DIK_D) / 254.0f * 30, 40);
}

void Player::Rotate()
{
	//���񏈗�
	//�R���g���[���[����
	Complement(transform_->rotation.z, -input_->GetLeftStickVec({ 1.0f,1.0f }).x * 40.0f * MyMathUtility::degree2Radius, 40);//��
	//�L�[�{�[�h����
	Complement(transform_->rotation.z, input_->GetKeyTime(DIK_A) / 254.0f * 40.0f * MyMathUtility::degree2Radius, 40);
	Complement(transform_->rotation.z, -input_->GetKeyTime(DIK_D) / 254.0f * 40.0f * MyMathUtility::degree2Radius, 40);
}

void Player::Complement(float& x1, float x2, float flame)
{
	MyMathUtility::Complement(x1, x2, flame);
}

void Player::OnCollision()
{
}

Object3d* Player::GetTransform()
{
	return nullptr;
}

Mathematics::Vector3 Player::GetWorldPosition()
{
	return Mathematics::Vector3();
}
