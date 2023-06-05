#include "Player.h"
#include <cassert>
#include "Input.h"
#include "AffineMatrixFunctions.h"
#include "ImGuiManager.h"
#include "PlayerBullet.h"



Player::Player() {

}

Player::~Player() { 
	for (PlayerBullet* bullet : bullets_) {
		delete bullet;
	}
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
	Rotate();

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


	worldTrasform_.UpdateMatrix();
	bullets_.remove_if([](PlayerBullet* bullet) { 
		if (bullet->Isdead()) {
			delete bullet;
			return true;
		}
		return false;
	});
	Attack();
	for (PlayerBullet* bullet : bullets_) {
		bullet->Update();
	}
}

void Player::Draw(ViewProjection viewProjection) { 
	viewProjection_ = viewProjection;
	model_->Draw(worldTrasform_, viewProjection_, tectureHandle_);
	for (PlayerBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}

void Player::Rotate() { 
	const float KRotSpeed = 0.02f; 
	if (input_->PushKey(DIK_A)) {
		worldTrasform_.rotation_.y += KRotSpeed;
	}
	if (input_->PushKey(DIK_D)) {
		worldTrasform_.rotation_.y -= KRotSpeed;
	}
}

void Player::Attack() { 
	if (input_->TriggerKey(DIK_Z)) {
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);
		velocity = AMF_->TransformNormal(velocity, worldTrasform_.matWorld_);
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, worldTrasform_.translation_,velocity);
		bullets_.push_back(newBullet);
	}
}

Vector3 Player::GetWorldPosition() { 
	Vector3 worldPos;
	worldPos.x = worldTrasform_.matWorld_.m[3][0];
	worldPos.y = worldTrasform_.matWorld_.m[3][1];
	worldPos.z = worldTrasform_.matWorld_.m[3][2];
	return worldPos;
}
