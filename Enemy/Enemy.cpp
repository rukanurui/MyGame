#include "Enemy.h"
#include <time.h>

#include"../Collider/QueryCallback.h"
#include"../Collider/CollisionManager.h";



Enemy::Enemy() : FBXobj3d()
{
}


void Enemy::EnemyInitialize(bool shot)
{
	//�����̒ǉ�
	collider->SetColor(COLLISION_COLOR_ENEMY);
	Shot = shot;
	//���f���ǂݍ���
	modelballet = FbxLoader::GetInstance()->LoadModelFromFile("bullet");
	model2 = FbxLoader::GetInstance()->LoadModelFromFile("testfbx");
	count = 0;

	for (std::unique_ptr<Enemybullet>& bullet : bullets)
	{
		bullet->SetPosition(position);
	}
}

void Enemy::EnemyUpdate(XMFLOAT3 playerpos)
{

	//�G�̈ړ�(���@�Ǐ])
	if (col==false)
	{
		if (Shot==false)
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
			Toenemy = XMVector3Normalize(Toenemy);

			//�G�̑��x
			Vel = Toenemy * 0.48f;


			XMMATRIX matScale, matRot, matTrans;
			// �X�P�[���A��]�A���s�ړ��s��̌v�Z
			matScale = XMMatrixScaling(scale.x, scale.y, scale.z);
			matRot = XMMatrixIdentity();
			matRot *= XMMatrixRotationZ(XMConvertToRadians(rotation.z));
			matRot *= XMMatrixRotationX(XMConvertToRadians(rotation.x));
			matRot *= XMMatrixRotationY(XMConvertToRadians(rotation.y));
			matTrans = XMMatrixTranslation(position.x += Vel.m128_f32[0], position.y += Vel.m128_f32[1], position.z += Vel.m128_f32[2]);

			// ���[���h�s��̍���
			matWorld = XMMatrixIdentity(); // �ό`�����Z�b�g
			matWorld *= matScale; // ���[���h�s��ɃX�P�[�����O�𔽉f
			matWorld *= matRot; // ���[���h�s��ɉ�]�𔽉f
			matWorld *= matTrans; // ���[���h�s��ɕ��s�ړ��𔽉f

			//���R���C�_�[�擾
			SphereCollider* sphereCollider = dynamic_cast<SphereCollider*>(collider);
			assert(sphereCollider);

			class EnemyQueryCallback :public QueryCallback
			{
			public:
				EnemyQueryCallback(Sphere* sphere) :sphere(sphere) {};

				//�Փˎ��R�[���o�b�N�֐�
				bool OnQueryHit(const QueryHit& info)
				{
					//���[���h�̏����
					const XMVECTOR up = { 0,1,0,0 };
					//�r�˕���
					XMVECTOR rejectDir = XMVector3Normalize(info.reject);
					//������ƍ��E�����̊p�x���̃R�T�C���l
					float cos = XMVector3Dot(rejectDir, up).m128_f32[0];

					//�����o������
					sphere->center += info.reject;
					move += info.reject;

					return true;
				}

				//�N�G���\�Ɏg�p���鋅
				Sphere* sphere = nullptr;
				//�r�˂ɂ��ړ���(�ݐ�)
				XMVECTOR move = {};
			};

			//�N�G���\�R�[���o�b�N�̊֐��I�u�W�F�N�g
			EnemyQueryCallback callback(sphereCollider);

			//�G�ƓG�̌���������
			CollisionManager::GetInstance()->CheckQuerySphere(*sphereCollider, &callback, COLLISION_COLOR_ENEMY);
			//�����ɂ��r�˕�������
			position.x += callback.move.m128_f32[0];
			position.y += callback.move.m128_f32[1];
			position.z += callback.move.m128_f32[2];

			//�G�ƕǂ̌���������
			CollisionManager::GetInstance()->CheckQueryBox(*sphereCollider, &callback, COLLISION_COLOR_LANDSHAPE);
			//�����ɂ��r�˕�������
			position.x += callback.move.m128_f32[0]*0.05f;
			position.y += callback.move.m128_f32[1]*0.05f;
			position.z += callback.move.m128_f32[2]*0.05f;

		}
		
		if (Shot)
		{
			Attack(playerpos);
		}
	}

	//���S���Ă�����
	if (col==true)
	{
		//20�܂�particle����
		if (partcount <= partnum)
		{
			std::unique_ptr<PartEnemy>newPart = std::make_unique<PartEnemy>();
			newPart->Initialize();
			newPart->SetScale({ 0.01f,0.01f,0.01f });
			newPart->SetModel(model2);
			newPart->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 }, 1.0f));
			newPart->PartInitialize(position);

			//�e�̓o�^
			particle.push_back(std::move(newPart));

			partcount++;
		}

		//particle�̍X�V
		if (parttimer<=150)
		{
			for (std::unique_ptr<PartEnemy>& part : particle)
			{
				part->PartUpdate();
				part->Update();
			}
			parttimer++;
		}
		else
		{
			death = true;
		}
		

	}
	
	Update();

	//�����蔻��X�V
	if (collider)
	{
		collider->Update();
	}


}


