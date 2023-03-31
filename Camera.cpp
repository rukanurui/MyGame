#include "Camera.h"


using namespace DirectX;
XMMATRIX Camera::matView = {};
XMMATRIX Camera::matProjection = {};
XMMATRIX Camera::matViewProjection = {};
XMMATRIX Camera::matWorld = {};
XMFLOAT3 Camera::eye = { 0, 4, 0.0f };
XMFLOAT3 Camera::target = { 0, 4, 0 };
XMFLOAT3 Camera::up = { 0, 1, 0 };
XMFLOAT3 Camera::rotation = { 45, 0, 0 };



Camera::Camera(Input* input,WindowsApp*windows)
{
	assert(input);
	assert(windows);
	this->input = input;
	this->windows = windows;
	// ��ʃT�C�Y�ɑ΂��鑊�ΓI�ȃX�P�[���ɒ���
	scaleX = 1.0f / (float)windows->window_width;
	scaleY = 1.0f / (float)windows->window_height;
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
	// �Čv�Z�K�v�Ȃ�
	if (viewDirtyFlag) {
		// �r���[�s��X�V
		UpdateViewMatrix();
		viewDirtyFlag = false;
	}
	
	UpdateProjectionMatrix(window_width, window_height);
	matViewProjection = matView * matProjection;
}

