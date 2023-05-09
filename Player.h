#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "AffineMatrixFunctions.h"


class Player {
public:
	Player();
	~Player();
	void Initialize(Model*model,uint32_t tectureHandle);
	void Update();
	void Draw(ViewProjection viewProjection);

private:
	WorldTransform worldTrasform_;
	ViewProjection viewProjection_;
	Model* model_ = nullptr;
	uint32_t tectureHandle_ = 0u;
	Input* input_ = nullptr;
	AffineMatrixFunctions* AMF_ = nullptr;
	float inputFloat[3] = {};
};

