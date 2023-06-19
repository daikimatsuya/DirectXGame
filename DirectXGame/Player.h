#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "AffineMatrixFunctions.h"
#include "PlayerBullet.h"
#include "MatrixFunctions.h"
#include "VectorFanctions.h"
#include "list"
#include "Sprite.h"


class Player {
public:
	Player();
	~Player();
	void Initialize(Model*model,uint32_t tectureHandle,Vector3 position);
	void Update();
	void Draw(const ViewProjection& viewProjection);
	void Rotate();
	void Attack();
	Vector3 GetWorldPosition();
	const std::list<PlayerBullet*>& GetBullets() { return bullets_; }
	void Setparent(const WorldTransform* parent);
	void OnCollision();

private:
	WorldTransform worldTrasform_;
	WorldTransform worldTransform3DReticle_;
	//ViewProjection viewProjection_;
	Model* model_ = nullptr;
	uint32_t tectureHandle_ = 0u;
	Input* input_ = nullptr;
	AffineMatrixFunctions* AMF_ = nullptr;
	MatrixFunctions* MF_ = nullptr;
	VectorFanctions* VF_ = nullptr;
	std::list<PlayerBullet*> bullets_;
	float inputFloat[3] = {};
	Sprite* sprite2DReticle_ = nullptr;
	
};

