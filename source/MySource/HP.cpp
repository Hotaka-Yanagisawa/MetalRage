#include "HP.h"
#include "Object.h"
#include "Bullet.h"
#include "State/PvEState.h"

void HP::Start()
{
	m_nHp = 450;
}

void HP::OnCollision(Object *obj)
{
	switch (obj->GetType())
	{
	case PLAYER:
		break;
	case ENEMY:
		break;
	case BULLET:
		Bullet *pOpponent;
		pOpponent = obj->GetComponent<Bullet>();
		
		if (pOpponent != nullptr)
		{
			if (pOpponent->GetLord() == m_Parent) break;	//自分に当たるのを防ぐ処理
			//敵→敵の場合も処理しない
			if (pOpponent->GetLord()->GetType() == ENEMY && m_Parent->GetType() == ENEMY)	return;	

			m_nHp -= pOpponent->GetAttack();
			if (m_nHp < 1)
			{
				if (!m_Parent->GetUse()) break;
				m_Parent->SetUse(false);
				PvEState::GetInstance()->m_nKillsNum++;
				if (PvEState::GetInstance()->m_nKillsNum > 99)
					PvEState::GetInstance()->m_nKillsNum = 99;
			}
		}
		break;
	case FIELD:
		break;
	case MAX:
		break;
	default:
		break;
	}

}