void Enemy::Attack(XMFLOAT3 playerpos)
{
	count++;

	//�e�̍폜
	bullets.remove_if([](std::unique_ptr<Enemybullet>& bullet) {
		return bullet->Gethit();
		});

	//if (count != 0)
	//{
	//	//�v���C���[�̍��W
	//	Playerpos.m128_f32[0] = playerpos.x;
	//	Playerpos.m128_f32[1] = playerpos.y;
	//	Playerpos.m128_f32[2] = playerpos.z;

	//	//�G�̍��W
	//	Vecpos.m128_f32[0] = position.x;
	//	Vecpos.m128_f32[1] = position.y;
	//	Vecpos.m128_f32[2] = position.z;

	//	//�����x�N�g���̌v�Z
	//	XMVECTOR Toenemy;
	//	Toenemy = Playerpos - Vecpos;
	//	Toenemy = XMVector3Normalize(Toenemy);

	//	Vel = Toenemy * 0.12f;

	//	XMMATRIX matScale, matRot, matTrans;
	//	// �X�P�[���A��]�A���s�ړ��s��̌v�Z
	//	matScale = XMMatrixScaling(scale.x, scale.y, scale.z);
	//	matRot = XMMatrixIdentity();
	//	matRot *= XMMatrixRotationZ(XMConvertToRadians(rotation.z));
	//	matRot *= XMMatrixRotationX(XMConvertToRadians(rotation.x));
	//	matRot *= XMMatrixRotationY(XMConvertToRadians(rotation.y));
	//	matTrans = XMMatrixTranslation(position.x += Vel.m128_f32[0], position.y += Vel.m128_f32[1], position.z += Vel.m128_f32[2]);

	//	// ���[���h�s��̍���
	//	matWorld = XMMatrixIdentity(); // �ό`�����Z�b�g
	//	matWorld *= matScale; // ���[���h�s��ɃX�P�[�����O�𔽉f
	//	matWorld *= matRot; // ���[���h�s��ɉ�]�𔽉f
	//	matWorld *= matTrans; // ���[���h�s��ɕ��s�ړ��𔽉f

	//	//���R���C�_�[�擾
	//	SphereCollider* sphereCollider = dynamic_cast<SphereCollider*>(collider);
	//	assert(sphereCollider);

	//	class EnemyQueryCallback :public QueryCallback
	//	{
	//	public:
	//		EnemyQueryCallback(Sphere* sphere) :sphere(sphere) {};

	//		//�Փˎ��R�[���o�b�N�֐�
	//		bool OnQueryHit(const QueryHit& info)
	//		{
	//			//���[���h�̏����
	//			const XMVECTOR up = { 0,1,0,0 };
	//			//�r�˕���
	//			XMVECTOR rejectDir = XMVector3Normalize(info.reject);
	//			//������ƍ��E�����̊p�x���̃R�T�C���l
	//			float cos = XMVector3Dot(rejectDir, up).m128_f32[0];

	//			//�����o������
	//			sphere->center += info.reject;
	//			move += info.reject;

	//			return true;
	//		}
	//		//�N�G���\�Ɏg�p���鋅
	//		Sphere* sphere = nullptr;
	//		//�r�˂ɂ��ړ���(�ݐ�)
	//		XMVECTOR move = {};
	//	};

	//	//�N�G���\�R�[���o�b�N�̊֐��I�u�W�F�N�g
	//	EnemyQueryCallback callback(sphereCollider);

	//	//�G�ƓG�̌���������
	//	CollisionManager::GetInstance()->CheckQuerySphere(*sphereCollider, &callback, COLLISION_COLOR_ENEMY);
	//	//�����ɂ��r�˕�������
	//	position.x += callback.move.m128_f32[0];
	//	position.y += callback.move.m128_f32[1];
	//	position.z += callback.move.m128_f32[2];
	//}

	if (count >= 180)
	{
		count = 0;

		//�e�̑��x
		const float bulspeed = 0.5f;
		XMVECTOR Velocity{ 0,0,bulspeed };

		//Velocity={ target.x - position.x, target.y - position.y, target.z - position.z };
		Velocity = { playerpos.x - position.x, playerpos.y - position.y, playerpos.z - position.z };

		Velocity = XMVector3Normalize(Velocity) * bulspeed;

		//�e�̐����Ə�����
		std::unique_ptr<Enemybullet>newBullet = std::make_unique<Enemybullet>();
		newBullet->Initialize();
		newBullet->SetScale({ 0.01f,0.01f,0.01f });
		newBullet->SetModel(modelballet);
		newBullet->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 }, 1.0f));
		newBullet->BulInitialize();
		newBullet->create(position, Velocity);
		
		//�e�̓o�^
		bullets.push_back(std::move(newBullet));
	}

	//�e�̍X�V
	for (std::unique_ptr<Enemybullet>& bullet:bullets)
	{
		bullet->bulupdate();
		bullet->Update();
	}
}


