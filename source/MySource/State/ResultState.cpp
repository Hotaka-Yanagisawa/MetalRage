#include "ResultState.h"
#include "PvEState.h"
#include "SelectScene.h"
#include "../Object.h"
#include "../Scene.h"
#include "../Input.h"
#include "../Defines.h"
#include "../Camera.h"
#include "../DirectX.h"
#include "../Controller.h"
#include "../Fade.h"

void ResultState::Init(Scene *obj)
{
	//フェード
	FADE->Init();
	FADE->FadeStart(FADEIN);
	FADE->SetFadeSpd(61.0f);
	FADE->Update();
	////カメラクラスの実体化
	obj->m_pCamera = new Camera();
	obj->m_pCamera->Init();
	obj->m_pCamera2P = nullptr;
	obj->m_pCamera->Update();
	m_nNextCnt = 60;
	m_bNext = false;

	//倒した数のポリゴン
	for (int i = 0; i < 2; i++)
	{
		m_Number[i].Start();
		m_Number[i].SetTexKind(NUMBERS);
		m_Number[i].SetSplit(Float2(5, 2));
		m_Number[i].SetTexCoord(0);
		m_Number[i].SetScale(300);
		m_Number[i].SetTranslate(Float3(SCREEN_WIDTH / 2 + i * -180.0f - 70.0f, SCREEN_HEIGHT /2, 0));
	}
	//文字
	m_Poly.Start();
	m_Poly.SetTexKind(KILLS);
	m_Poly.SetScale(Float3(400,200,0));
	m_Poly.SetTranslate(Float3(SCREEN_WIDTH/2 - 200, SCREEN_HEIGHT / 2 - 200, 0));
	//PushB
	m_Push.Start();
	m_Push.SetScale(Float3(200, 50, 0));
	m_Push.SetTranslate(Float3(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 300, 0));
	m_Push.SetColor(Float4(1, 1, 1, 1.0f));
	m_Push.SetTexKind(BB);
	m_Push.Update();
	m_bAlpha = false;
	m_fAlphaCnt = 10;
}

void ResultState::Uninit(Scene * obj)
{
	FADE->Uninit();

	delete obj->m_pCamera;
}

void ResultState::Update(Scene *obj, HierarchySceneState * parent)
{
	int Hp = PvEState::GetInstance()->m_nKillsNum;
	int Digits = 0;
	while (Hp > 0)
	{
		int temp = Hp % 10;
		m_Number[Digits].SetTexCoord(Float2(temp % 5, temp / 5));

		++Digits;

		Hp /= 10;
	}
	
	if (Digits < 2) m_Number[1].SetTexCoord(Float2(0));

	for (int i = 0; i < 2; i++)	m_Number[i].Update();
	m_Poly.Update();
	obj->m_pCamera->Update();
	if (FADE->Update())
	{
		if (IsKeyTrigger(VK_RETURN) || PAD->IsButtonsTrigger(XINPUT_GAMEPAD_B))
		{
			m_bNext = true;
		}
	}

	if (m_bNext)
	{
		if (m_nNextCnt == 60)
		{
			FADE->FadeStart(FADEOUT);
			FADE->SetFadeSpd(60.0f);
		}
		m_nNextCnt--;
	}
	if (m_nNextCnt < 1)
	{
		m_bNext = false;
		obj->SetHierarchyState(SelectScene::GetInstance());
	}
	m_fAlphaCnt--;
	if (m_fAlphaCnt < 1)
	{
		m_bAlpha ^= true;
		m_fAlphaCnt = 10;
	}
	if (m_bAlpha) m_Push.SetAlpha(1);
	else
	{
		m_Push.SetAlpha(0.1f);
	}
	m_Push.Update();
}

void ResultState::Draw(Scene *obj, HierarchySceneState * parent)
{
	GetContext()->RSSetViewports(1, &GetVp(2));

	for (int i = 0; i < 2; i++)
		m_Number[i].Draw();
	m_Poly.Draw();
	m_Push.Draw();
	FADE->Draw();
}
