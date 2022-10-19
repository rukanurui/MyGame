#include "Enemy.h"
#include <time.h>



Enemy::Enemy() : FBXobj3d()
{
}

//Enemy* Enemy::Create()
//{
//	//3D�I�u�W�F�N�g�̃C���X�^���X�𐶐�
//	Enemy* instance = new Enemy();
//	if (instance == nullptr) {
//		return nullptr;
//	}
//
//	// ������
//	if (!instance->Initialize()) {
//		delete instance;
//		assert(0);
//	}
//	return instance;
//}

bool Enemy::EnemyInitialize()
{
	//�R���C�_�[�̒ǉ�
	float radius = 1.5f;
	//���a�������������畂�������W�����̒��S�ɂ���
	SetCollider(new SphereCollider(XMVECTOR({ 0,radius,0,0 }), radius));
	return true;
}

void Enemy::EnemyUpdate()
{

	if (col == 1)
	{

		G -= 0.01f;

		if (G <= -0.1f)
		{
			G = -0.1f;
		}

		DivVel.m128_f32[1] += G;

		position.x += DivVel.m128_f32[0];
		position.y += DivVel.m128_f32[1];
		position.z += DivVel.m128_f32[2];

		/*if (position.x >= 10 || position.x <= 0)
		{
			DivVel.m128_f32[0] = 0.0f;
		}

		if (position.z >= 40 || position.z <= 15)
		{
			DivVel.m128_f32[2] = 0.0f;
		}*/

		if (position.y<=0)
		{
			position.y = 0;
		}
		

		HRESULT result;
		XMMATRIX matScale, matRot, matTrans;

		// �X�P�[���A��]�A���s�ړ��s��̌v�Z
		matScale = XMMatrixScaling(scale.x, scale.y, scale.z);
		matRot = XMMatrixIdentity();
		matRot *= XMMatrixRotationZ(XMConvertToRadians(rotation.z));
		matRot *= XMMatrixRotationX(XMConvertToRadians(rotation.x));
		matRot *= XMMatrixRotationY(XMConvertToRadians(rotation.y));
		matTrans = XMMatrixTranslation(position.x, position.y, position.z);

		// ���[���h�s��̍���
		matWorld = XMMatrixIdentity(); // �ό`�����Z�b�g
		matWorld *= matScale; // ���[���h�s��ɃX�P�[�����O�𔽉f
		matWorld *= matRot; // ���[���h�s��ɉ�]�𔽉f
		matWorld *= matTrans; // ���[���h�s��ɕ��s�ړ��𔽉f

		//��������J����
		//�r���[�v���W�F�N�V�����s��
		const XMMATRIX& matViewProjection =
			camera->GetViewProjectionMatrix();
		//���f���̃��b�V���g�����X�t�H�[��
		const XMMATRIX& modelTransform = fbxmodel->GetModelTransform();
		//�J�������W
		const XMFLOAT3& camerapos = camera->GetEye();

		//�A�j���[�V����
		if (isPlay) {
			//1�t���[���i�߂�
			currentTime += frameTime;
			//�Ō�܂ōĐ�������擪�ɖ߂�
			if (currentTime > endTime) {
				currentTime = startTime;
			}
		}

		//�{�[���z��
		std::vector<FbxModel::Bone>& bones = fbxmodel->GetBones();

		// �X�L���̒萔�o�b�t�@�փf�[�^�]��
		ConstBufferDataSkin* constMapSkin = nullptr;
		result = constBuffSkin->Map(0, nullptr, (void**)&constMapSkin);
		for (int i = 0; i < bones.size(); i++)
		{
			//���̎p���s��
			XMMATRIX matCurrentPose;
			//���̎p���s����擾
			FbxAMatrix fbxCurrentPose =
				bones[i].fbxCluster->GetLink()->EvaluateGlobalTransform(currentTime);
			//XMMATRIX�ɕϊ�
			FbxLoader::ConvertMatrixFromFbx(&matCurrentPose, fbxCurrentPose);
			//�������ăX�L�j���O�s���
			constMapSkin->bones[i] = bones[i].invInitialPose * matCurrentPose;
		}
		constBuffSkin->Unmap(0, nullptr);

		//�萔�o�b�t�@�փf�[�^�]��
		ConstBufferDataTransform* constMap = nullptr;
		result = constBufferTransform->Map(0, nullptr, (void**)&constMap);
		if (SUCCEEDED(result))
		{
			constMap->viewproj = matViewProjection;
			constMap->world = modelTransform * matWorld;
			constMap->camerapos = camerapos;
			constBufferTransform->Unmap(0, nullptr);
		}
	}


	

	////�����蔻��X�V
	//if (collider)
	//{
	//	collider->Update();
	//}
}

