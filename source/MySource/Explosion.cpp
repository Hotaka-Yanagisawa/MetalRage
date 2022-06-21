#include "Explosion.h"
#include "Object.h"

Explosion::Explosion()
{
}

Explosion::~Explosion()
{
}

void Explosion::Init()
{
	for (int i = 0; i < MAX_EXPLOSION; i++)
	{
		m_Bill[i].Start();
		m_Bill[i].SetTexKind(EXPLOSION);
		m_Bill[i].SetSplit(Float2(7,7));
		m_Bill[i].SetScale(20.0f);
	}
}

void Explosion::Uninit()
{
	for (int i = 0; i < MAX_EXPLOSION; i++)
	m_Bill[i].Uninit();
}

void Explosion::Update()
{
	for (int i = 0; i < MAX_EXPLOSION; i++)
	{
		if (m_Bill[i].GetState() != ANIME::PLAY) continue;
		m_Bill[i].Update();
	}
}

void Explosion::Draw()
{
	for (int i = 0; i < MAX_EXPLOSION; i++)
	{
		if (m_Bill[i].GetState() != ANIME::PLAY) continue;
		m_Bill[i].Draw();

	}
}
void Explosion::Set(Float3 Translate)
{
	for (int i = 0; i < MAX_EXPLOSION; i++)
	{
		if (m_Bill[i].GetState() == ANIME::PLAY) continue;

		m_Bill[i].SetAnime(10, 5, 1.0f);
		m_Bill[i].SetTranslate(Translate);
	}
}
