#pragma once

// シーン基底クラス
class BaseScene
{
public: // メンバ関数

	virtual ~BaseScene() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update();
	
	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw();

	/// <summary>
	/// 終了処理
	/// </summary>
	virtual void Finalize();
};

