#pragma once
#include <KamataEngine.h>

namespace KamataEngine {
class Input;
}

class Player {
public:
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& pos);

	void Update();
	void Draw();

	~Player();

	// getter
	KamataEngine::Vector3 GetWorldPosition() const;

	bool IsDead() const;
	bool IsHit() const;
	bool IsSwing() const;

	// setter
	void SetDead(bool flag);
	void SetHit(bool flag);
	void SetSwing(bool flag);

	static inline const float kWidth = 1.0f;
	static inline const float kHeight = 1.0f;

private:
	bool isDead_ = false;
	bool isR_ = false;
	bool isL_ = false;
	bool isHit_ = false;
	bool isSwing_ = false;

	KamataEngine::WorldTransform worldTransform_;

	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Model* model2_ = nullptr;

	KamataEngine::Input* input_ = nullptr;

	KamataEngine::Camera* camera_ = nullptr;

	KamataEngine::Vector3 velocity_ = {0, 0, 0};

	float rotationY_ = 0.0f;
	float targetRotationY_ = 0.0f;

	static inline const float kJumpAcceleration = 1.0f;
	static inline const float kLimitFallSpeed = 0.03f;
	static inline const float kGravityAcceleration = 0.5f;

	bool onGround_ = true;
};