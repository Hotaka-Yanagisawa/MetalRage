#include "Collision.h"
#include "Object.h"
#include "Collider2D.h"
#include "Enemy.h"
#include "State/PatrolState.h"
#include "State/DiscoveryState.h"

Collision::Collision()
{
}

Collision::~Collision()
{
	Uninit();
}

bool Collision::Init()
{
	return true;
}

void Collision::Uninit()
{
}

void Collision::Update()
{
	int ShiftNum = -1;
	// リストを回す
	for (auto A : COLLIDER_LIST)
	{
		++ShiftNum;
		int continueNum = ShiftNum + 1;
		for (auto B : COLLIDER_LIST)
		{
			if (continueNum > 0)
			{
				continueNum--;
				continue;
			}
			// 四角形同士の当たり判定
			// 2Dでも3Dでも
			// 中心までの距離 < 半分の大きさを足し合わせた数は変わらない。
			// 計算する軸が増えるだけ
			Float3 aPos = (*A).m_Parent->GetTranslate();
			Float3 bPos = (*B).m_Parent->GetTranslate();
			Float3 aScale = (*A).m_Parent->GetScale();
			Float3 bScale = (*B).m_Parent->GetScale();

			Float3 distance(
				fabsf(bPos.x - aPos.x),
				fabsf(bPos.y - aPos.y),
				fabsf(bPos.z - aPos.z)
			);

			bool hitX = distance.x < (aScale.x + bScale.x) * 0.5f;
			bool hitY = distance.y < (aScale.y + bScale.y) * 0.5f;
			bool hitZ = distance.z < (aScale.z + bScale.z) * 0.5f;

			// 当たり判定の結果
			if (hitX && hitY && hitZ)
			{
				for (auto i : A->m_Parent->ComponentList) i->OnCollision(B->m_Parent);
				for (auto j : B->m_Parent->ComponentList) j->OnCollision(A->m_Parent);
			}
		}
	}
	ShiftNum = -1;
	
	// リストを回す
	for (auto A : COLLIDER2D_LIST)
	{
		if (A->m_Parent->GetType() != PLAYER) continue;
		for (auto B : COLLIDER2D_LIST)
		{
			Fan fan;
			fan.Position.x = B->m_Parent->GetTransform()->Translate.x;
			fan.Position.y = B->m_Parent->GetTransform()->Translate.z;
			fan.Length = 20;
			fan.FanDegree = 360;
			fan.RotateDegree = 180;
			Float2 point;
			point.x = A->m_Parent->GetTransform()->Translate.x;
			point.y = A->m_Parent->GetTransform()->Translate.z;
		
			if (IsCollidingFanAndPoint(fan, point))
			{
				if (B->m_Parent->GetType() == ENEMY)
				{
					//B->m_Parent->GetComponent<Enemy>()->CreateBullet();
					if (B->m_Parent->GetComponent<Enemy>()->GetHierarchyState() != DiscoveryState::GetInstance())
					{
						B->m_Parent->GetComponent<Enemy>()->SetHierarchyState(DiscoveryState::GetInstance());
					}
					B->m_Parent->GetComponent<Enemy>()->m_Placemark.SetColor(Float4(1, 0, 0, 1));
				}
			}
			else
			{
				if (B->m_Parent->GetComponent<Enemy>()->GetHierarchyState() != PatrolState::GetInstance())
				{
					B->m_Parent->GetComponent<Enemy>()->SetHierarchyState(PatrolState::GetInstance());
				}
				B->m_Parent->GetComponent<Enemy>()->m_Placemark.SetColor(Float4(0, 1, 0, 1));

			}
		}	
	}
}

bool Collision::IsCollidingFanAndPoint(Fan fan, Float2 point)
{
	const float RAD = 3.141519f / 180.0f;

	// 点と扇のベクトル
	Float2 vec_fan_to_point = {
		point.x - fan.Position.x,
		point.y - fan.Position.y
	};

	// ベクトルの長さ算出
	float vec_length = sqrtf((vec_fan_to_point.x * vec_fan_to_point.x) + (vec_fan_to_point.y * vec_fan_to_point.y));

	// ベクトルと扇の距離の比較
	if (fan.Length < vec_length)
	{
		// 当たっていない
		return false;
	}

	// 円弧の方向ベクトルを求める
	float rotate_rad = fan.RotateDegree * RAD;
	Float2 fan_dir =
	{
		1.0f,
		0.0f
	};

	// ベクトルを回転させる
	Float2 rotate_fan_dir
	{
		fan_dir.x * cosf(rotate_rad) + fan_dir.y * -sinf(rotate_rad),
		fan_dir.x * sinf(rotate_rad) + fan_dir.y * cosf(rotate_rad)
	};

	// 扇と点のベクトルを単位ベクトルにする
	Float2 normal_fan_to_point = {
		vec_fan_to_point.x / vec_length,
		vec_fan_to_point.x / vec_length
	};

	// 内積計算
	float dot = normal_fan_to_point.x * rotate_fan_dir.x + normal_fan_to_point.y * rotate_fan_dir.y;

	// 扇の範囲をcosにする
	float fan_cos = cosf((fan.FanDegree / 2.0f) * RAD);

	// 点が扇の範囲内にあるかを比較する
	if (fan_cos > dot)
	{
		// 当たってない
		return false;
	}

	return true;
}

