#pragma once
#include <vector>
#define DIRECTINPUT_VERSION     0x0800   // DirectInputのバージョン指定
#include <string>
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include "Input.h"
#include "fbxsdk.h"
#include "FbxLoader.h"

#include "FBXobj3d.h"
#include "Modelfbx.h"


class Pbullet
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

public:
	void Initialize(FbxModel* model);
	void create(FbxModel* model,const XMFLOAT3& Playerpos,const XMFLOAT3& velocity);
	void update();
	void deleate(int flag);
	void draw();
	

private:
	//座標
	XMFLOAT3 pos{ 0,0,0 };
	//速度
	XMFLOAT3 Vel{ 0,0,0 };//速度
	bool colisionflag;
	bool areaflag;

	//3Dモデル
	FBXobj3d* ballet = nullptr;
	FbxModel* modelballet = nullptr;
};

