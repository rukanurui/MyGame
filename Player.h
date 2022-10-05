#pragma once
#include "Camera.h"
#include"Pbullet.h"
#include"Input.h"
#include <DirectXMath.h>
#include "fbxsdk.h"
#include "FbxLoader.h"

#include "FBXobj3d.h"
#include "Modelfbx.h"

class Player
{

public://メンバ関数
	//初期化
	void Initialize(Input*Input);
	//更新
	void Update();
	//描画
	void Draw();
	//攻撃処理
	void Shot();

	///Getter
	// 座標の取得
	const XMFLOAT3& GetPos() { return pos; }
	//回転の取得
	const XMFLOAT3& GetRoatation() { return rotation; }

	///Setter
	//座標
	void SetPos(XMFLOAT3 pos);
	//回転
	void SetRoatation(XMFLOAT3 roatation);


private://メンバ変数
	Input* input = nullptr;
	Pbullet* bullet = nullptr;

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
	// プレイヤーの座標
	static XMFLOAT3 pos;
	// 注視点座標(見てる場所)
	static XMFLOAT3 target;
	// 上方向ベクトル
	static XMFLOAT3 up;



};

