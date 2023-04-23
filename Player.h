#pragma once

#include "Model.h"
#include "WorldTransform.h"

class Player {
public:
	Player();
	~Player();
	void Initialize(Model*model,uint32_t tectureHandle);
	void Update();
	void Draw();

private:
	WorldTransform worldTrasform_;
	Model* model_ = nullptr;
	uint32_t tectureHandle_ = 0u;
};

