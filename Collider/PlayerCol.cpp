#include "PlayerCol.h"
#include"QueryCallback.h"
#include"CollisionManager.h";

PlayerCol::PlayerCol()
{

}

void PlayerCol::OnCollision(const CollisionInfo& info)
{
	if (info.collider->color == 8 || info.collider->color == 16)
	{
		hit = 1;
	}

	if (info.collider->color == 1)
	{
		//球コライダー取得
		SphereCollider* sphereCollider = dynamic_cast<SphereCollider*>(collider);
		assert(sphereCollider);

		class PlayerQueryCallback :public QueryCallback
		{
		public:
			PlayerQueryCallback(Sphere* sphere) :sphere(sphere) {};

			//衝突時コールバック関数
			bool OnQueryHit(const QueryHit& info)
			{
				//ワールドの上方向
				const XMVECTOR up = { 0,1,0,0 };
				//排斥方向
				XMVECTOR rejectDir = XMVector3Normalize(info.reject);
				//上方向と左右方向の角度差のコサイン値
				float cos = XMVector3Dot(rejectDir, up).m128_f32[0];

				//押し出し処理
				sphere->center += info.reject;
				move += info.reject;

				return true;
			}
			//クエリ―に使用する球
			Sphere* sphere = nullptr;
			//排斥による移動量(累積)
			XMVECTOR move = {};
		};

		//クエリ―コールバックの関数オブジェクト
		PlayerQueryCallback callback(sphereCollider);

		//敵と敵の交差を検索
		CollisionManager::GetInstance()->CheckQuerySphere(*sphereCollider, &callback, COLLISION_COLOR_LANDSHAPE);
		//交差による排斥分動かす
		position.x += callback.move.m128_f32[0];
		position.y += callback.move.m128_f32[1];
		position.z += callback.move.m128_f32[2];
	}

	HRESULT result;
	XMMATRIX matScale, matRot, matTrans;

	// スケール、回転、平行移動行列の計算
	matScale = XMMatrixScaling(scale.x, scale.y, scale.z);
	matRot = XMMatrixIdentity();
	matRot *= XMMatrixRotationZ(XMConvertToRadians(rotation.z));
	matRot *= XMMatrixRotationX(XMConvertToRadians(rotation.x));
	matRot *= XMMatrixRotationY(XMConvertToRadians(rotation.y));
	matTrans = XMMatrixTranslation(position.x, position.y, position.z);

	// ワールド行列の合成
	matWorld = XMMatrixIdentity(); // 変形をリセット
	matWorld *= matScale; // ワールド行列にスケーリングを反映
	matWorld *= matRot; // ワールド行列に回転を反映
	matWorld *= matTrans; // ワールド行列に平行移動を反映

	//当たり判定更新
	if (collider)
	{
		collider->Update();
	}
	
}

void PlayerCol::colUpdate()
{

	if (hit==0)
	{
		//球コライダー取得
		SphereCollider* sphereCollider = dynamic_cast<SphereCollider*>(collider);
		assert(sphereCollider);

		class PlayerQueryCallback :public QueryCallback
		{
		public:
			PlayerQueryCallback(Sphere* sphere) :sphere(sphere) {};

			//衝突時コールバック関数
			bool OnQueryHit(const QueryHit& info)
			{
				//ワールドの上方向
				const XMVECTOR up = { 0,1,0,0 };
				//排斥方向
				XMVECTOR rejectDir = XMVector3Normalize(info.reject);
				//上方向と左右方向の角度差のコサイン値
				float cos = XMVector3Dot(rejectDir, up).m128_f32[0];

				//押し出し処理
				sphere->center += info.reject;
				move += info.reject;

				return true;
			}
			//クエリ―に使用する球
			Sphere* sphere = nullptr;
			//排斥による移動量(累積)
			XMVECTOR move = {};
		};

		//クエリ―コールバックの関数オブジェクト
		PlayerQueryCallback callback(sphereCollider);

		//敵と敵の交差を検索
		CollisionManager::GetInstance()->CheckQuerySphere(*sphereCollider, &callback, COLLISION_COLOR_LANDSHAPE);
		//交差による排斥分動かす
		position.x += callback.move.m128_f32[0];
		position.y += callback.move.m128_f32[1];
		position.z += callback.move.m128_f32[2];
	}
	
	HRESULT result;
	XMMATRIX matScale, matRot, matTrans;

	// スケール、回転、平行移動行列の計算
	matScale = XMMatrixScaling(scale.x, scale.y, scale.z);
	matRot = XMMatrixIdentity();
	matRot *= XMMatrixRotationZ(XMConvertToRadians(rotation.z));
	matRot *= XMMatrixRotationX(XMConvertToRadians(rotation.x));
	matRot *= XMMatrixRotationY(XMConvertToRadians(rotation.y));
	matTrans = XMMatrixTranslation(position.x, position.y, position.z);

	// ワールド行列の合成
	matWorld = XMMatrixIdentity(); // 変形をリセット
	matWorld *= matScale; // ワールド行列にスケーリングを反映
	matWorld *= matRot; // ワールド行列に回転を反映
	matWorld *= matTrans; // ワールド行列に平行移動を反映

	//当たり判定更新
	if (collider)
	{
		collider->Update();
	}

}



void PlayerCol::ColInitialize()
{
	//属性の追加
	collider->SetColor(COLLISION_COLOR_PLAYER);
}
