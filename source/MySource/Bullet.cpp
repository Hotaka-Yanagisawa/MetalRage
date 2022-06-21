#include "Bullet.h"
#include "Object.h"
#include "Player.h"
#include "Camera.h"
#include "Explosion.h"

CSound Bullet::m_Sound;
Bullet::Bullet()
{
	m_nAttack = 0;
	m_Time = 120;
	m_bType = true;
	m_Num = 0;
	m_Sound.m_pBuffer = m_Sound.CreateSound("Assets/Sound/SE/Hit_3.mp3");
	m_Sound.m_pSpeaker = m_Sound.PlaySound(m_Sound.m_pBuffer);
	m_Sound.m_pSpeaker->SetVolume(0.0f);
}

Bullet::~Bullet()
{
}

void Bullet::Start()
{
	m_nAttack = 20;
}


void Bullet::Update()
{
	m_Sound.Update();
	--m_Time;
	if (m_Time < 1)
	{
		m_Parent->SetUse(false);
	}
	if (m_bType)
	{
		const float RAD = 3.141519f / 180.0f;
		Float3 move;
		if (m_Num != 1)
		{
			move = Float3(cosf((m_CameraXzAngle + 91)* RAD) * 1.5f,
				-sinf((m_CameraYAngle - 30) * RAD),
				sinf((m_CameraXzAngle + 91)* RAD) *1.5f);
		}
		else
		{
			move = Float3(cosf((m_CameraXzAngle + 89)* RAD) * 1.5f,
				-sinf((m_CameraYAngle - 30) * RAD),
				sinf((m_CameraXzAngle + 89)* RAD) * 1.5f);
		}
		m_Parent->SetMove(move);
	}
}

void Bullet::Draw()
{
}

void Bullet::OnCollision(Object *obj)
{
	if (obj == m_pLord) return;	//自分に当たるのを防ぐ処理

	switch (obj->GetType())
	{
	case PLAYER:
		if (!m_Parent->GetUse()) break;
		m_Parent->SetUse(false);
		m_Sound.m_pSpeaker = m_Sound.PlaySound(m_Sound.m_pBuffer);
		m_Sound.m_pSpeaker->SetVolume(0.0f);
		m_Sound.m_bFade = false;
		if (m_pLord->GetType() == PLAYER)
		{
			m_pLord->GetComponent<Player>()->SetHitCheck();
			obj->GetComponent<Player>()->m_pCamera->Shaking(30);
			Explosion::GetInstance()->Set(obj->GetTranslate());
			m_Sound.m_bFade = m_Sound.Fade(0.8f, 0.01f);
			m_Sound.Update();
		}
		else
		{
			m_Sound.m_bFade = m_Sound.Fade(0.3f, 0.01f);
			if(obj->GetComponent<Player>()->m_pCamera->GetTime() < 1)
			obj->GetComponent<Player>()->m_pCamera->Shaking(5);
			m_Sound.Update();
		}
		//エフェクト
		//できるならカメラ揺れ、反動で少し操作性変化するとか行動不能とか少し後ろに移動するとか
		break;
	case ENEMY:
		if (!m_Parent->GetUse()) break;
		m_Parent->SetUse(false);
		Explosion::GetInstance()->Set(obj->GetTranslate());
		if (m_pLord->GetType() == PLAYER)
		{
			m_pLord->GetComponent<Player>()->SetHitCheck();
			m_Sound.m_pSpeaker = m_Sound.PlaySound(m_Sound.m_pBuffer);
			m_Sound.m_pSpeaker->SetVolume(0.0f);
			m_Sound.m_bFade = false;
			m_Sound.m_bFade = m_Sound.Fade(0.8f, 0.01f);
			m_Sound.Update();
		}

		break;
	case BULLET:
		break;
	case FIELD:
		if (!m_Parent->GetUse()) break;
		m_Parent->SetUse(false);
		
		break;
	case FLOOR:
		if (!m_Parent->GetUse()) break;
		m_Parent->SetUse(false);
		
		break;
	}
}
