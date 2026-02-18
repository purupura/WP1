#include "Stage.h"
#include <algorithm>
#include <cassert>

void Stage::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& pos) {

	assert(model);
	model_ = model;
	camera_ = camera;
	worldtransfrom_.translation_ = pos;
	input_ = KamataEngine::Input::GetInstance();
	worldtransfrom_.Initialize();
}

// ワールド座標を取得
KamataEngine::Vector3 Stage::GetWorldPosition() {

	// ワールド座標を入れる変数
	KamataEngine::Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = worldtransfrom_.matWorld_.m[3][0];
	worldPos.y = worldtransfrom_.matWorld_.m[3][1];
	worldPos.z = worldtransfrom_.matWorld_.m[3][2];

	return worldPos;
}

void Stage::Update() {

	worldtransfrom_.updateMatrix();
}

void Stage::Draw() { model_->Draw(worldtransfrom_, *camera_); }
