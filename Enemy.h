#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "AffineMatrixFunctions.h"
#include "Vector3.h"
class Enemy {
public:
	Enemy();
	~Enemy();
	void Initialize(Model* model,uint32_t textureHandle);
	void Update();
	void Draw(const ViewProjection& viewProjection);

private:
	enum Phase {
		Approach,	//接近
		Leave,		//離脱
	};
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	Vector3 AproachVelocity_;
	Vector3 LeaveVelocity_;
	uint32_t textureHandle_ = 0;
	AffineMatrixFunctions amf_;
	Phase phase_ = Approach;
};
