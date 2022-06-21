#include "Enemy.h"
#include "State/PatrolState.h"
#include "State/DiscoveryState.h"
#include "State/EnemyState.h"
#include "State/HierarchyEnemyState.h"
#include "Object.h"
#include "Bullet.h"
#include "Collider.h"
#include "Cube.h"


Float3 Enemy::m_decidedPoints[19][19];
int Enemy::m_Num;
Enemy::Enemy()
{
}

Enemy::~Enemy()
{
	--m_Num;
}

void Enemy::Start()
{
	++m_Num;
	m_HierarchyState = PatrolState::GetInstance();
	m_HierarchyState->Init(this);
	m_fan.Length = 10;
	m_fan.FanDegree = 180;
	m_fan.Position = -9999;
	m_fan.RotateDegree = 0;

	m_nPointNum = rand() % (19 * 19);
	if (m_nPointNum > 19 * 19 - 1)
	{
		m_nPointNum = 0;
	}
	m_MovePoint = m_decidedPoints[m_nPointNum / 19][m_nPointNum % 19];

	m_Placemark.Start();
	m_Placemark.SetTexKind(NULL_TEX);
	if (m_HierarchyState == PatrolState::GetInstance())
	{
		m_Placemark.SetColor(Float4(0, 1, 0, 1));
	}
	else
	{
		m_Placemark.SetColor(Float4(1, 0, 0, 1));
	}

	m_bFire = false;
	m_FireInterval = 0;
}

void Enemy::Update()
{
	if (m_bReload)
	{
		m_ReloadTime -= 1.0f / 60.0f;
		if (m_ReloadTime < 0)
		{
			m_ReloadTime = 0;

			m_MagazineNum = MAGAZINE_SIZE;
			m_bReload = false;
		}
	}

	if (m_bFire)
	{
		m_FireInterval -= 1.0f / 60.0f;
		if (m_FireInterval <= 0)
		{
			m_FireInterval = 0;
			m_bFire = false;
		}
	}


	m_HierarchyState->Update(this);
	m_fan.Position.x = m_Parent->GetTranslate().x;
	m_fan.Position.y = m_Parent->GetTranslate().z;
	


	m_Placemark.SetTranslate(Float3(
		m_Parent->GetTranslate().x,
		m_Parent->GetTranslate().y + m_Parent->GetScale().y / 2 + 1,
		m_Parent->GetTranslate().z));

	m_Placemark.Update();
}

void Enemy::Draw()
{
	m_Placemark.Draw();
}

void Enemy::PointsInit()
{
	for (int j = 0; j < 19; j++)
	{
		for (int i = 0; i < 19; i++)
		{
			m_decidedPoints[j][i].x = -45 + 5 * i;
			m_decidedPoints[j][i].z = -45 + 5 * j;
			m_decidedPoints[j][i].y = 2;
		}
	}

}

void Enemy::SetState(EnemyState * newState)
{
	m_State = newState; 
	m_State->Init(this);
}

void Enemy::SetHierarchyState(HierarchyEnemyState * newState)
{
	m_HierarchyState = newState;
	m_HierarchyState->Init(this);
}

void Enemy::CreateBullet()
{
	//発射間隔中なら処理を行わない
	if (m_bFire) return;
	//マガジン内が1以下なら処理を行わない
	if (m_MagazineNum < 1) return;
	//打つ分マガジン内から弾減らす
	m_MagazineNum--;
	//マガジンが空になったら強制リロード
	if (m_MagazineNum <= 0 && !m_bReload)
	{
		if (m_MagazineNum >= MAGAZINE_SIZE) return;
		m_ReloadTime = RELOAD_TIME;
		m_bReload = true;
	}
	//発射間隔
	m_FireInterval = FIRE_INTERVAL;
	m_bFire = true;

	float moveRad = atan2f(m_pPlayerTransform->Translate.z - m_Parent->GetTranslate().z,
		m_pPlayerTransform->Translate.x - m_Parent->GetTranslate().x);

	float moveRad2 = atan(m_pPlayerTransform->Translate.y - m_Parent->GetTranslate().y);

	Float3 move;

	move.x = cosf(moveRad) * 0.8f;
	move.y = sinf(moveRad2) * 0.025f;
	move.z = sinf(moveRad) * 0.8f;

	Object *obj;

	obj = new Object();
	obj->SetType(BULLET);
	obj->AddComponent<Bullet>()->m_Parent->SetMove(move);
	obj->GetComponent<Bullet>()->SetLord(m_Parent);
	obj->GetComponent<Bullet>()->SetType(false);
	obj->GetComponent<Bullet>()->SetAttack(5);
	obj->AddComponent<Collider>()->SetScale(0.1f);
	obj->AddComponent<Cube>();
	obj->GetComponent<Cube>()->SetScale(obj->GetScale());
	obj->GetComponent<Cube>()->SetTexNum(Figure::BRICK);
	obj->SetTranslate(m_Parent->GetTranslate());
	obj->SetRotate(m_Parent->GetRotate());
}

