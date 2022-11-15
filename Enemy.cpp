#include "Enemy.h"
#include <time.h>



Enemy::Enemy() : FBXobj3d()
{
}


void Enemy::EnemyInitialize()
{
	//�����̒ǉ�
	collider->SetColor(COLLISION_COLOR_ENEMY);
}

void Enemy::EnemyUpdate(XMFLOAT3 playerpos)
{

	//�G�̈ړ�(���@�Ǐ])
	if (col==0)
	{
		//�v���C���[�̍��W
		Playerpos.m128_f32[0] = playerpos.x;
		Playerpos.m128_f32[1] = playerpos.y;
		Playerpos.m128_f32[2] = playerpos.z;

		//�G�̍��W
		Vecpos.m128_f32[0] = position.x;
		Vecpos.m128_f32[1] = position.y;
		Vecpos.m128_f32[2] = position.z;

		//�����x�N�g���̌v�Z
		XMVECTOR Toenemy;
		Toenemy = Playerpos - Vecpos;
		Toenemy=XMVector3Normalize(Toenemy);

		Vel = Toenemy * 0.05f;


		XMMATRIX matScale, matRot, matTrans;
		// �X�P�[���A��]�A���s�ړ��s��̌v�Z
		matScale = XMMatrixScaling(scale.x, scale.y, scale.z);
		matRot = XMMatrixIdentity();
		matRot *= XMMatrixRotationZ(XMConvertToRadians(rotation.z));
		matRot *= XMMatrixRotationX(XMConvertToRadians(rotation.x));
		matRot *= XMMatrixRotationY(XMConvertToRadians(rotation.y));
		matTrans = XMMatrixTranslation(position.x +=Vel.m128_f32[0], position.y += Vel.m128_f32[1], position.z += Vel.m128_f32[2]);

		// ���[���h�s��̍���
		matWorld = XMMatrixIdentity(); // �ό`�����Z�b�g
		matWorld *= matScale; // ���[���h�s��ɃX�P�[�����O�𔽉f
		matWorld *= matRot; // ���[���h�s��ɉ�]�𔽉f
		matWorld *= matTrans; // ���[���h�s��ɕ��s�ړ��𔽉f
	}
	

	//�����蔻��X�V
	if (collider)
	{
		collider->Update();
	}
}


void Enemy::OnCollision(const CollisionInfo& info)
{

	if (info.collider->color==2)
	{

	if (scale.x >= 0.01f)
	{
		scale.x = 0.005f; scale.y = 0.005f; scale.z = 0.005f;
	}

	col = 1;

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

	if (info.collider->color == 6)
	{
		
	}

	//�����蔻��X�V
	if (collider)
	{
		collider->Update();
	}


}



void Enemy::colReset()
{
	col = 0;
}


void Enemy::move()
{

}
;


