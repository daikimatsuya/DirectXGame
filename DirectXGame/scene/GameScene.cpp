#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"


GameScene::GameScene() {}

GameScene::~GameScene() { 
	delete player_;
	delete model_;
	delete debugCamera_;
	delete enemy_;
	delete skydome_;
	delete modelSkydome_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	player_ = new Player();
	enemy_ = new Enemy();
	skydome_ = new Skydome();
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);
	enemy_->SetPlayer(player_);
	model_ = Model::Create();
	viewPlojection_.Initialize();
	textuerHandle_ = TextureManager::Load("picture/mario.png");
	textureHandleEnemy_ = TextureManager::Load("picture/enemy.png");
	textureHandleSkydome_ = TextureManager::Load("skydome/OIP.jpg");
	player_->Initialize(model_,textuerHandle_);
	enemy_->Initialize(model_, textureHandleEnemy_);
	skydome_->Initialize(modelSkydome_, textureHandleSkydome_);
	debugCamera_ = new DebugCamera(1280, 720);
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewPlojection_);
}

void GameScene::Update() { 
	player_->Update(); 
	enemy_->Update();
	skydome_->Update();
	GetAllColisions();
#ifdef _DEBUG
	if (input_->TriggerKey(DIK_SPACE)) {
		if (isDebugCameraActive_ == false) {
			isDebugCameraActive_ = true;
		} else {
			isDebugCameraActive_ = false;
		}
	}
#endif // _DEBUG
	if (isDebugCameraActive_) {
		debugCamera_->Update();
		viewPlojection_.matView = debugCamera_->GetViewProjection().matView;
		viewPlojection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		viewPlojection_.TransferMatrix();

	} else {
		viewPlojection_.UpdateMatrix();
		}
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	skydome_->Draw(viewPlojection_);
	player_->Draw(viewPlojection_);
	if (enemy_) {
		enemy_->Draw(viewPlojection_);
	}
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::GetAllColisions() { 
	Vector3 posA, posB; 
	
	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();
	const std::list<EnemyBullet*>& enemyBullets = enemy_->GetBullets();

	posA = player_->GetWorldPosition();
	for (EnemyBullet* bullet : enemyBullets) {
		posB = bullet->GetWorldPosition();
		float length =
		    ((posB.x - posA.x) * (posB.x - posA.x) + (posB.y - posA.y) * (posB.y - posA.y) +
		     (posB.z - posA.z) * (posB.z - posA.z));
		if (length < (1 + 2) * (1 + 2)) {
			//player_->OnCollision();
			bullet->OnCollision();
		}
	}

	posA = enemy_->GetWorldPosition();
	for (PlayerBullet* bullet : playerBullets) {
		posB = bullet->GetWorldPos();
		float length =
		    ((posB.x - posA.x) * (posB.x - posA.x) + (posB.y - posA.y) * (posB.y - posA.y) +
		     (posB.z - posA.z) * (posB.z - posA.z));
		if (length < (1 + 2) * (1 + 2)) {
			//enemy_->OnCollision();
			bullet->OnCollision();
		}
	}
}
