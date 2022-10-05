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
	const XMFLOAT3& GetPos() { return pos; }
	//��]�̎擾
	const XMFLOAT3& GetRoatation() { return rotation; }

	///Setter
	//���W
	void SetPos(XMFLOAT3 pos);
	//��]
	void SetRoatation(XMFLOAT3 roatation);


private://�����o�ϐ�
	Input* input = nullptr;
	Pbullet* bullet = nullptr;

	// �r���[�s��
	static XMMATRIX matView;
	// �ˉe�s��
	static XMMATRIX matProjection;
	// �r���[�v���W�F�N�V�����s��
	static XMMATRIX matViewProjection;
	//���[���h�s��
	static XMMATRIX matWorld;
	// X,Y,Z�����̃��[�J����]�p
	static XMFLOAT3 rotation;
	// �v���C���[�̍��W
	static XMFLOAT3 pos;
	// �����_���W(���Ă�ꏊ)
	static XMFLOAT3 target;
	// ������x�N�g��
	static XMFLOAT3 up;



};

