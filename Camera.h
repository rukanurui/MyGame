#pragma once

#include <DirectXMath.h>

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

	//������
	void Initialize(int window_width, int window_height);
	//�X�V
	void Update(int window_width, int window_height);
	void UpdateViewMatrix();
	void UpdateProjectionMatrix(int window_width, int window_height);

	void MoveVector(XMFLOAT3 move);

	//Getter
	//�r���[�s��֘A
	const XMMATRIX& GetViewMatrix() {return matView;}

	/// ���_���W�̎擾
	const XMFLOAT3& GetEye() { return eye; }

	/// �����_���W�̎擾
	const XMFLOAT3& GetTarget() { return target; }

	const XMFLOAT3& GetUp() {return up;}


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




private://�����o�ϐ�
	// �r���[�s��
	static XMMATRIX matView;
	// �ˉe�s��
	static XMMATRIX matProjection;
	// �r���[�v���W�F�N�V�����s��
	static XMMATRIX matViewProjection;
	// �J�����̍��W
	static XMFLOAT3 eye;
	// �����_���W(���Ă�ꏊ)
	static XMFLOAT3 target;
	// ������x�N�g��
	static XMFLOAT3 up;
	// �A�X�y�N�g��
	float aspectRatio = 1.0f;

};

