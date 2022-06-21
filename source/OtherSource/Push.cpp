#include "Push.h"
#include "FloatOperator.h"
#include "Object.h"
#include "Player.h"

void Push::Start()
{
}

void Push::OnCollision(Object * obj)
{
	if (obj->GetType() != PLAYER && obj->GetType() != COLLIDER && obj->GetType() != ENEMY) return;
	Float3 dPos = obj->GetTranslate();
	Float3 sPos = m_Parent->GetTranslate();
	Float3 dSize = obj->GetScale();
	Float3 sSize = m_Parent->GetScale();
	Float3 dMove = obj->GetMove();

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
			obj->SetTranslate(dPos);

			//全ての移動量を0にしてしまうと、
			//他のオブジェクトと押し出しの計算を
			//する際に移動量が無いことになるので、
			//移動量を0にしなければならない成分だけ0にする。
			dMove.x *= 1 - fabsf(Normal[i].x);
			dMove.y *= 1 - fabsf(Normal[i].y);
			dMove.z *= 1 - fabsf(Normal[i].z);
	
			obj->SetMove(dMove);
			break;
		}
	}

	if (obj->GetType() == PLAYER)
	{
		if (m_Parent->GetType() == FLOOR && obj->GetTransform()->Move.y == 0)
		{
			obj->GetComponent<Player>()->m_bJump = false;
		}
		if (m_Parent->GetType() == PLAYER && obj->GetTransform()->Move.y == 0)
		{
			obj->GetComponent<Player>()->m_bJump = false;
		}
	}
}
