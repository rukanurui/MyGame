#pragma once
#include "Camera.h"
#include"Pbullet.h"
#include"Input.h"

class Player
{
public://メンバ関数
	//初期化
	void Initialize(Input*input);
	//更新
	void Update();
	//描画
	void Draw();
	// 座標の取得
	const XMFLOAT3& GetPos() { return pos; }

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

