#include "ObjectManager.h"

void ObjectManager::Initialize(Player* player)
{
	player_ = player;
	objectModel_ = std::make_unique<Model>();
	objectModel_.reset(Model::LoadFromObj("cube"));
	cubeObject_ = std::make_unique<Object3d>();
	cubeObject_.reset(Object3d::Create());
	cubeObject_->SetModel(objectModel_.get());

	aabbToSphere_ = std::make_unique<BoundingBox>();
	
	Reset();
}

void ObjectManager::Reset()
{
	objects_.clear();

	std::unique_ptr<Object> object;

	//最初の道	|
	object = std::make_unique<Object>();
	object->Initialize({ -1.5f, -1.5f, 280.0f }, { 0.0f, 0.0f, 0.0f }, 1.0f, objectModel_.get());

	objects_.push_back(std::move(object));

	object = std::make_unique<Object>();
	object->Initialize({ 1.5f, -1.5f, 300.0f }, { 0.0f, 0.0f, 0.0f }, 1.0f, objectModel_.get());

	objects_.push_back(std::move(object));

	//道ふさぎ
	for (float i = 0; i < 10; i++)
	{
		object = std::make_unique<Object>();
		object->Initialize({ 10.0f - i * 2.0f, -1.5f, 400.0f }, { 0.0f, 0.0f, 0.0f }, 1.0f, objectModel_.get());

		objects_.push_back(std::move(object));
	}

	//道ふさぎ
	for (float i = 0; i < 10; i++)
	{
		object = std::make_unique<Object>();
		object->Initialize({ 10.0f - i * 2.0f, -1.5f, 500.0f }, { 0.0f, 0.0f, 0.0f }, 1.0f, objectModel_.get());

		objects_.push_back(std::move(object));
	}

	//二個目の道	/

	//両脇塞ぎ

	for (float i = 0; i < 3; i++)
	{
		for (float j = 0; j < 8; j++)
		{
			if (j != 3 && j != 4)
			{
				object = std::make_unique<Object>();
				object->Initialize({ 67.0f - j * 1.75f, 2.5f - 2.0f * i, 850.0f + j * 1.0f }, { 0.0f, 30.0f * MyMathUtility::degree2Radius, 0.0f }, 1.0f, objectModel_.get());
				objects_.push_back(std::move(object));
			}
		}
	}

	//道ふさぎ
	for (float j = 0; j < 9; j++)
	{

		object = std::make_unique<Object>();
		object->Initialize({ 298.0f - j * 1.75f, -1.5f , 1250.0f + j * 1.0f }, { 0.0f, 30.0f * MyMathUtility::degree2Radius, 0.0f }, 1.0f, objectModel_.get());
		objects_.push_back(std::move(object));
	}

	//3個目の道

	//道ふさぎ
	for (float k = 0; k < 3; k++)
	{
		for (float j = 0; j < 7; j++)
		{
			for (float i = 0; i < 5; i++)
			{
				object = std::make_unique<Object>();
				object->Initialize({ (490.0f + i * 1.75f) + j * 1.0f, 2.5f - 2.0f * k, (1200.0f + i * 1.0f) - j * 1.75f }, { 0.0f, 60.0f * MyMathUtility::degree2Radius, 0.0f }, 1.0f, objectModel_.get());
				objects_.push_back(std::move(object));
			}
		}
	}

	for (float k = 0; k < 3; k++)
	{
		for (float j = 0; j < 7; j++)
		{
			for (float i = 0; i < 5; i++)
			{
				object = std::make_unique<Object>();
				object->Initialize({ (653.5f + i * 1.75f) + j * 1.0f, 2.5f - 2.0f * k, (900.0f + i * 1.0f) - j * 1.75f }, { 0.0f, 60.0f * MyMathUtility::degree2Radius, 0.0f }, 1.0f, objectModel_.get());
				objects_.push_back(std::move(object));
			}
		}
	}

	//4個目の道

	//潜る
	for (float i = 0; i < 4; i++)
	{
		if (i != 1 && i != 2)
		{
			object = std::make_unique<Object>();
			object->Initialize({ 750.0f + i * 2.0f,-1.5f,440.3f }, { 0.0f, 0.0f, 0.0f }, 1.0f, objectModel_.get());

			objects_.push_back(std::move(object));
		}
		else
		{
			object = std::make_unique<Object>();
			object->Initialize({ 750.0f + i * 2.0f,0.5f,440.3f }, { 0.0f, 0.0f, 0.0f }, 1.0f, objectModel_.get());

			objects_.push_back(std::move(object));
		}

	}

	//潜る
	for (float i = 0; i < 4; i++)
	{
		if (i != 1 && i != 2)
		{
			object = std::make_unique<Object>();
			object->Initialize({ 744.0f + i * 2.0f,-1.5f,160.0f }, { 0.0f, 0.0f, 0.0f }, 1.0f, objectModel_.get());

			objects_.push_back(std::move(object));
		}
		else
		{
			object = std::make_unique<Object>();
			object->Initialize({ 744.0f + i * 2.0f,0.5f,160.0f }, { 0.0f, 0.0f, 0.0f }, 1.0f, objectModel_.get());

			objects_.push_back(std::move(object));
		}

	}

	//道ふさぎ
	for (float i = 0; i < 10; i++)
	{
		object = std::make_unique<Object>();
		object->Initialize({ 740.0f + i * 2.0f, -1.5f, 70.0f }, { 0.0f, 0.0f, 0.0f }, 1.0f, objectModel_.get());

		objects_.push_back(std::move(object));
	}

	//5個目の道

	//潜る
	for (float i = 0; i < 8; i++)
	{
		if (i != 1 && i != 2 && i != 5 && i != 6)
		{
			object = std::make_unique<Object>();
			object->Initialize({ 699.0f - i * 1.75f, -1.5f , -100.0f + i * 1.0f }, { 0.0f, 30.0f * MyMathUtility::degree2Radius, 0.0f }, 1.0f, objectModel_.get());

			objects_.push_back(std::move(object));
		}
		else
		{
			object = std::make_unique<Object>();
			object->Initialize({ 699.0f - i * 1.75f, 0.5f , -100.0f + i * 1.0f }, { 0.0f, 30.0f * MyMathUtility::degree2Radius, 0.0f }, 1.0f, objectModel_.get());

			objects_.push_back(std::move(object));
		}

	}

	//道ふさぎ
	for (float k = 0; k < 3; k++)
	{
		for (float j = 0; j < 7; j++)
		{
			for (float i = 0; i < 5; i++)
			{
				object = std::make_unique<Object>();
				object->Initialize({ (586.0f - i * 1.75f) - j * 1.0f, 2.5f - 2.0f * k, (-284.0f + i * 1.0f) - j * 1.75f }, { 0.0f, 30.0f * MyMathUtility::degree2Radius, 0.0f }, 1.0f, objectModel_.get());
				objects_.push_back(std::move(object));
			}
		}
	}

	for (float k = 0; k < 3; k++)
	{
		for (float j = 0; j < 7; j++)
		{
			for (float i = 0; i < 5; i++)
			{
				object = std::make_unique<Object>();
				object->Initialize({ (506.0f - i * 1.75f) - j * 1.0f, 2.5f - 2.0f * k, (-439.0f + i * 1.0f) - j * 1.75f }, { 0.0f, 30.0f * MyMathUtility::degree2Radius, 0.0f }, 1.0f, objectModel_.get());
				objects_.push_back(std::move(object));
			}
		}
	}

	//6個目の道

	//道ふさぎ
	for (float i = 0; i < 9; i++)
	{
		object = std::make_unique<Object>();
		object->Initialize({ 50.0f + i * 1.75f, -1.5f, -100.0f + i * 1.0f }, { 0.0f,60.0f * MyMathUtility::degree2Radius, 0.0f }, 1.0f, objectModel_.get());

		objects_.push_back(std::move(object));
	}
}

void ObjectManager::Update()
{
	objects_.remove_if([](std::unique_ptr<Object>& call)
		{
			return call->GetIsDeath();
		});

	for (std::unique_ptr<Object>& object : objects_)
	{
		object->Update();

		if (aabbToSphere_->CheckAABBToSphere(player_->GetCollider(), object->GetCollider()))
		{
			object->OnCollision();
			player_->OnCollision();
		}
	}
}

void ObjectManager::Draw(Camera* camera)
{
	for (std::unique_ptr<Object>& object : objects_)
	{
		object->Draw(camera);
	}
}
