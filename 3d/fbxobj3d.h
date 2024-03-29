#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include "Modelfbx.h"
#include "../Engine/Camera.h"
#include "FbxLoader.h"
#include "fbxsdk.h"
#include <string>
#include"../Collider/ColisionInfo.h"
#include"../Collider/CollisionColor.h"

class BaseCollider;

class FBXobj3d
{
protected: // エイリアス
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;	

public://サブクラス
	//定数バッファ用データ構造体(座標変換)
	struct ConstBufferDataTransform
	{
		XMMATRIX viewproj;//ビュープロジェクション
		XMMATRIX world;//ワールド行列
		XMFLOAT3 camerapos;//カメラ座標(ワールド座標)
	};

	//ボーンの最大数
	static const int MAX_BONES = 32;

	struct ConstBufferDataSkin
	{
		XMMATRIX bones[MAX_BONES];
	};

public://メンバ関数
	//コンストラクタ
	FBXobj3d() = default;
	//デストラクタ
	virtual ~FBXobj3d();
	//初期化
	virtual void Initialize();
	//グラフィックスパイプラインの生成
	static void CreateGraphicsPipeline();
	//舞フレーム処理
	virtual void Update();
	//モデルのセット
	void SetModel(FbxModel* model) { this->fbxmodel = model; }
	//描画
	virtual void Draw(ID3D12GraphicsCommandList* cmdList);
	//Fbxアニメーション再生
	void PlayAnimation();

	//衝突時コールバック関数
	virtual void OnCollision(const CollisionInfo& info) {};

	//getter
	//ワールド行列のゲッター
	const XMMATRIX& GetMatWorld() { return matWorld; }

	const XMFLOAT3& GetPos() { return position; }
	const float& GetPosX() { return position.x; }
	const float& GetPosY() { return position.y; }
	const float& GetPosZ() { return position.z; }

	const XMFLOAT3& GetScale() { return scale; }

	const XMFLOAT3& GetRotation() { return rotation; }

	const float& GetScaleX() { return scale.x; }
	const float& GetScaleY() { return scale.y; }
	const float& GetScaleZ() { return scale.z; }

	const XMMATRIX& GetmatTrans() { return matTrans; }
	
	//setter
	static void SetDevice(ID3D12Device* device) { FBXobj3d::device = device; }
	static void SetCamera(Camera* camera) { FBXobj3d::camera = camera; }
	//ポジションの変更
	void SetPosition(XMFLOAT3 position) { this->position = position; }
	//スケールの変更
	void SetScale(XMFLOAT3 scale) { this->scale = scale; }
	//角度の変更
	void SetRotation(XMFLOAT3 rotation) { this->rotation = rotation; }
	//平行移動行列のセッター
	void SetmatTrans(XMMATRIX Mattrans) { this->matTrans = Mattrans; }
	//コライダーのセット
	void SetCollider(BaseCollider* collider);
	//ワールド座標更新
	void UpdateWorld();
	//弾道に合わせたスケール変化
	void MoveScaleZ(float Velocity);

protected://メンバ変数
	//定数バッファ
	ComPtr<ID3D12Resource> constBufferTransform;
	//スキンの定数バッファ
	ComPtr<ID3D12Resource> constBuffSkin;
	// ローカルスケール
	XMFLOAT3 scale = { 1,1,1 };
	// X,Y,Z軸回りのローカル回転角
	XMFLOAT3 rotation = { 0,0,0 };
	// ローカル座標
	XMFLOAT3 position = { 0,0,0 };
	// ローカルワールド変換行列
	XMMATRIX matWorld;
	XMMATRIX matScale, matRot, matTrans;
	//モデル
	FbxModel* fbxmodel = nullptr;

	//デバイス
	static ID3D12Device* device;
	//カメラ
	static Camera* camera;
	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView;
	// インデックスバッファビュー
	D3D12_INDEX_BUFFER_VIEW ibView;
	
	//1フレームの時間
	FbxTime frameTime;
	//アニメーション開始時間
	FbxTime startTime;
	//アニメーション終了時間
	FbxTime endTime;
	//現在時間(アニメーション)
	FbxTime currentTime;
	//アニメーション再生中
	bool isPlay = false;

	//ルートシグネチャ
	static ComPtr<ID3D12RootSignature> rootsignature;
	//パイプラインステートオブジェ
	static ComPtr<ID3D12PipelineState> pipelinestate;

	//クラス名(デバッグ用)
	const char* name = nullptr;
	//コライダー
	BaseCollider* collider = nullptr;

};