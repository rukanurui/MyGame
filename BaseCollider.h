#pragma once
#include"CollisionTypes.h"
#include"fbxobj3d.h"
#include"ColisionInfo.h"

//�R���C�_�[���N���X
class BaseCollider
{
public:
	BaseCollider() = default;
	//���z�f�X�g���N�^
	virtual ~BaseCollider() = default;

	inline void SetObject(FBXobj3d* object) {
		this->object3d = object;
	}

	inline FBXobj3d* GetObject3d() {
		return object3d;
	}

	virtual void Update() = 0;
	//�`��^�C�v�擾
	inline CollisionShapeType GetShapeType() { return shapeType; }

protected://�����o�ϐ�
	FBXobj3d* object3d = nullptr;
	//�`��^�C�v
	CollisionShapeType shapeType = SHAPE_UNKNOWN;
};

