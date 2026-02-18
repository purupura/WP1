#include "ball.h"
#include <algorithm>
#include <cassert>
#include <cstdlib> // rand
#include <ctime>   // time


Ball::~Ball() {}

void Ball::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& pos) {

	assert(model);
	model_ = model;
	camera_ = camera;
	worldTransform_.translation_ = pos;
	input_ = KamataEngine::Input::GetInstance();
	worldTransform_.Initialize();

	 std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

// ワールド座標を取得
KamataEngine::Vector3 Ball::GetWorldPosition() {

	// ワールド座標を入れる変数
	KamataEngine::Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Ball::Update() {

	// キャラクターの移動ベクトル
	KamataEngine::Vector3 move = {0, 0, 0};

	// キャラクターの移動速さ
	const float kCharacterSpeed = 0.3f;

	if (worldTransform_.translation_.z <= -40 && worldTransform_.translation_.z >= -50 && input_->PushKey(DIK_D)) {
		isHit_ = true;
	}

	if (isHit_) {
		// ヒットした瞬間に1回だけランダム値を作る
		if (!isRandomSet_) {
			// -1.0 ～ 1.0 の範囲
			randomX_ = (rand() / (float)RAND_MAX) * -1.0f - 1.0f;
			isRandomSet_ = true;
		}
		move.z += kCharacterSpeed;
		move.x += randomX_ * 0.2f; // 横に飛ばす強さ
	} else {
		move.z -= kCharacterSpeed;
	}

	worldTransform_.rotation_.y += 1.0f;

	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;

	worldTransform_.updateMatrix();

	ImGui::Begin("Ball");

	ImGui::Text("z: %.2f", worldTransform_.translation_.z);
	ImGui::End();
}

void Ball::Draw() { model_->Draw(worldTransform_, *camera_); }
