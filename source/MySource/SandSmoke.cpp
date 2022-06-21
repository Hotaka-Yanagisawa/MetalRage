#include "SandSmoke.h"
#include "Object.h"

void SandSmoke::Init()
{
	for (int i = 0; i < MAX_SAND_SMOKE; i++)
	{
		m_SmokeStatus[i].bExist = false;
		m_SmokeStatus[i].bill.Start();
		m_SmokeStatus[i].bill.SetTexKind(SMOKE);
		//m_SmokeStatus[i].SetSplit(Float2(7, 7));
		m_SmokeStatus[i].bill.SetScale(0.2f);
		m_SmokeStatus[i].bill.SetColor(Float4(1, 0.5f, 0.1f, 0.8f));
	}
	m_AddScale = 0;
}

void SandSmoke::Uninit()
{
	for (int i = 0; i < MAX_SAND_SMOKE; i++)
		m_SmokeStatus[i].bill.Uninit();
}

void SandSmoke::Update()
{
	if (m_SmokeStatus[0].bExist && m_AddScale.x < 2.f)
	{
		m_AddScale.x += 0.05f;
		m_AddScale.y += 0.05f;
		m_AddScale.z += 0.05f;
	}
	for (int i = 0; i < MAX_SAND_SMOKE; i++)
	{
		if (!m_SmokeStatus[i].bExist) continue;
		m_SmokeStatus[i].bill.SetScale(m_AddScale);
		//m_SmokeStatus[i].bill.SetAlpha(0.2f-m_AddScale.x*0.1f);
		m_SmokeStatus[i].bill.SetColor(Float4(
			1 - m_AddScale.x * 0.1f,
			1 - m_AddScale.y * 0.1f,
			1 - m_AddScale.z * 0.1f,
			0.8f - m_AddScale.x * 0.1f));
		Float3 TempTranslate = m_SmokeStatus[i].bill.GetTranslate();
		TempTranslate += m_SmokeStatus[i].move;
		m_SmokeStatus[i].bill.SetTranslate(TempTranslate);
		m_SmokeStatus[i].bill.Update();
	}
}

void SandSmoke::Draw()
{
	for (int i = 0; i < MAX_SAND_SMOKE; i++)
	{
		//if (m_SmokeStatus[i].GetState() != ANIME::PLAY) continue;
		EnableZBuffer(false);
		m_SmokeStatus[i].bill.Draw();
		EnableZBuffer(true);
	}
}
void SandSmoke::Set(Float3 Translate)
{
	for (int i = 0; i < MAX_SAND_SMOKE; i++)
	{
		m_SmokeStatus[i].bExist = true;
		m_SmokeStatus[i].move = Float3(
			(rand() % 5 + 1) * 0.0001f,
			(rand() % 5 + 1) * 0.0001f,
			(rand() % 5 + 1) * 0.0001f);
		//m_SmokeStatus[i].bill.SetScale((rand() % 9 + 1) * 0.5f);
		Float3 newTranslate = Float3(Translate.x, Translate.y - 1, Translate.z);
		m_SmokeStatus[i].bill.SetTranslate(newTranslate);
	}
	m_AddScale = 0;
}
