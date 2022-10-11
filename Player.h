#pragma once
#include"Pbullet.h"
#include"Input.h"
#include <DirectXMath.h>
//#include "fbxsdk.h"
//#include "FbxLoader.h"
//
//#include "FBXobj3d.h"
//#include "Modelfbx.h"

class Player
{
protected: // エイリアス
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

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
	const XMFLOAT3& GetPos() { return pos;}

	///Setter
	//座標
	void SetPos(XMFLOAT3 pos);


private://メンバ変数
	Input* input = nullptr;
	Pbullet* bullet = nullptr;

	// プレイヤーの座標
	XMFLOAT3 pos = {0,0,0};
	


};

