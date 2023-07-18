#pragma once

#include <DirectXMath.h>
#include"Input.h"
#include"WindowsApp.h"
#include"pad.h"
//#include"Player.h"

#define DIRECTINPUT_VERSION     0x0800   // DirectInputのバージョン指定


using namespace DirectX;

class Camera
{
protected:
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
	virtual void Initialize(int window_width, int window_height,Input* input);
	//更新
	void Update(int window_width, int window_height);
	void UpdateViewMatrix();
	void UpdateProjectionMatrix(int window_width, int window_height);

	//カメラ座標と注視点同時移動
	void MoveVector(const XMVECTOR& move);
	//注視点のみ移動
	void MoveTarget(const XMVECTOR& move);

	//update前処理
	void CurrentUpdate(XMFLOAT3 vel);

	//Getter
	//ビュー行列関連
	const XMMATRIX& GetViewMatrix() {return matView;}

	/// 視点座標の取得
	const XMFLOAT3& GetEye() { return eye; }

	/// 注視点座標の取得
	const XMFLOAT3& GetTarget() { return target; }
	const float& GetTargetX() { return target.x; }
	const float& GetTargetY() { return target.y; }
	const float& GetTargetZ() { return target.z; }

	/// 視点座標の取得
	const XMFLOAT3& GetWallEye() { return walleye; }

	/// 注視点座標の取得
	const XMFLOAT3& GetWallTarget() { return walltarget; }
	const float& GetWallTargetX() { return walltarget.x; }
	const float& GetWallTargetY() { return walltarget.y; }
	const float& GetWallTargetZ() { return walltarget.z; }


	const XMFLOAT3& GetUp() {return up;}

	const XMFLOAT3& GetRoatation() { return rotation; }

	const XMMATRIX& GetmatRot() { return matRot; }

	void Setwallflag(bool flag) { this->wallflag = flag; }


	//プロジェクション行列関連

	const XMMATRIX& GetProjectionMatrix() {return matProjection;}

	const XMMATRIX& GetViewProjectionMatrix() {return matViewProjection;}


	//Setter
	//ビュー行列関連

	/// 視点座標の設定
	void SetEye(XMFLOAT3 eye);

	/// 注視点座標の設定
	void SetTarget(XMFLOAT3 target);

	/// 視点座標の設定
	void SetWallEye(XMFLOAT3 noweye) { this->walleye = noweye; }

	/// 注視点座標の設定
	void SetWallTarget(XMFLOAT3 nowtarget) { this->walltarget = nowtarget; }


	void SetUp(XMFLOAT3 up);

	void SetViewMatrix(XMMATRIX viewmatrix);

	void SetRoatation(XMFLOAT3 roatation);

	void SetmouseX(float mouseX);

	void SetmouseY(float mouseY);

	void Setscene(int &scene) { this->nowscene = scene; }

	void Setnowtuto(int &tuto) { this->nowtuto = tuto; }

	const int& Getnowtuto() { return nowtuto; }

	void Settuto(int &tutoNum) { this->tutonum = tutoNum; }


protected://メンバ変数
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
	// カメラの座標(壁に当たる前)
	XMFLOAT3 walleye;
	// 注視点座標(壁に当たる前)
	XMFLOAT3 walltarget;
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

	//1フレーム前のアングル
	float angleculentX = 0.0f;
	float angleculentY = 0.0f;

	//加算されていくアングル
	float anglelimitX = 0.0f;
	float anglelimitY = 0.0f;

	float CurretmouseX = 0;
	float CurretmouseY = 0;

	XMFLOAT3 Velocity{ 0,0,0 };//速度

	//壁に当たっているか
	bool wallflag = false;

	// カメラ注視点までの距離
	float distance = 3;

	//現在何面か
	int nowscene = 0;
	//現在のチュートリアル
	int nowtuto = 0;
	//面ごとのチュートリアルの数
	int tutonum = 0;


	float angleX = 0.0f;
	float angleY = 0.0f;

};