void Collision::Register(Collider * pA, Collider * pB)
{
	//if (m_registerNum > MAX_COLLISION_REGISTER) return;

	//m_pList[m_registerNum][0] = pA;
	//m_pList[m_registerNum][1] = pB;
	//++m_registerNum;
}

void Collision::Push(Collider * pDynamic, Collider * pStatic)
{
	Float3 dPos  = pDynamic->m_Parent->GetTranslate();
	Float3 sPos  = pStatic->m_Parent->GetTranslate();
	Float3 dSize = pDynamic->m_Parent->GetScale();
	Float3 sSize = pStatic->m_Parent->GetScale();
	Float3 dMove = pDynamic->m_Parent->GetMove();
	
	//計算に必要な情報を抜き出す
	//移動量から移動する方向を求める
	//※移動する方向は１か-1で表す
	Float3 dir(dMove.x > 0 ? 1 : -1, dMove.y > 0 ? 1 : -1, dMove.z > 0 ? 1 : -1);
	//実際に当たり判定でめり込んだのは、オブジェクトの座標ではなく、
	//角だけがめり込んでいることもあるので、対象の角を計算で求める
	Float3 dPoint
				(dPos.x + dir.x * dSize.x * 0.5f, dPos.y + dir.y * dSize.y * 0.5f, dPos.z + dir.z * dSize.z * 0.5f);
	//移動前の角の座標
	//そのままの移動量で移動前の座標を表そうとすると浮動小数点の計算誤差により、
	//移動ベクトルの始点が面の内側にあることになり、貫通してないと判定される。
	//これを回避するために、移動前の位置が遠くなるように
	//計算の時だけ、移動量を大きくする
	Float3 prePoint(dPoint.x - dMove.x * 1.1f, dPoint.y - dMove.y * 1.1f, dPoint.z - dMove.z * 1.1f);
	//衝突された側の角を計算
	//衝突された側の角は移動方向を反転した方向に向かって大きさの半分を足すと求められる
	Float3 sPoint
				(sPos.x - dir.x * sSize.x * 0.5f, sPos.y - dir.y * sSize.y * 0.5f, sPos.z - dir.z * sSize.z * 0.5f);
	// 面上の一点から移動ベクトルの始点と終点へ向かうベクトル(の長さ?)を計算する
	Float3 vStart(prePoint.x - sPoint.x, prePoint.y - sPoint.y, prePoint.z - sPoint.z);
	Float3 vEnd(dPoint.x - sPoint.x, dPoint.y - sPoint.y, dPoint.z - sPoint.z);

	//それぞれの面と計算
	//各面の法線ベクトル
	Float3 Normal[] =
	{
		Float3(-dir.x, 0, 0),	//xの面
		Float3(0, -dir.y, 0),	//yの面
		Float3(0, 0, -dir.z),	//zの面ということだと思われる　角は三つの面の頂点だから３つ
	};

	for (int i = 0; i < _countof(Normal); i++)
	{
		//面の法線との内積を計算
		float dotS = vStart.x * Normal[i].x + vStart.y * Normal[i].y + vStart.z * Normal[i].z;
		float dotE = vEnd.x   * Normal[i].x + vEnd.y   * Normal[i].y + vEnd.z   * Normal[i].z;
		//それぞれの内積の結果が正と負の値であれば移動ベクトルが面を貫通している
		//正と負の組み合わせかどうかは掛け算で判定できる
		//(正*負=負 / 正*正=正 / 負*負=正）
		if (dotS * dotE < 0)
		{
			//移動ベクトルの方向にめりこんだ量を戻すのではなく、面の方向に向かって
			//戻す(戻す距離は内積の値と等しい)
			dotE = fabsf(dotE);
			dPos.x += Normal[i].x * dotE;
			dPos.y += Normal[i].y * dotE;
			dPos.z += Normal[i].z * dotE;
			pDynamic->m_Parent->SetTranslate(dPos);
			//全ての移動量を0にしてしまうと、
			//他のオブジェクトと押し出しの計算を
			//する際に移動量が無いことになるので、
			//移動量を0にしなければならない成分だけ0にする。
			dMove.x *= 1 - fabsf(Normal[i].x);
			dMove.y *= 1 - fabsf(Normal[i].y);
			dMove.z *= 1 - fabsf(Normal[i].z);
			pDynamic->m_Parent->SetMove(dMove);
			break;
		}
	}


}