void Camera::UpdateViewMatrix()
{

	// ���_���W
	XMVECTOR eyePosition = XMLoadFloat3(&eye);
	// �����_���W
	XMVECTOR targetPosition = XMLoadFloat3(&target);
	// �i���́j�����
	XMVECTOR upVector = XMLoadFloat3(&up);

	// �J����Z���i���������j
	XMVECTOR cameraAxisZ = XMVectorSubtract(targetPosition, eyePosition);
	// 0�x�N�g�����ƌ�������܂�Ȃ��̂ŏ��O
	//assert(!XMVector3Equal(cameraAxisZ, XMVectorZero()));
	assert(!XMVector3IsInfinite(cameraAxisZ));
	assert(!XMVector3Equal(upVector, XMVectorZero()));
	assert(!XMVector3IsInfinite(upVector));
	// �x�N�g���𐳋K��
	cameraAxisZ = XMVector3Normalize(cameraAxisZ);

	// �J������X���i�E�����j
	XMVECTOR cameraAxisX;
	// X���͏������Z���̊O�ςŋ��܂�
	cameraAxisX = XMVector3Cross(upVector, cameraAxisZ);
	// �x�N�g���𐳋K��
	cameraAxisX = XMVector3Normalize(cameraAxisX);

	// �J������Y���i������j
	XMVECTOR cameraAxisY;
	// Y����Z����X���̊O�ςŋ��܂�
	cameraAxisY = XMVector3Cross(cameraAxisZ, cameraAxisX);

	// �����܂łŒ�������3�����̃x�N�g��������
	//�i���[���h���W�n�ł̃J�����̉E�����A������A�O�����j	

	// �J������]�s��
	XMMATRIX matCameraRot;
	// �J�������W�n�����[���h���W�n�̕ϊ��s��
	matCameraRot.r[0] = cameraAxisX;
	matCameraRot.r[1] = cameraAxisY;
	matCameraRot.r[2] = cameraAxisZ;
	matCameraRot.r[3] = XMVectorSet(0, 0, 0, 1);
	// �]�u�ɂ��t�s��i�t��]�j���v�Z
	matView = XMMatrixTranspose(matCameraRot);

	// ���_���W��-1���|�������W
	XMVECTOR reverseEyePosition = XMVectorNegate(eyePosition);
	// �J�����̈ʒu���烏�[���h���_�ւ̃x�N�g���i�J�������W�n�j
	XMVECTOR tX = XMVector3Dot(cameraAxisX, reverseEyePosition);	// X����
	XMVECTOR tY = XMVector3Dot(cameraAxisY, reverseEyePosition);	// Y����
	XMVECTOR tZ = XMVector3Dot(cameraAxisZ, reverseEyePosition);	// Z����
	// ��̃x�N�g���ɂ܂Ƃ߂�
	XMVECTOR translation = XMVectorSet(tX.m128_f32[0], tY.m128_f32[1], tZ.m128_f32[2], 1.0f);
	// �r���[�s��ɕ��s�ړ�������ݒ�
	matView.r[3] = translation;

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

void Camera::SetmouseX(float mouseX)
{
	Camera::CurretmouseX = mouseX;
}

void Camera::SetmouseY(float mouseY)
{
	Camera::CurretmouseY = mouseY;
}

void Camera::MoveVector(const XMVECTOR& move)
{
	XMFLOAT3 eye_moved = GetEye();
	XMFLOAT3 target_moved = GetTarget();

	eye_moved.x += move.m128_f32[0];
	eye_moved.y += move.m128_f32[1];
	eye_moved.z += move.m128_f32[2];

	target_moved.x += move.m128_f32[0];
	target_moved.y += move.m128_f32[1];
	target_moved.z += move.m128_f32[2];

	SetEye(eye_moved);
	SetTarget(target_moved);
}

void Camera::MoveTarget(const XMVECTOR& move)
{
	XMFLOAT3 target_moved = GetTarget();

	target_moved.x += move.m128_f32[0];
	target_moved.y += move.m128_f32[1];
	target_moved.z += move.m128_f32[2];

	SetTarget(target_moved);
}

void Camera::CurrentUpdate()
{
	viewDirtyFlag = false;
	float angleX = 0;
	float angleY = 0;

	float oldeye = eye.y;

	XMFLOAT3 oldpos{ eye };

	// �}�E�X�̓��͂��擾
	Input::MouseMove mouseMove = input->GetMouseMove();

	if (mouseMove.lX==CurretmouseX || mouseMove.lY == CurretmouseY)
	{
		float dy = (mouseMove.lX * scaleX)*0.168;
		float dx = (mouseMove.lY * scaleY)*0.168;

		angleX = -dx * XM_PI;
		angleY = -dy * XM_PI;
		angleculentX += angleX;
		angleculentY += angleY;


		viewDirtyFlag = true;
	}


	//pad�̓���
	/*Pad->Update();

	if (Pad->state.Gamepad.sThumbLX!=0)
	{
		float dy = Pad->state.Gamepad.sThumbLX * scaleX;
		float dx = Pad->state.Gamepad.sThumbLY * scaleY;

		angleX = -dy * XM_PI;
		angleY = -dx * XM_PI;
		viewDirtyFlag = true;
	}

	if (Pad->state.Gamepad.sThumbLY != 0)
	{
		float dy = Pad->state.Gamepad.sThumbLX * scaleX;
		float dx = Pad->state.Gamepad.sThumbLY * scaleY;

		angleX = -dy * XM_PI;
		angleY = -dx * XM_PI;
		viewDirtyFlag = true;
	}*/


	//���W�̑���
	
	if (input->PushKey(DIK_A) || input->PushKey(DIK_D))
	{
		
		if (input->PushKey(DIK_A)) Velocity.x = -0.1f;
		else
		{
			if (input->PushKey(DIK_D)) Velocity.x = 0.1f;
		}

		if (!input->PushKey(DIK_A) && !input->PushKey(DIK_D)) Velocity.x = 0;

		/*if (eye.x <= -6.0f)
		{
			eye.x = 1.0f;
			Velocity.x = 0.1;
			Velocity.z = 0;
		}

		if (eye.z >= 6.0f && eye.x <= 10.0f)
		{
			eye.z = 5.0f;
			Velocity.x = 0.2f;
			Velocity.z = -0.2;
		}

		if (eye.x >= 26.0f && eye.z <= 46.0f)
		{
			eye.x = 21.0f;
			Velocity.x = -0.1;
			Velocity.z = 0;
		}

		if (eye.z >= 70.0f)
		{
			eye.x = 65.0f;
			Velocity.x = 0;
			Velocity.z = -0.1;
		}

		if (eye.z<=-6.0f)
		{
			eye.z = -1.0f;
			Velocity.z = 0.1;
			Velocity.x = 0;
		}*/


		XMVECTOR move = { Velocity.x,Velocity.y,0,0 };

		move = XMVector3Transform(move, matRot);
		MoveVector(move);
		viewDirtyFlag = true;

		
	}

	if (input->PushKey(DIK_W) || input->PushKey(DIK_S))
	{
		if (input->PushKey(DIK_S)) Velocity.z = -0.1f;
		else
		{
			if (input->PushKey(DIK_W)) Velocity.z = 0.1f;
		}
		if (!input->PushKey(DIK_W) && !input->PushKey(DIK_S)) Velocity.z = 0;


		/*if (eye.x <= -6.0f)
		{
			eye.x = 1.0f;
			Velocity.x = 0.1;
			Velocity.z = 0;
		}

		if (eye.x >= 26.0f && eye.z <= 46.0f)
		{
			eye.x = 21.0f;
			Velocity.x = -0.1;
			Velocity.z = 0;
		}

		if (eye.z >= 70.0f)
		{
			eye.x = 65.0f;
			Velocity.x = 0;
			Velocity.z = -0.1;
		}

		if (eye.z <= -6.0f)
		{
			eye.z = -1.0f;
			Velocity.z = 0.1;
			Velocity.x = 0;
		}*/

		
		XMVECTOR move = { 0,0,Velocity.z,0 };

		move = XMVector3Transform(move, matRot);
		MoveTarget(move);
		viewDirtyFlag = true;


		
	}

	if (target.y <= 5)target.y = 5;//�����_��0�ȉ��ɂȂ肻����������

	if (target.y >= 5)target.y = 5;//�����_��5�ȏ�ɂȂ肻����������

	
	if (viewDirtyFlag)
	{
		// �ǉ���]���̉�]�s��𐶐�
		XMMATRIX matRotNew = XMMatrixIdentity();

		//������angle����
		// 
		//��Ɉ��ȏ��������
		if (angleculentX >= 1.0f&&target.y>=5)
		{
			angleculentX -= 0.05f;
			angleX -= 0.05f;

		}

		//���Ɉ��ȏ��������
		if (angleculentX <= -1.0f)
		{
			angleculentX += 0.05f;
			angleX += 0.05f;
		}


		matRotNew *= XMMatrixRotationX(-angleX);
		matRotNew *= XMMatrixRotationY(-angleY);


		// �ݐς̉�]�s�������
		// ����]�s���ݐς��Ă����ƁA�덷�ŃX�P�[�����O��������댯�������
		// �N�H�[�^�j�I�����g�p��������]�܂���
		matRot = matRotNew * matRot;

		// �����_���王�_�ւ̃x�N�g���ƁA������x�N�g��

		if (target.y >= 10 && eye.y <= 9) distance = 5;
		else
		{
			distance = 5;
		}


		XMVECTOR vTargetEye = { 0.0f, 0.0f, -distance, 1.0f };
		XMVECTOR vUp = { 0.0f, 1.0f, 0.0f, 0.0f };
		// �x�N�g������]
		vTargetEye = XMVector3Transform(vTargetEye, matRot);
		vUp = XMVector3Transform(vUp, matRot);
		// �����_���炸�炵���ʒu�Ɏ��_���W������
		const XMFLOAT3& Target = GetTarget();
		
		SetEye({ Target.x + vTargetEye.m128_f32[0], Target.y + vTargetEye.m128_f32[1], Target.z + vTargetEye.m128_f32[2] });
		//SetUp({ vUp.m128_f32[0], vUp.m128_f32[1], vUp.m128_f32[2] });

	}


	Camera::Update(windows->window_width, windows->window_height);

}
