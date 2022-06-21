#include "GlassSmoke.h"
#include "Object.h"

//Boolフラグ増やす
//硝煙と砂煙の実装
//硝煙は弾を打ち終わった時に出る(ヴァンガード)
//ブースト出来たらいいね

//時間で硝煙消してない
//重なると枠が見える
//画像が悪い？

void GlassSmoke::Init()
{
	for (int i = 0; i < MAX_GLASS_SMOKE; i++)
	{
		m_SmokeStatus[i].bExist = false;
		m_SmokeStatus[i].bill.Start();
		m_SmokeStatus[i].bill.SetTexKind(SMOKE);
		//m_SmokeStatus[i].SetSplit(Float2(7, 7));
		m_SmokeStatus[i].bill.SetScale(0.2f);
		m_SmokeStatus[i].bill.SetAlpha(0.2f);
	}
	m_AddScale = 0;
}

void GlassSmoke::Uninit()
{
	for (int i = 0; i < MAX_GLASS_SMOKE; i++)
		m_SmokeStatus[i].bill.Uninit();
}

void GlassSmoke::Update()
{
	if (m_SmokeStatus[0].bExist && m_AddScale.x < 2.f)
	{
		m_AddScale.x += 0.05f;
		m_AddScale.y += 0.05f;
		m_AddScale.z += 0.05f;
	}
	for (int i = 0; i < MAX_GLASS_SMOKE; i++)
	{
		if (!m_SmokeStatus[i].bExist) continue;
		m_SmokeStatus[i].bill.SetScale(m_AddScale);
		//m_SmokeStatus[i].bill.SetAlpha(0.2f-m_AddScale.x*0.1f);
		m_SmokeStatus[i].bill.SetColor(Float4(
			1 - m_AddScale.x*0.1f,
			1 - m_AddScale.y*0.1f,
			1 - m_AddScale.z*0.1f,
			0.2f - m_AddScale.x*0.1f));
		Float3 TempTranslate = m_SmokeStatus[i].bill.GetTranslate();
		TempTranslate += m_SmokeStatus[i].move;
		m_SmokeStatus[i].bill.SetTranslate(TempTranslate);
		m_SmokeStatus[i].bill.Update();
	}
}

void GlassSmoke::Draw()
{
	for (int i = 0; i < MAX_GLASS_SMOKE; i++)
	{
		//if (m_SmokeStatus[i].GetState() != ANIME::PLAY) continue;
		EnableZBuffer(false);
		//m_SmokeStatus[i].bill.Draw();
		EnableZBuffer(true);
	}
}

void GlassSmoke::Set(Float3 Translate)
{
	for (int i = 0; i < MAX_GLASS_SMOKE; i++)
	{
		m_SmokeStatus[i].bExist = true;
		m_SmokeStatus[i].move = Float3(
			(rand() % 5 + 1) * 0.0001f,
			(rand() % 5 + 1) * 0.01f,
			(rand() % 5 + 1) * 0.0001f);
		//m_SmokeStatus[i].bill.SetScale((rand() % 9 + 1) * 0.5f);
		Float3 newTranslate = Float3(Translate.x, Translate.y + 1, Translate.z);
		m_SmokeStatus[i].bill.SetTranslate(newTranslate);
		break;
	}
	m_AddScale = 0;
}
