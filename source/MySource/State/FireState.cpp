#include "FireState.h"
#include "../Object.h"
#include "../Enemy.h"

void FireState::Init(Enemy *obj)
{
}

void FireState::Update(Enemy *obj, HierarchyEnemyState * parent)
{
	obj->CreateBullet();
	obj->m_Parent->SetMove(Float3(0, obj->m_Parent->GetMove().y,0));
	//プレイヤーの位置から自分（エネミー）の角度を算出
	float moveRad = atan2f(
		obj->m_pPlayerTransform->Translate.z - obj->m_Parent->GetTranslate().z,
		obj->m_pPlayerTransform->Translate.x - obj->m_Parent->GetTranslate().x);

	//モデルの元のRotateがおかしいと思われるのでので調整
	float y = 90 * 3.14f / 180.0f - moveRad;

	obj->m_Parent->SetRotate(Float3(0, y, 0));
}
