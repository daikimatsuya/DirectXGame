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
}

void Player::Update() {

}

void Player::Draw() {

}
