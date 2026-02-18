#pragma once
class ball {};
#pragma once
#include <KamataEngine.h>
#include <list>

class Enemy;
class GameScene;

namespace KamataEngine {
class Input;
};

class Ball {
public:
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& pos);
	void Update();
	void Draw();
	~Ball();
	

	KamataEngine::Vector3 GetWorldPosition();

	static inline const float kWidth = 1.0f;
	static inline const float kHeight = 1.0f;

private:
	bool isDead_ = false;
	bool isR_ = false;
	bool isL_ = false;
	bool isHit_ = false;
	KamataEngine::WorldTransform worldTransform_;

	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Model* model2_ = nullptr;

	KamataEngine::Input* input_ = nullptr;

	KamataEngine::Camera* camera_ = nullptr;

	KamataEngine::Vector3 velocity_ = {0, 0, 0};

	float randomX_ = 0.0f;
	bool isRandomSet_ = false;

	static inline const float kGravityAcceleration = 0.5f;
};