#include "MoveState.h"
#include "../Object.h"
#include "../Enemy.h"

void MoveState::Init(Enemy *obj)
{
	
}

void MoveState::Update(Enemy *obj, HierarchyEnemyState * parent)
{
	//目的地に着いたら次の目的地の番号の設定
	if (fabsf(obj->m_MovePoint.x - obj->m_Parent->GetTranslate().x) +
		fabsf(obj->m_MovePoint.z - obj->m_Parent->GetTranslate().z) < 1)
	{
		obj->m_nPointNum = rand() % (19*19);
		if (obj->m_nPointNum > 19 * 19 - 1)
		{
			obj->m_nPointNum = 0;
		}
	}
	//現在の目的地設定
	obj->m_MovePoint = obj->m_decidedPoints[obj->m_nPointNum / 19][obj->m_nPointNum % 19];

	//目的地に向けて移動量の設定
	float Rad = atan2f(obj->m_MovePoint.z - obj->m_Parent->GetTranslate().z,
					   obj->m_MovePoint.x - obj->m_Parent->GetTranslate().x);

	obj->m_Parent->GetTransform()->Move.x = cosf(Rad) * 0.1f;
	obj->m_Parent->GetTransform()->Move.y = -0.1f;
	obj->m_Parent->GetTransform()->Move.z = sinf(Rad) * 0.1f;

	//目的地の位置から自分（エネミー）の角度を算出
	float moveRad = atan2f(
		obj->m_MovePoint.z - obj->m_Parent->GetTranslate().z,
		obj->m_MovePoint.x - obj->m_Parent->GetTranslate().x);
	
	obj->m_Parent->SetRotate(Float3(0, 90 * 3.14f / 180.0f - moveRad, 0));
}
