#pragma once
#include"CollisionTypes.h"
#include"fbxobj3d.h"
#include"ColisionInfo.h"

//コライダー基底クラス
class BaseCollider
{
public:
	BaseCollider() = default;
	//仮想デストラクタ
	virtual ~BaseCollider() = default;

	inline void SetObject(FBXobj3d* object) {
		this->object3d = object;
	}

	inline FBXobj3d* GetObject3d() {
		return object3d;
	}

	virtual void Update() = 0;
	//形状タイプ取得
	inline CollisionShapeType GetShapeType() { return shapeType; }

protected://メンバ変数
	FBXobj3d* object3d = nullptr;
	//形状タイプ
	CollisionShapeType shapeType = SHAPE_UNKNOWN;
};

