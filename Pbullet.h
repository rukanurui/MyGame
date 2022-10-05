#pragma once
#include <vector>
#define DIRECTINPUT_VERSION     0x0800   // DirectInput�̃o�[�W�����w��
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
protected: // �G�C���A�X
// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
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
	//���W
	XMFLOAT3 pos{ 0,0,0 };
	//���x
	XMFLOAT3 Vel{ 0,0,0 };//���x
	bool colisionflag;
	bool areaflag;

	//3D���f��
	FBXobj3d* ballet = nullptr;
	FbxModel* modelballet = nullptr;
};

