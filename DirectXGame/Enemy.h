#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "AffineMatrixFunctions.h"
#include "Vector3.h"
#include "list"
#include "EnemyBullet.h"
#include "VectorFanctions.h"
class Player;
class Enemy {
public:
	Enemy();
	~Enemy();
	void Initialize(Model* model,uint32_t textureHandle);
	void Update();
	void Draw(const ViewProjection& viewProjection);
	void Fire();
	void InitializeBulletPhase();
	void SetPlayer(Player* player) { player_ = player; };
	Vector3 GetWorldPosition();
	const std::list<EnemyBullet*>& GetBullets() { return bullets_; }
	void OnCollision();

	static const int kInterval = 60;
private:
	enum Phase {
		Approach,	//接近
		Leave,		//離脱
	};
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	Player* player_ = nullptr;
	Vector3 AproachVelocity_ = {0,0,0};
	Vector3 LeaveVelocity_ = {0,0,0};
	uint32_t textureHandle_ = 0;
	AffineMatrixFunctions amf_;
	VectorFanctions vf_;
	Phase phase_ = Approach;
	std::list<EnemyBullet*> bullets_;
	uint32_t intervalTimer = 0;

};
