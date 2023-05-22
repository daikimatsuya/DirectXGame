#pragma once
#include "WorldTransform.h"
#include "AffineMatrixFunctions.h"
#include "Model.h"
#include "Vector3.h"
class EnemyBullet {
public:
	EnemyBullet();
	~EnemyBullet();
	void Initialize(Model* model,const Vector3 position,const Vector3 velocity);
	void Update();
	void Draw(const ViewProjection viewProjection);
	void OnCollision();


private:
	WorldTransform worldTransform_;
	AffineMatrixFunctions amf_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0;
	Vector3 velocity_;
};