void Enemy::Enemycol(XMFLOAT3 pos,XMVECTOR vel)
{

	if (col==0)
	{
		
		position = pos;

		DivVel = vel;

		G = 0.01f;

		col = 1;
	}
	
}


void Enemy::OnCollision(const CollisionInfo& info)
{


	if (scale.x >= 1)
	{
		scale.x = 0.5; scale.y = 0.5; scale.z = 0.5;
	}


	HRESULT result;
	XMMATRIX matScale, matRot, matTrans;

	// �X�P�[���A��]�A���s�ړ��s��̌v�Z
	matScale = XMMatrixScaling(scale.x, scale.y, scale.z);
	matRot = XMMatrixIdentity();
	matRot *= XMMatrixRotationZ(XMConvertToRadians(rotation.z));
	matRot *= XMMatrixRotationX(XMConvertToRadians(rotation.x));
	matRot *= XMMatrixRotationY(XMConvertToRadians(rotation.y));
	matTrans = XMMatrixTranslation(position.x, position.y, position.z);

	// ���[���h�s��̍���
	matWorld = XMMatrixIdentity(); // �ό`�����Z�b�g
	matWorld *= matScale; // ���[���h�s��ɃX�P�[�����O�𔽉f
	matWorld *= matRot; // ���[���h�s��ɉ�]�𔽉f
	matWorld *= matTrans; // ���[���h�s��ɕ��s�ړ��𔽉f

	//��������J����
	//�r���[�v���W�F�N�V�����s��
	const XMMATRIX& matViewProjection =
		camera->GetViewProjectionMatrix();
	//���f���̃��b�V���g�����X�t�H�[��
	const XMMATRIX& modelTransform = fbxmodel->GetModelTransform();
	//�J�������W
	const XMFLOAT3& camerapos = camera->GetEye();

	//�A�j���[�V����
	if (isPlay) {
		//1�t���[���i�߂�
		currentTime += frameTime;
		//�Ō�܂ōĐ�������擪�ɖ߂�
		if (currentTime > endTime) {
			currentTime = startTime;
		}
	}

	//�{�[���z��
	std::vector<FbxModel::Bone>& bones = fbxmodel->GetBones();

	// �X�L���̒萔�o�b�t�@�փf�[�^�]��
	ConstBufferDataSkin* constMapSkin = nullptr;
	result = constBuffSkin->Map(0, nullptr, (void**)&constMapSkin);
	for (int i = 0; i < bones.size(); i++)
	{
		//���̎p���s��
		XMMATRIX matCurrentPose;
		//���̎p���s����擾
		FbxAMatrix fbxCurrentPose =
			bones[i].fbxCluster->GetLink()->EvaluateGlobalTransform(currentTime);
		//XMMATRIX�ɕϊ�
		FbxLoader::ConvertMatrixFromFbx(&matCurrentPose, fbxCurrentPose);
		//�������ăX�L�j���O�s���
		constMapSkin->bones[i] = bones[i].invInitialPose * matCurrentPose;
	}
	constBuffSkin->Unmap(0, nullptr);

	//�萔�o�b�t�@�փf�[�^�]��
	ConstBufferDataTransform* constMap = nullptr;
	result = constBufferTransform->Map(0, nullptr, (void**)&constMap);
	if (SUCCEEDED(result))
	{
		constMap->viewproj = matViewProjection;
		constMap->world = modelTransform * matWorld;
		constMap->camerapos = camerapos;
		constBufferTransform->Unmap(0, nullptr);
	}

	////�����蔻��X�V
	//if (collider)
	//{
	//	collider->Update();
	//}
}


void Enemy::EnemyDeleate()
{
	position.x = 100.0f;
}

void Enemy::colReset()
{
	col = 0;
}
;


