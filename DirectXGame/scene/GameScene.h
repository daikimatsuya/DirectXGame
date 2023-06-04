#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player.h"
#include "DebugCamera.h"
#include "Enemy.h"
#include "Skydome.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void GetAllColisions();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	ViewProjection viewPlojection_;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	Player* player_ = nullptr;
	Skydome* skydome_ = nullptr;
	Model* model_ = nullptr;
	Model* modelSkydome_ = nullptr;
	Enemy* enemy_ = nullptr;
	uint32_t textuerHandle_=0;
	uint32_t textureHandleEnemy_ = 0;
	uint32_t textureHandleSkydome_ = 0;
	bool isDebugCameraActive_ = false;
	DebugCamera* debugCamera_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
