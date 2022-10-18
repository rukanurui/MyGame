#pragma once
#include"CollisionTypes.h"
#include"3d/fbxobj3d.h"
#include"ColisionInfo.h"



//�R���C�_�[���N���X
class BaseCollider
{
public:
	BaseCollider() = default;

	//���z�f�X�g���N�^
	virtual ~BaseCollider() = default;

	inline void SetObject(FBXobj3d* object) {
		this->fbxobject = object;
	}

	inline FBXobj3d* GetObject3d() {
		return fbxobject;
	}

	virtual void Update() = 0;
	//�`��^�C�v�擾
	inline CollisionShapeType GetShapeType() { return shapeType; }

	//�Փˎ��R�[���o�b�N�֐�
	inline void OnCollision(const CollisionInfo& info) {
		fbxobject->OnCollision(info);
	}

protected://�����o�ϐ�
	FBXobj3d* fbxobject = nullptr;
	//�`��^�C�v
	CollisionShapeType shapeType = SHAPE_UNKNOWN;
};

