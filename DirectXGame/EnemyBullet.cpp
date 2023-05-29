#include "EnemyBullet.h"
#include "assert.h"

EnemyBullet::EnemyBullet() {}

EnemyBullet::~EnemyBullet() {}

void EnemyBullet::Initialize(Model* model, const Vector3 position, const Vector3 velocity) {
	assert(model);
	velocity_ = velocity;
	model_ = model;
	worldTransform_.Initialize();
	textureHandle_ = TextureManager::Load("picture/enemybullet.png");
	worldTransform_.translation_ = position;
}

void EnemyBullet::Update() {
	Vector3 tmp = amf_.Add(worldTransform_.translation_, velocity_);
	worldTransform_.translation_ = tmp;
	worldTransform_.UpdateMatrix();
	if (--deathTimer_ <= 0) {
		isdead_ = true;
	}
}

void EnemyBullet::Draw(const ViewProjection viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

Vector3 EnemyBullet::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;
	return worldPos;
}

void EnemyBullet::OnCollision() { isdead_ = true; }


