#include "Player.h"
#include <algorithm>
#include <cassert>

Player::~Player() {}

void Player::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& pos) {

	assert(model);

	model_ = model;
	camera_ = camera;

	worldTransform_.translation_ = pos;

	input_ = KamataEngine::Input::GetInstance();

	worldTransform_.Initialize();
}

// ワールド座標を取得
KamataEngine::Vector3 Player::GetWorldPosition() const {

	KamataEngine::Vector3 worldPos;

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

// 状態取得
bool Player::IsDead() const { return isDead_; }

bool Player::IsHit() const { return isHit_; }

bool Player::IsSwing() const { return isSwing_; }

// 状態変更
void Player::SetDead(bool flag) { isDead_ = flag; }

void Player::SetHit(bool flag) { isHit_ = flag; }

void Player::SetSwing(bool flag) { isSwing_ = flag; }

void Player::Update() {

	const float kRotateSpeed = 0.25f;
	const float kRotateLimit = 170.0f * (3.141592f / 180.0f);

	// 移動ベクトル
	KamataEngine::Vector3 move = {0, 0, 0};

	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;

	// 右入力
	if (input_->TriggerKey(DIK_D)) {
		targetRotationY_ = -kRotateLimit;
	}

	// 左入力
	if (input_->TriggerKey(DIK_A)) {
		targetRotationY_ = kRotateLimit;
	}

	// 回転補間
	rotationY_ += (targetRotationY_ - rotationY_) * kRotateSpeed;

	rotationY_ = std::clamp(rotationY_, -kRotateLimit, kRotateLimit);

	worldTransform_.rotation_.y = rotationY_;

	worldTransform_.updateMatrix();
}

void Player::Draw() { model_->Draw(worldTransform_, *camera_); }