#pragma once
#include <memory>

#include "lib/engine/3D/Model/Model.h"
#include "lib/engine/3D/Model/Object3d.h"

class skydome
{
public:
	// コンストラクタ・デストラクタ
	skydome() = default;
	~skydome() = default;

	void Initialize();

	void Update(Camera* camera);

	void Draw();

private:
	// ワールドトランスフォーム
	std::shared_ptr<Object3d> transform_;
	// モデル
	std::shared_ptr<Model> model_;

	//コピーコンストラクタ・代入演算子削除
	skydome& operator=(const skydome&) = delete;
	skydome(const skydome&) = delete;
};

