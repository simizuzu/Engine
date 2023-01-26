#pragma once

// ゲーム全体
class Framework
{
public: // メンバ関数
	virtual ~Framework() = default;
	// 初期化
	virtual void Initialize();
	// 更新
	virtual void Finalize();
	// 毎フレーム更新
	virtual void Update();
	// 描画
	virtual void Draw() = 0;
	// 終了チェック
	virtual bool IsEndRequest();

	// 実行
	void Run();

private:
	// ゲーム終了フラグ
	bool endRequest_ = false;

	
};

