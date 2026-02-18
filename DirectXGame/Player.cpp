#include "Player.h"
#include <algorithm>
#include <cassert>

Player::~Player() {}

void Player::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera,uint32_t texture) {

	assert(model);
	model_ = model;
	camera_ = camera;
	input_ = KamataEngine::Input::GetInstance();

}

// ワールド座標を取得
KamataEngine::Vector3 Player::GetWorldPosition() {

	// ワールド座標を入れる変数
	KamataEngine::Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = worldtransfrom_.matWorld_.m[3][0];
	worldPos.y = worldtransfrom_.matWorld_.m[3][1];
	worldPos.z = worldtransfrom_.matWorld_.m[3][2];

	return worldPos;
}

void Player::Update() {
	const float kRotateSpeed = 0.25f; // 補間スピード（小さいほどゆっくり）
	const float kRotateLimit = 170.0f * (3.141592f / 180.0f);

	// キャラクターの移動ベクトル
	KamataEngine::Vector3 move = {0, 0, 0};
	
	worldtransfrom_.translation_.x += move.x;
	worldtransfrom_.translation_.y += move.y;

	
	if (input_->TriggerKey(DIK_D)) {
		targetRotationY_ = -kRotateLimit; // 右へ170度
	}
	
	// 現在角度 → 目標角度へスムーズに近づける
	rotationY_ += (targetRotationY_ - rotationY_) * kRotateSpeed;

	// 念のため制限
	rotationY_ = std::clamp(rotationY_, -kRotateLimit, kRotateLimit);

	worldtransfrom_.rotation_.y = rotationY_;

	worldtransfrom_.updateMatrix();
}

void Player::Draw() { model_->Draw(worldtransfrom_, *camera_); }

