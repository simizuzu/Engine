#pragma once
#include "BaseScene.h"

class SceneManager final
{
public: // メンバ関数

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();

	// 次のシーン予約
	void SetNextScene(BaseScene* nextScene);

	static SceneManager* GetInstance();

private:
	// 今のシーン（実行中シーン）
	BaseScene* scene_ = nullptr;
	BaseScene* nextScene_ = nullptr;

	SceneManager() = default;
	~SceneManager() = default;
	SceneManager& operator=(const SceneManager&) = delete;
	SceneManager(const SceneManager&) = delete;
};

