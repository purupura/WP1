#include "GameScene.h"
GameScene::~GameScene() { 
	delete modelPlayer_;
	delete player_;
	delete model_;
}

void GameScene::Initialize() {
	dxCommon_ = KamataEngine::DirectXCommon::GetInstance(); 
	input_ = KamataEngine::Input::GetInstance();            
	audio_ = KamataEngine::Audio::GetInstance();
	//==============================================================
	// カメラ生成
	//==============================================================
	camera_ = new Camera();                            
	camera_->Initialize();
	worldTransform_.Initialize();
	//==============================================================
	// スプライト生成
	//==============================================================
	uint32_t redTex = TextureManager::Load("white1x1.png");
	redRect_ = Sprite::Create(redTex, {0, 0});
	textureHandle_ = KamataEngine::TextureManager::Load("LE3D.jpg");
	TestSprite_ = Sprite::Create(textureHandle_, {0, 0});
	//==============================================================
	// モデル読み込み
	//==============================================================
	model_ = KamataEngine::Model::Create();
	modelPlayer_ = KamataEngine::Model::CreateFromOBJ("player", true);
	modelBall_ = KamataEngine::Model::CreateFromOBJ("ball", true);
	modelStage_ = KamataEngine::Model::CreateFromOBJ("stage", true);
	//==============================================================
	//オブジェクト生成
	//==============================================================
	player_ = new Player();
	player_->Initialize(modelPlayer_, camera_, textureHandle_);
	ball_ = new Ball();
	ball_->Initialize(modelBall_, camera_, {0,-1.0,10});
	stage_ = new Stage();
	stage_->Initialize(modelStage_, camera_, {-40, -10, 50});
	//==============================================================
}

void GameScene::Update() {
	// ビュープロジェクションの初期化
	// camera_.Initialize();
	if (input_->TriggerKey(DIK_SPACE)) {
		isFinished_ = true;
	}
	player_->Update();
	ball_->Update();
	stage_->Update();
	
}

void GameScene::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();
//==============================================================
#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	KamataEngine::Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
	/// 
	redRect_->SetPosition({590, 500}); // x,y
	redRect_->SetSize({100, 100});     // 幅, 高さ
	redRect_->Draw();

	// スプライト描画後処理
	KamataEngine::Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
//==============================================================

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	KamataEngine::Model::PreDraw();

	modelPlayer_->Draw();

	/// <summary>
	/// ここにモデルの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	KamataEngine::Model::PostDraw();
#pragma endregion

//==============================================================
#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	KamataEngine::Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	// スプライト描画後処理
	// TestSprite_->Draw();

	// スプライト描画後処理
	KamataEngine::Sprite::PostDraw();

#pragma endregion
//==============================================================
}
