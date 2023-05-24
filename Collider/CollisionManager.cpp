#include "CollisionManager.h"
#include"BaseCollider.h"
#include"Collision.h"

using namespace DirectX;

CollisionManager* CollisionManager::GetInstance()
{
	static CollisionManager instance;
	return &instance;
}

void CollisionManager::CheckAllCollisions()
{
	std::forward_list<BaseCollider*>::iterator itA;
	std::forward_list<BaseCollider*>::iterator itB;
	//全ての組み合わせについて総当たりチェック
	itA = colliders.begin();
	for (;itA != colliders.end(); ++itA)
	{
		itB = itA;
		++itB;
		for (; itB != colliders.end(); ++itB)
		{
			BaseCollider* colA = *itA;
			BaseCollider* colB = *itB;

			//ともに球
			 if (colA->GetShapeType()==COLLISIONSHAPE_SPHERE&&
				colB->GetShapeType()==COLLISIONSHAPE_SPHERE)
			{
				Sphere* SphereA = dynamic_cast<Sphere*>(colA);
				Sphere* SphereB = dynamic_cast<Sphere*>(colB);
				DirectX::XMVECTOR inter;
				if (Collision::CheckSphere2Sphere(*SphereA, *SphereB, &inter)) {
					colA->OnCollision(CollisionInfo(colB->GetObject3d(), colB, inter));
					colB->OnCollision(CollisionInfo(colA->GetObject3d(), colA, inter));
				}
			}

			 //球と直方体
			 if (colA->GetShapeType() == COLLISIONSHAPE_SPHERE &&
				 colB->GetShapeType() == COLLISIONSHAPE_BOX)
			 {

				 Sphere* SphereA = dynamic_cast<Sphere*>(colA);
				 Box* BoxB = dynamic_cast<Box*>(colB);
				 DirectX::XMVECTOR inter;

				 if (Collision::CheckSphere2Box(*SphereA, *BoxB, &inter))
				 {
					 colA->OnCollision(CollisionInfo(colB->GetObject3d(), colB, inter));
					 colB->OnCollision(CollisionInfo(colA->GetObject3d(), colA, inter));
				 }
			 }

			//球と直方体反対
			else if (colA->GetShapeType() == COLLISIONSHAPE_BOX &&
				colB->GetShapeType() == COLLISIONSHAPE_SPHERE)
			{
				Box* BoxA = dynamic_cast<Box*>(colA);
				Sphere* SphereB = dynamic_cast<Sphere*>(colB);
				DirectX::XMVECTOR inter;
				if (Collision::CheckSphere2Box(*SphereB, *BoxA, &inter)) {
					colA->OnCollision(CollisionInfo(colB->GetObject3d(), colB, inter));
					colB->OnCollision(CollisionInfo(colA->GetObject3d(), colA, inter));
				}
			}

		}
	}
}

void CollisionManager::CheckQuerySphere(const Sphere& sphere, QueryCallback* callback,unsigned short color)
{
	assert(callback);

	std::forward_list<BaseCollider*>::iterator it;

	//すべてのコライダーと総当たりチェック
	it = colliders.begin();
	for (; it != colliders.end(); ++it)
	{
		BaseCollider* col = *it;

		//属性が合わなければスキップ
		if (!(col->color&color))
		{
			continue;
		}

		//球の場合
		if (col->GetShapeType() == COLLISIONSHAPE_SPHERE)
		{

			Sphere* sphereB = dynamic_cast<Sphere*>(col);
			XMVECTOR tempInter;
			XMVECTOR tempReject;

			//当たらなければ除外
			if (!Collision::CheckSphere2Sphere(sphere, *sphereB, &tempInter, &tempReject))continue;

			//交差情報をセット
			QueryHit info;
			info.collider = col;
			info.object = col->GetObject3d();
			info.inter = tempInter;
			info.reject = tempReject;

			//クエリ―コールバック呼び出し
			if (!callback->OnQueryHit(info))
			{
				//戻り値がfalseの場合終了
				return;
			}
		}
		//次の当たり判定
	}

}

