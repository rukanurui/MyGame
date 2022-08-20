#pragma once

#include <DirectXMath.h>
#include"Input.h"
#include"WindowsApp.h"
#include"pad.h"

#define DIRECTINPUT_VERSION     0x0800   // DirectInputのバージョン指定


using namespace DirectX;

class Camera
{
private:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;


public: // メンバ関数

	//コンストラクタ
	Camera(Input* input,WindowsApp* windows);
	//初期化
	void Initialize(int window_width, int window_height,Input* input);
	//更新
	void Update(int window_width, int window_height);
	void UpdateViewMatrix();
	void UpdateProjectionMatrix(int window_width, int window_height);

	//カメラ座標と注視点同時移動
	void MoveVector(const XMVECTOR& move);
	//注視点のみ移動
	void MoveTarget(const XMVECTOR& move);


	void CurrentUpdate();

	//Getter
	//ビュー行列関連
	const XMMATRIX& GetViewMatrix() {return matView;}

	/// 視点座標の取得
	const XMFLOAT3& GetEye() { return eye; }

	/// 注視点座標の取得
	const XMFLOAT3& GetTarget() { return target; }

	const XMFLOAT3& GetUp() {return up;}

	const XMFLOAT3& GetRoatation() { return rotation; }


	//プロジェクション行列関連

	const XMMATRIX& GetProjectionMatrix() {return matProjection;}

	const XMMATRIX& GetViewProjectionMatrix() {return matViewProjection;}


	//Setter
	//ビュー行列関連

	/// 視点座標の設定
	void SetEye(XMFLOAT3 eye);

	/// 注視点座標の設定
	void SetTarget(XMFLOAT3 target);

	void SetUp(XMFLOAT3 up);

	void SetViewMatrix(XMMATRIX viewmatrix);

	void SetRoatation(XMFLOAT3 roatation);

	void SetmouseX(float mouseX);

	void SetmouseY(float mouseY);


private://メンバ変数
	Input* input=nullptr;
	WindowsApp* windows = nullptr;
	//pad* Pad = nullptr;
	// ビュー行列
	static XMMATRIX matView;
	// 射影行列
	static XMMATRIX matProjection;
	// ビュープロジェクション行列
	static XMMATRIX matViewProjection;
	//ワールド行列
	static XMMATRIX matWorld;
	// X,Y,Z軸回りのローカル回転角
	static XMFLOAT3 rotation;
	// カメラの座標
	static XMFLOAT3 eye;
	// 注視点座標(見てる場所)
	static XMFLOAT3 target;
	// 上方向ベクトル
	static XMFLOAT3 up;
	// アスペクト比
	float aspectRatio = 1.0f;
	//フラグ
	bool viewDirtyFlag = false;
	// 回転行列
	XMMATRIX matRot = DirectX::XMMatrixIdentity();
	// スケーリング
	float scaleX = 0.5f;
	float scaleY = 0.5f;

	float CurretmouseX = 0;
	float CurretmouseY = 0;

	XMFLOAT3 Velocity{ 0,0,0 };//速度

	// カメラ注視点までの距離
	float distance = 10;

};

