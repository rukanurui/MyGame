#pragma once

#include <DirectXMath.h>
#include"Input.h"
#include"WindowsApp.h"
#include"pad.h"

#define DIRECTINPUT_VERSION     0x0800   // DirectInput�̃o�[�W�����w��


using namespace DirectX;

class Camera
{
private:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;


public: // �����o�֐�

	//�R���X�g���N�^
	Camera(Input* input,WindowsApp* windows);
	//������
	void Initialize(int window_width, int window_height,Input* input);
	//�X�V
	void Update(int window_width, int window_height);
	void UpdateViewMatrix();
	void UpdateProjectionMatrix(int window_width, int window_height);

	//�J�������W�ƒ����_�����ړ�
	void MoveVector(const XMVECTOR& move);
	//�����_�݈̂ړ�
	void MoveTarget(const XMVECTOR& move);


	void CurrentUpdate();

	//Getter
	//�r���[�s��֘A
	const XMMATRIX& GetViewMatrix() {return matView;}

	/// ���_���W�̎擾
	const XMFLOAT3& GetEye() { return eye; }

	/// �����_���W�̎擾
	const XMFLOAT3& GetTarget() { return target; }

	const XMFLOAT3& GetUp() {return up;}

	const XMFLOAT3& GetRoatation() { return rotation; }


	//�v���W�F�N�V�����s��֘A

	const XMMATRIX& GetProjectionMatrix() {return matProjection;}

	const XMMATRIX& GetViewProjectionMatrix() {return matViewProjection;}


	//Setter
	//�r���[�s��֘A

	/// ���_���W�̐ݒ�
	void SetEye(XMFLOAT3 eye);

	/// �����_���W�̐ݒ�
	void SetTarget(XMFLOAT3 target);

	void SetUp(XMFLOAT3 up);

	void SetViewMatrix(XMMATRIX viewmatrix);

	void SetRoatation(XMFLOAT3 roatation);

	void SetmouseX(float mouseX);

	void SetmouseY(float mouseY);


private://�����o�ϐ�
	Input* input=nullptr;
	WindowsApp* windows = nullptr;
	//pad* Pad = nullptr;
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
	// �J�����̍��W
	static XMFLOAT3 eye;
	// �����_���W(���Ă�ꏊ)
	static XMFLOAT3 target;
	// ������x�N�g��
	static XMFLOAT3 up;
	// �A�X�y�N�g��
	float aspectRatio = 1.0f;
	//�t���O
	bool viewDirtyFlag = false;
	// ��]�s��
	XMMATRIX matRot = DirectX::XMMatrixIdentity();
	// �X�P�[�����O
	float scaleX = 0.5f;
	float scaleY = 0.5f;

	float CurretmouseX = 0;
	float CurretmouseY = 0;

	XMFLOAT3 Velocity{ 0,0,0 };//���x

	// �J���������_�܂ł̋���
	float distance = 10;

};

