#pragma once
#include <KamataEngine.h>
#include <list>

namespace KamataEngine {
	class Input;
};

class Stage {
public:
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& pos);
	void Update();
	void Draw();
	KamataEngine::Vector3 GetWorldPosition();

private:
	bool isDead_ = false;
	bool isR_ = false;
	bool isL_ = false;
	bool isHit_ = false;
	bool isSwing_ = false;
	KamataEngine::WorldTransform worldtransfrom_;

	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Model* model2_ = nullptr;

	KamataEngine::Input* input_ = nullptr;

	KamataEngine::Camera* camera_ = nullptr;

	KamataEngine::Vector3 velocity_ = {0, 0, 0};

	float rotationY_ = 0.0f;
	float targetRotationY_ = 0.0f;

	static inline const float kJumpAcceleration = 1.0f;
	static inline const float kLimitFallSpeed = 0.03f;
	bool onGround_ = true;

	static inline const float kGravityAcceleration = 0.5f;
};