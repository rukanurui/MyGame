#pragma once
#include"CollisionTypes.h"
#include"../3d/fbxobj3d.h"
#include"ColisionInfo.h"



//コライダー基底クラス
class BaseCollider
{
public:
	friend class CollisionManager;
	BaseCollider() = default;

	//仮想デストラクタ
	virtual ~BaseCollider() = default;

	inline void SetObject(FBXobj3d* object) {
		this->fbxobject = object;
	}

	inline FBXobj3d* GetObject3d() {
		return fbxobject;
	}

	inline void SetColor(unsigned short color) {
		this->color = color;
	}

	inline void AddColor(unsigned short color) {
		this->color |= color;
	}

	inline void RemoveColor(unsigned short color) {
		this->color &= !color;
	}

	virtual void Update() = 0;
	//形状タイプ取得
	inline CollisionShapeType GetShapeType() { return shapeType; }

	//衝突時コールバック関数
	inline void OnCollision(const CollisionInfo& info) {
		fbxobject->OnCollision(info);
	}

protected://メンバ変数
	FBXobj3d* fbxobject = nullptr;
	//形状タイプ
	CollisionShapeType shapeType = SHAPE_UNKNOWN;
public:
	//当たり判定属性
	unsigned short color = 0b1111111111111111;
};

