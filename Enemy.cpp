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
	velocity_ = {0, 0, -0.2f};
}

void Enemy::Update() { 
	Vector3 tmp = amf_.Add(worldTransform_.translation_, velocity_);
	worldTransform_.translation_ = tmp;
	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
