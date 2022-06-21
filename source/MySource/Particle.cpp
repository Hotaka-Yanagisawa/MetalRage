#include "Particle.h"
#include "DirectX.h"

Particle::Particle()
{
}

Particle::~Particle()
{
}

void Particle::Init()
{
	for (int i = 0; i < MAX_PARTICLE; i++)
	{
		m_Particle[i].m_Bb.Start();
		m_Particle[i].m_Bb.SetTexKind(TEX_BULLET);
		m_Particle[i].m_Bb.SetSplit(Float2(8,8));
		m_Particle[i].bExist = false;
		m_Particle[i].fLife = 3;
		m_Particle[i].Move = Float3(1, 1, 1);
	}
}

void Particle::Uninit()
{
	for (int i = 0; i < MAX_PARTICLE; i++)
	{
		m_Particle[i].m_Bb.Uninit();
	}
}

void Particle::Update()
{
	for (int i = 0; i < MAX_PARTICLE; i++)
	{
		if (!m_Particle[i].bExist) continue;
		m_Particle[i].fLife -= 1.0f / 60.0f;
		if (m_Particle[i].fLife <= 0) m_Particle[i].bExist = false;
		Float3 Translate = m_Particle[i].m_Bb.GetTranslate();
		Float3 Move = Float3((rand() % 3 - 1)*0.3f, (rand() % 3 - 1)*0.3f, (rand() % 3 - 1)*0.3f);
		m_Particle[i].Move = Move;
		Translate += m_Particle[i].Move;
		m_Particle[i].m_Bb.SetTranslate(Translate);
		m_Particle[i].m_Bb.Update();
	}
}

void Particle::Draw()
{
	SetBlendMode(BLEND_ADD);
	for (int i = 0; i < MAX_PARTICLE; i++)
	{
		if (!m_Particle[i].bExist) continue;
		m_Particle[i].m_Bb.Draw();
	}
	SetBlendMode(BLEND_ALPHA);
}

void Particle::Set(Float3 Translate)
{
	for (int i = 0; i < MAX_PARTICLE; i++)
	{
		if (m_Particle[i].bExist) continue;
		m_Particle[i].m_Bb.Start();
		m_Particle[i].m_Bb.SetTexKind(TEX_BULLET);
		m_Particle[i].m_Bb.SetSplit(Float2(8, 8));
		m_Particle[i].bExist = true;
		m_Particle[i].fLife = 3;
		m_Particle[i].m_Bb.SetAnime(0, 60, 1, true);
		m_Particle[i].m_Bb.SetTranslate(Translate);
		
		break;
	}
}

