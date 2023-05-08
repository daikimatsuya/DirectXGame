#include "Player.h"
#include <cassert>
#include "Input.h"
#include "AffineMatrixFunctions.h"


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
	input_ = Input::GetInstance();
}

void Player::Update() { 
	worldTrasform_.TransferMatrix();
	Vector3 move = {0, 0, 0};
	const float kCharacterSpeed = 0.2f;
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}
	if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	} else if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	}
	worldTrasform_.translation_.y += move.y;
	worldTrasform_.translation_.x += move.x;
	worldTrasform_.matWorld_= AMF_->MakeAffinMatrix(
													AMF_->MakeScaleMatrix(worldTrasform_.scale_),
													AMF_->MakeRotateMatrix(
														  AMF_->MakeRotateXMatrix(worldTrasform_.rotation_.x),
														  AMF_->MakeRotateYMatrix(worldTrasform_.rotation_.y),
														  AMF_->MakeRotateZMatrix(worldTrasform_.rotation_.z)),
													AMF_->MakeTranslateMatrix(worldTrasform_.translation_));

}

void Player::Draw(ViewProjection viewProjection) { 
	viewProjection_ = viewProjection;
	model_->Draw(worldTrasform_, viewProjection_, tectureHandle_);
}
