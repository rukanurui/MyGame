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
	// 画面サイズに対する相対的なスケールに調整
	scaleX = 1.0f / (float)windows->window_width;
	scaleY = 1.0f / (float)windows->window_height;
}

void Camera::Initialize(int window_width, int window_height,Input* input)
{

	// ビュー行列の生成
	matView = XMMatrixLookAtLH(
		XMLoadFloat3(&eye),
		XMLoadFloat3(&target),
		XMLoadFloat3(&up));

	
	// 透視投影による射影行列の生成
	matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(60.0f),
		(float)window_width / window_height,
		0.1f, 1000.0f
	);
}

void Camera::Update(int window_width, int window_height)
{
	// 再計算必要なら
	if (viewDirtyFlag) {
		// ビュー行列更新
		UpdateViewMatrix();
		viewDirtyFlag = false;
	}
	
	UpdateProjectionMatrix(window_width, window_height);
	matViewProjection = matView * matProjection;
}

void Camera::UpdateViewMatrix()
{

	// 視点座標
	XMVECTOR eyePosition = XMLoadFloat3(&eye);
	// 注視点座標
	XMVECTOR targetPosition = XMLoadFloat3(&target);
	// （仮の）上方向
	XMVECTOR upVector = XMLoadFloat3(&up);

	// カメラZ軸（視線方向）
	XMVECTOR cameraAxisZ = XMVectorSubtract(targetPosition, eyePosition);
	// 0ベクトルだと向きが定まらないので除外
	//assert(!XMVector3Equal(cameraAxisZ, XMVectorZero()));
	assert(!XMVector3IsInfinite(cameraAxisZ));
	assert(!XMVector3Equal(upVector, XMVectorZero()));
	assert(!XMVector3IsInfinite(upVector));
	// ベクトルを正規化
	cameraAxisZ = XMVector3Normalize(cameraAxisZ);

	// カメラのX軸（右方向）
	XMVECTOR cameraAxisX;
	// X軸は上方向→Z軸の外積で求まる
	cameraAxisX = XMVector3Cross(upVector, cameraAxisZ);
	// ベクトルを正規化
	cameraAxisX = XMVector3Normalize(cameraAxisX);

	// カメラのY軸（上方向）
	XMVECTOR cameraAxisY;
	// Y軸はZ軸→X軸の外積で求まる
	cameraAxisY = XMVector3Cross(cameraAxisZ, cameraAxisX);

	// ここまでで直交した3方向のベクトルが揃う
	//（ワールド座標系でのカメラの右方向、上方向、前方向）	

	// カメラ回転行列
	XMMATRIX matCameraRot;
	// カメラ座標系→ワールド座標系の変換行列
	matCameraRot.r[0] = cameraAxisX;
	matCameraRot.r[1] = cameraAxisY;
	matCameraRot.r[2] = cameraAxisZ;
	matCameraRot.r[3] = XMVectorSet(0, 0, 0, 1);
	// 転置により逆行列（逆回転）を計算
	matView = XMMatrixTranspose(matCameraRot);

	// 視点座標に-1を掛けた座標
	XMVECTOR reverseEyePosition = XMVectorNegate(eyePosition);
	// カメラの位置からワールド原点へのベクトル（カメラ座標系）
	XMVECTOR tX = XMVector3Dot(cameraAxisX, reverseEyePosition);	// X成分
	XMVECTOR tY = XMVector3Dot(cameraAxisY, reverseEyePosition);	// Y成分
	XMVECTOR tZ = XMVector3Dot(cameraAxisZ, reverseEyePosition);	// Z成分
	// 一つのベクトルにまとめる
	XMVECTOR translation = XMVectorSet(tX.m128_f32[0], tY.m128_f32[1], tZ.m128_f32[2], 1.0f);
	// ビュー行列に平行移動成分を設定
	matView.r[3] = translation;

}

void Camera::UpdateProjectionMatrix(int window_width, int window_height)
{
	// 透視投影による射影行列の生成
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

	// マウスの入力を取得
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


	//padの入力
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


	//座標の操作
	
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

	if (target.y <= 5)target.y = 5;//注視点が0以下になりそうだったら

	if (target.y >= 5)target.y = 5;//注視点が5以上になりそうだったら

	
	if (viewDirtyFlag)
	{
		// 追加回転分の回転行列を生成
		XMMATRIX matRotNew = XMMatrixIdentity();

		//ここにangle処理
		// 
		//上に一定以上向いたら
		if (angleculentX >= 1.0f&&target.y>=5)
		{
			angleculentX -= 0.05f;
			angleX -= 0.05f;

		}

		//下に一定以上向いたら
		if (angleculentX <= -1.0f)
		{
			angleculentX += 0.05f;
			angleX += 0.05f;
		}


		matRotNew *= XMMatrixRotationX(-angleX);
		matRotNew *= XMMatrixRotationY(-angleY);


		// 累積の回転行列を合成
		// ※回転行列を累積していくと、誤差でスケーリングがかかる危険がある為
		// クォータニオンを使用する方が望ましい
		matRot = matRotNew * matRot;

		// 注視点から視点へのベクトルと、上方向ベクトル

		if (target.y >= 10 && eye.y <= 9) distance = 5;
		else
		{
			distance = 5;
		}


		XMVECTOR vTargetEye = { 0.0f, 0.0f, -distance, 1.0f };
		XMVECTOR vUp = { 0.0f, 1.0f, 0.0f, 0.0f };
		// ベクトルを回転
		vTargetEye = XMVector3Transform(vTargetEye, matRot);
		vUp = XMVector3Transform(vUp, matRot);
		// 注視点からずらした位置に視点座標を決定
		const XMFLOAT3& Target = GetTarget();
		
		SetEye({ Target.x + vTargetEye.m128_f32[0], Target.y + vTargetEye.m128_f32[1], Target.z + vTargetEye.m128_f32[2] });
		//SetUp({ vUp.m128_f32[0], vUp.m128_f32[1], vUp.m128_f32[2] });

	}


	Camera::Update(windows->window_width, windows->window_height);

}
