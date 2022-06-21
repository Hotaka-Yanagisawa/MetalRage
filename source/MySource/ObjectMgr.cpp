#include "ObjectMgr.h"
#include "Object.h"
#include "Enemy.h"
#include "Collider.h"
#include "Player.h"
#include "Bullet.h"
#include "Camera.h"
#include "HP.h"
#include "Push.h"
#include "Collider2D.h"
#include "Model.h"

Object *ObjectMgr::CreateObject(Object_Type Type)
{
	Object *obj;

	Float3 pos(10, 0.5, 0);
	switch (Type)
	{
	case PLAYER:
		obj = new Object();
		obj->SetType(PLAYER);
		//obj->SetScale(5);
		obj->AddComponent<Push>();
		obj->AddComponent<Collider>();
		obj->AddComponent<Cube>();
		obj->GetComponent<Cube>()->SetScale(obj->GetScale());
		obj->AddComponent<Player>()->m_Parent->SetTranslate(pos);
		obj->AddComponent<HP>();
		//モードによって必要かどうか変わるためこの関数の戻り値を利用して必要なモードの時のみ追加する
		//obj->AddComponent<Collider2D>();
		break;

	case ENEMY:
		obj = new Object();
		obj->SetType(ENEMY);
		obj->SetTranslate(pos);
		//obj->SetScale(2);
		obj->AddComponent<Push>();
		obj->AddComponent<Collider>();
		obj->AddComponent<Collider2D>();
		obj->AddComponent<Cube>();
		obj->GetComponent<Cube>()->SetScale(obj->GetScale());
		obj->AddComponent<Enemy>();
		obj->AddComponent<HP>();
		break;
	case BULLET:
		//****************************************************************************************
		//*****プレイヤーの座標が必要かつプレイヤーが発射するものなので別に記述するべきでは*****
		//****************************************************************************************

		//for (int i = 0; i < 2; i++)
		//{
		//	obj = new Object();
		//	obj->AddComponent<Bullet>();
		//	obj->AddComponent<Collider>()->SetScale(0.2f);
		//	obj->SetTranslate(m_Parent->GetTranslate());
		//	if (i == 0)
		//	{
		//		Float3 Add(m_Parent->GetScale().x, 0, 0);
		//		obj->AddTranslate(Add);
		//	}
		//	else
		//	{
		//		Float3 Add(-m_Parent->GetScale().x, 0, 0);
		//		obj->AddTranslate(Add);
		//	}
		//	obj->SetRotate(m_Parent->GetRotate());
		//}
		break;
	case FIELD:
		obj = new Object();
		obj->SetType(FIELD);
		break;
	case MAX:
		break;
	default:
		break;
	}
	return obj;
}

Object * ObjectMgr::CreatePlayer(Float3 Translate, Float3 Scale, int Controller)
{
	Object *obj = new Object();
	obj->SetType(PLAYER);
	obj->SetScale(Scale);
	obj->AddComponent<Push>();
	obj->AddComponent<Collider>();
	//obj->AddComponent<Cube>();
	//obj->GetComponent<Cube>()->SetScale(Scale);
	obj->AddComponent<Model>()->Create();
	obj->AddComponent<Player>()->m_Parent->SetTranslate(Translate);
	obj->GetComponent<Player>()->SetPlayerNum(Controller);
	obj->AddComponent<HP>();
	
	return obj;
}

Object * ObjectMgr::CreateEnemy(Float3 Translate, Float3 Scale, Transform * pTransform)
{
	Object *obj;

	obj = new Object();
	obj->SetType(ENEMY);
	obj->SetTranslate(Translate);
	obj->SetScale(Scale);
	obj->AddComponent<Enemy>()->SetPlayerTransform(pTransform);
	obj->AddComponent<Push>();
	obj->AddComponent<Collider>();
	obj->AddComponent<Collider2D>();
	//obj->AddComponent<Cube>();
	//obj->GetComponent<Cube>()->SetScale(obj->GetScale());
	obj->AddComponent<HP>()->SetHp(80);
	obj->AddComponent<Model>()->Create();

	return obj;
}

Object * ObjectMgr::CreateField(Float3 Translate, Float3 Scale, Figure::Texture Kind, bool Floor)
{
	Object *obj;
	obj = new Object();
	if(!Floor)	obj->SetType(FIELD);
	else        obj->SetType(FLOOR);
	obj->SetTranslate(Translate);
	obj->SetScale(Scale);
	obj->AddComponent<Push>();
	obj->AddComponent<Collider>();
	obj->GetComponent<Collider>()->SetTranslate(Translate);
	obj->GetComponent<Collider>()->SetScale(Scale);
	obj->GetComponent<Collider>()->SetCollisionType(COLLISION_STATIC);
	obj->AddComponent<Cube>()->SetTexNum(Kind);
	obj->GetComponent<Cube>()->SetScale(Scale);
	return obj;
}

Object * ObjectMgr::CreateCollider(Float3 Translate, Float3 Scale, int PlayerNum)
{
	Object *obj;
	obj = new Object();
	obj->SetType(COLLIDER);
	obj->SetTranslate(Translate);
	obj->SetScale(Scale);
	obj->AddComponent<Push>();
	obj->AddComponent<Collider>();
	obj->GetComponent<Collider>()->SetTranslate(Translate);
	obj->GetComponent<Collider>()->SetScale(Scale);
	obj->GetComponent<Collider>()->SetCollisionType(COLLISION_STATIC);
	obj->AddComponent<Cube>();
	obj->GetComponent<Cube>()->SetScale(Scale);
	return obj;
}

void ObjectMgr::AllDeleteObject()
{
	for (auto it = OBJ_LIST.begin(); it != OBJ_LIST.end(); )
	{
		Object *temp = (*it);
		++it;
		delete temp;
	}
	OBJ_LIST.clear();
}
