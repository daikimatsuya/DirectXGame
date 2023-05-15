#include "Enemy.h"

Enemy::Enemy(){

}

Enemy::~Enemy(){

}

void Enemy::Initialize(Model* model,uint32_t textureHandle) {
	model_ = model;
	worldTransform_.Initialize();
	textureHandle_ = textureHandle;
	worldTransform_.translation_ = {0,5,50};
	AproachVelocity_ = {0, 0, -0.2f};
	LeaveVelocity_ = {-0.5f, 0.2f, 0};
}

void Enemy::Update() { 
switch (phase_) {
	case Enemy::Approach:
	default:
		Vector3 tmp = amf_.Add(worldTransform_.translation_, AproachVelocity_);
		worldTransform_.translation_ = tmp;
		if (worldTransform_.translation_.z < 0.0f) {
			phase_ = Leave;
		}
		
		break;
	case Enemy::Leave:
		Vector3 tmp2 = amf_.Add(worldTransform_.translation_, LeaveVelocity_);
		worldTransform_.translation_ = tmp2;
		break;
	
	}
	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
