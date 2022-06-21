#include "Fade.h"
#include "Defines.h"

void Fade::FadeStart(eFadeState State)
{
	m_State = State;
	switch (m_State)
	{
	case WAIT:
		break;
	case FADEIN:
		SetAlpha(1);
		break;
	case FADEOUT:
		SetAlpha(0);
		break;
	case MAX_FADE:
		break;
	default:
		break;
	}
}

Fade::Fade()
{
}

Fade::~Fade()
{
}

void Fade::Init()
{
	m_State = WAIT;
	m_Alpha = 0;
	m_FadeSpd = 180.0f;
	m_Poly.Start();
	m_Poly.SetColor(Float4(0, 0, 0, 0));
	m_Poly.SetScale(Float3(SCREEN_WIDTH, SCREEN_HEIGHT, 1));
	m_Poly.SetTranslate(Float3(0,0,0));
}

void Fade::Uninit()
{
	m_Poly.Uninit();
}

bool Fade::Update()
{
	if (m_State == FADEIN)
	{
		m_Alpha -= 1.0f / m_FadeSpd;
		m_Poly.SetColor(Float4(0, 0, 0, m_Alpha));
		if (m_Alpha <= 0)
		{
			m_Alpha = 0;
			m_State = WAIT;
		}
	}
	if (m_State == FADEOUT)
	{
		m_Alpha += 1.0f / m_FadeSpd;
		m_Poly.SetColor(Float4(0, 0, 0, m_Alpha));
		if (m_Alpha >= 1)
		{
			m_Alpha = 1;
			m_State = WAIT;
		}
	}

	m_Poly.Update();
	if (m_State == WAIT) return true;

	return false;
}

void Fade::Draw()
{
	if (m_State != WAIT)
	{
		m_Poly.Draw();
	}
}
