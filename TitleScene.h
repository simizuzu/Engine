#pragma once
#include "BaseScene.h"
#include "TextureManager.h"
#include "Sprite.h"

// タイトルシーン
class TitleScene : public BaseScene
{
public: // メンバ関数

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize() override;

private:
	TextureData tex;
	std::unique_ptr<Sprite> sprite_;
};

