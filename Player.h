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
protected: // �G�C���A�X
// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public://�����o�֐�
	//������
	void Initialize(Input*Input);
	//�X�V
	void Update();
	//�`��
	void Draw();
	//�U������
	void Shot();

	///Getter
	// ���W�̎擾
	const XMFLOAT3& GetPos() { return pos;}

	///Setter
	//���W
	void SetPos(XMFLOAT3 pos);


private://�����o�ϐ�
	Input* input = nullptr;
	Pbullet* bullet = nullptr;

	// �v���C���[�̍��W
	XMFLOAT3 pos = {0,0,0};
	


};

