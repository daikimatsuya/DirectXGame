#include "PlayerBullet.h"
#include "assert.h"
#include "WorldTransform.h"
#include "Model.h"

void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	assert(model);
	model_ = model;
	velocity_ = velocity;
	textureHandle_ = TextureManager::Load("picture/black.png");
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
}

void PlayerBullet::Update() { 
	Vector3 tmp = amf_.Add(worldTransform_.translation_, velocity_);
	worldTransform_.translation_ = tmp;
	worldTransform_.UpdateMatrix();
	if (--deathTimer_ <= 0) {
		isdead_ = true;
	}
}

void PlayerBullet::Draw(const ViewProjection& viewProjection) { 
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

Vector3 PlayerBullet::GetWorldPos() { 
	
	Vector3 tmp = amf_.Add(worldTransform_.translation_, velocity_);

	return tmp;
}

void PlayerBullet::OnCollision() { isdead_ = true; }
