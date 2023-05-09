#include "Player.h"
#include <cassert>
#include "Input.h"
#include "AffineMatrixFunctions.h"
#include "ImGuiManager.h"


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

	inputFloat[0] = worldTrasform_.translation_.x;
	inputFloat[1] = worldTrasform_.translation_.y;  
	inputFloat[2] = worldTrasform_.translation_.z;

	const float MoveLimitX = 30;
	const float MoveLimitY = 15;


	ImGui::Begin("Player");
	ImGui::SliderFloat3("Player", inputFloat, -100, 100);
	ImGui::End();

	worldTrasform_.translation_.x = inputFloat[0];
	worldTrasform_.translation_.y = inputFloat[1];
	worldTrasform_.translation_.z = inputFloat[2];

	worldTrasform_.translation_.x = max(worldTrasform_.translation_.x, -MoveLimitX);
	worldTrasform_.translation_.x = min(worldTrasform_.translation_.x, +MoveLimitX);
	worldTrasform_.translation_.y = max(worldTrasform_.translation_.y, -MoveLimitY);
	worldTrasform_.translation_.y = min(worldTrasform_.translation_.y, +MoveLimitY);

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