void Enemy::OnCollision(const CollisionInfo& info)
{

	//�e�Ɠ���������
	if (info.collider->color == 4)
	{

	if (scale.x >= 0.01f)
	{
		scale.x = 0.0f; scale.y = 0.0f; scale.z = 0.0f;
	}

	col = true;

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
	col = false;
}


void Enemy::move()
{

}

void Enemy::BulUpdate()
{
	for (std::unique_ptr<Enemybullet>& bullet : bullets)
	{
		bullet->Update();
	}

}


void Enemy::BulDraw(ID3D12GraphicsCommandList* cmdList)
{

	for (std::unique_ptr<Enemybullet>& bullet : bullets)
	{
		bullet->Draw(cmdList);
	}
}

void Enemy::PartUpdate()
{
	for (std::unique_ptr<PartEnemy>& part : particle)
	{
		part->Update();
	}
}

void Enemy::PartDraw(ID3D12GraphicsCommandList* cmdList)
{
	for (std::unique_ptr<PartEnemy>& part : particle)
	{
		part->Draw(cmdList);
	}
}

void Enemy::LastUpdate()
{
	//���S���Ă�����
	if (col == true)
	{
		//20�܂�particle����
		if (partcount <= partnum)
		{
			std::unique_ptr<PartEnemy>newPart = std::make_unique<PartEnemy>();
			newPart->Initialize();
			newPart->SetScale({ 0.01f,0.01f,0.01f });
			newPart->SetModel(model2);
			newPart->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 }, 1.0f));
			newPart->PartInitialize(position);

			//�e�̓o�^
			particle.push_back(std::move(newPart));

			partcount++;
		}

		//particle�̍X�V
		if (parttimer <= 150)
		{
			for (std::unique_ptr<PartEnemy>& part : particle)
			{
				part->PartUpdate();
				part->Update();
			}
			parttimer++;
		}
		else
		{
			death = true;
		}


	}
}

void Enemy::setcol(bool Col)
{
	col = Col;
}

