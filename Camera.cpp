#include "Camera.h"

using namespace DirectX;
XMMATRIX Camera::matView = {};
XMMATRIX Camera::matProjection = {};
XMMATRIX Camera::matViewProjection = {};
XMMATRIX Camera::matWorld = {};
XMFLOAT3 Camera::eye = { 0, 0, 10.0f };
XMFLOAT3 Camera::target = { 0, 0, 0 };
XMFLOAT3 Camera::up = { 0, 1, 0 };
XMFLOAT3 Camera::rotation = { 0, 0, 0 };



Camera::Camera(Input* input)
{
	assert(input);

	this->input = input;
}

void Camera::Initialize(int window_width, int window_height,Input* input)
{
	
	
	// �r���[�s��̐���
	matView = XMMatrixLookAtLH(
		XMLoadFloat3(&eye),
		XMLoadFloat3(&target),
		XMLoadFloat3(&up));

	
	// �������e�ɂ��ˉe�s��̐���
	matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(60.0f),
		(float)window_width / window_height,
		0.1f, 1000.0f
	);
}

void Camera::Update(int window_width, int window_height)
{
	XMMATRIX matScale, matRot, matTrans;

	// �X�P�[���A��]�A���s�ړ��s��̌v�Z
	matRot = XMMatrixIdentity();
	matRot *= XMMatrixRotationX(XMConvertToRadians(rotation.x));
	matRot *= XMMatrixRotationY(XMConvertToRadians(rotation.y));

	// ���[���h�s��̍���
	matWorld = XMMatrixIdentity(); // �ό`�����Z�b�g
	//matWorld *= matScale; // ���[���h�s��ɃX�P�[�����O�𔽉f
	matWorld *= matRot; // ���[���h�s��ɉ�]�𔽉f
	//matWorld *= matTrans; // ���[���h�s��ɕ��s�ړ��𔽉f


	
	UpdateProjectionMatrix(window_width, window_height);
	matViewProjection = matView * matProjection;
}

void Camera::UpdateViewMatrix()
{

	if (input->PushclickLeft())
	{
		// �����_���王�_�ւ̃x�N�g���ƁA������x�N�g��
		XMVECTOR vTargetEye = { 0.0f, 0.0f, 10.0f, 1.0f };
		XMVECTOR vUp = { 0.0f, 1.0f, 0.0f, 0.0f };
		//// �����_���炸�炵���ʒu�Ɏ��_���W������
		const XMFLOAT3& Target = GetTarget();
		SetEye({ Target.x + vTargetEye.m128_f32[0], Target.y + vTargetEye.m128_f32[1], Target.z + vTargetEye.m128_f32[2] });
		SetUp({ vUp.m128_f32[0], vUp.m128_f32[1], vUp.m128_f32[2] });
	}
	

	// �r���[�s��̍X�V
	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));



}

void Camera::UpdateProjectionMatrix(int window_width, int window_height)
{
	// �������e�ɂ��ˉe�s��̐���
	matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(60.0f),
		(float)window_width / window_height,
		0.1f, 1000.0f
	);
}

void Camera::SetEye(XMFLOAT3 eye)
{
	Camera::eye = eye;

	UpdateViewMatrix();
}

void Camera::SetTarget(XMFLOAT3 target)
{
	Camera::target = target;

	UpdateViewMatrix();
}

void Camera::SetUp(XMFLOAT3 up)
{
	Camera::up = up;

	UpdateViewMatrix();
}

void Camera::SetRoatation(XMFLOAT3 roatation)
{
	Camera::rotation = roatation;
}

void Camera::MoveVector(XMFLOAT3 move)
{
	XMFLOAT3 eye_moved = GetEye();
	XMFLOAT3 target_moved = GetTarget();

	eye_moved.x += move.x;
	eye_moved.y += move.y;
	eye_moved.z += move.z;

	target_moved.x += move.x;
	target_moved.y += move.y;
	target_moved.z += move.z;

	SetEye(eye_moved);
	SetTarget(target_moved);
}

void Camera::MoveTarget(XMFLOAT3 move)
{
	XMFLOAT3 target_moved = GetTarget();

	target_moved.x += move.x;
	target_moved.y += move.y;

	SetTarget(target_moved);
}