void CollisionManager::CheckQueryBox(const Sphere& sphere, QueryCallback* callback, unsigned short color)
{
	assert(callback);

	std::forward_list<BaseCollider*>::iterator it;

	//すべてのコライダーと総当たりチェック
	it = colliders.begin();
	for (; it != colliders.end(); ++it)
	{
		BaseCollider* col = *it;

		//属性が合わなければスキップ
		if (!(col->color & color))
		{
			continue;
		}

		//矩形の場合
		if (col->GetShapeType() == COLLISIONSHAPE_BOX)
		{

			Box* box = dynamic_cast<Box*>(col);
			XMVECTOR tempInter;
			XMVECTOR tempReject;

			//当たらなければ除外
			if (!Collision::CheckSphere2Box(sphere, *box, &tempInter, &tempReject))continue;

			//交差情報をセット
			QueryHit info;
			info.collider = col;
			info.object = col->GetObject3d();
			info.inter = tempInter;
			info.reject = tempReject;

			//クエリ―コールバック呼び出し
			if (!callback->OnQueryHit(info))
			{
				//戻り値がfalseの場合終了
				return;
			}
		}
		//次の当たり判定
	}

}

void CollisionManager::CheckBoxShere() 
{
	std::forward_list<BaseCollider*>::iterator itA;
	std::forward_list<BaseCollider*>::iterator itB;
	//全ての組み合わせについて総当たりチェック
	itA = colliders.begin();
	for (; itA != colliders.end(); ++itA)
	{
		itB = itA;
		++itB;
		for (; itB != colliders.end(); ++itB)
		{
			BaseCollider* colA = *itA;
			BaseCollider* colB = *itB;
			//球と直方体
			if (colA->GetShapeType() == COLLISIONSHAPE_SPHERE &&
				colB->GetShapeType() == COLLISIONSHAPE_BOX)
			{
				Sphere* SphereA = dynamic_cast<Sphere*>(colA);
				Box* BoxB = dynamic_cast<Box*>(colB);
				DirectX::XMVECTOR inter;
				if (Collision::CheckSphere2Box(*SphereA, *BoxB, &inter)) {
					colA->OnCollision(CollisionInfo(colB->GetObject3d(), colB, inter));
					colB->OnCollision(CollisionInfo(colA->GetObject3d(), colA, inter));
				}
			}
			/*else if(colA->GetShapeType() == COLLISIONSHAPE_BOX &&
				colB->GetShapeType() == COLLISIONSHAPE_SPHERE)
			{
				Box* BoxA = dynamic_cast<Box*>(colA);
				Sphere* SphereB = dynamic_cast<Sphere*>(colB);
				DirectX::XMVECTOR inter;
				if (Collision::CheckSphere2Box(*SphereA, *BoxB, &inter)) {
					colA->OnCollision(CollisionInfo(colB->GetObject3d(), colB, inter));
					colB->OnCollision(CollisionInfo(colA->GetObject3d(), colA, inter));
				}

			}*/

		}
	}

}

bool CollisionManager::RayCast(const Ray& ray, RayCastHit* hitinfo, float MaxDistance)
{
	bool result = false;
	//走査用のイテレーター
	std::forward_list<BaseCollider*>::iterator it;
	//今までで最も近いコライダーを記録するためのイテレーター
	std::forward_list<BaseCollider*>::iterator it_hit;
	//今までで最も近いコライダーとの距離を記録するためのイテレーター
	float distance = MaxDistance;
	//今までで最も近いコライダーとの交点を記録するためのイテレーター
	XMVECTOR inter;
	//すべてのコライダーと総当たりチェック
	it = colliders.begin();
	for (; it != colliders.end(); ++it)
	{
		BaseCollider* colA = *it;
		//球の場合
		if (colA->GetShapeType() == COLLISIONSHAPE_SPHERE)
		{
			Sphere* sphere = dynamic_cast<Sphere*>(colA);
			float tempDistance;
			XMVECTOR tempInter;
			//当たらなければ除外
			if (!Collision::CheckRay2Sphere(ray, *sphere, &tempDistance, &tempInter))continue;
			//距離が最小でなければ除外
			if (tempDistance >= distance)continue;
			//今までで最も距離が近いので判定をとる
			result = true;
			distance = tempDistance;
			inter = tempInter;
			it_hit = it;
		}
		//次の当たり判定
	}
	//最終的に何かに当たってたら結果を書き込む
	if (result&&hitinfo)
	{
		hitinfo->distance = distance;
		hitinfo->inter = inter;
		hitinfo->collider = *it_hit;
		hitinfo->object = hitinfo->collider->GetObject3d();
	}
	return result;
}
