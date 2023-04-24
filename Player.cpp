#include "Player.h"
#include <cassert>


Player::Player() {

}

Player::~Player() {

}

void Player::Initialize(Model* model, uint32_t tectureHandle) {
	assert(model);
	model_ = model; 
	tectureHandle_ = tectureHandle;
	worldTrasform_.Initialize();
	viewProjection_.Initialize();
}

void Player::Update() { 
	worldTrasform_.TransferMatrix();
}

void Player::Draw(ViewProjection viewProjection) { 
	viewProjection_ = viewProjection;
	model_->Draw(worldTrasform_, viewProjection_, tectureHandle_);
}
