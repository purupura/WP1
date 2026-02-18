#pragma once
#include "KamataEngine.h"
#include "Player.h"
#include "ball.h"
#include "Stage.h"

using namespace KamataEngine;

class GameScene {
public:
	/// <summary>
	/// デストクラタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	bool IsFinished() const { return isFinished_; }

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	Camera* camera_ = nullptr;
	
	Ball* ball_ = nullptr;
	Player* player_ = nullptr;
	Stage* stage_ = nullptr;

	//モデル
	Model* model = nullptr;
	Model* modelBall_ = nullptr;
	Model* modelPlayer_ = nullptr;
	Model* modelStage_ = nullptr;

	Vector3 playerPos = {-2, -4.0, -40};

	uint32_t textureHandle_ = 0;
	uint32_t textureHandle2_ = 0;
	Sprite* TestSprite_ = nullptr;
	bool isFinished_ = false;
	KamataEngine::Sprite* redRect_ = nullptr;
};
