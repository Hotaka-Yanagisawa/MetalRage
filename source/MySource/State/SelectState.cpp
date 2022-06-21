#include "SelectState.h"
#include "GameScene.h"
#include "TutorialScene.h"
#include "TitleScene.h"
#include "../Object.h"
#include "../Scene.h"
#include "../Input.h"
#include "../Camera.h"
#include "../Shader.h"
#include "../Fade.h"
#include "../Defines.h"
#include "../Controller.h"

void SelectState::Init(Scene *obj)
{
	//ビューポートの設定
	GetContext()->RSSetViewports(1, &GetVp(2));
	//平行投影ポリゴン
	SelectInit();
	CharaInit();
	//フェード
	FADE->Init();
	FADE->FadeStart(FADEIN);
	FADE->SetFadeSpd(60.0f);
	FADE->Update();
	////カメラクラスの実体化
	obj->m_pCamera = new Camera();
	obj->m_pCamera->Init();
	obj->m_pCamera->Bind2D();
	obj->m_pCamera->Update();
	obj->m_pCamera2P = nullptr;
	//サウンド
	m_Sound.m_pBuffer = m_Sound.CreateSound("Assets/Sound/BGM/bgm_2.mp3", true);
	m_Sound.m_pSpeaker = m_Sound.PlaySound(m_Sound.m_pBuffer);
	m_Sound.m_pSpeaker->SetVolume(0.0f);
	m_Sound.m_bFade = false;
	m_Sound.m_bFade = m_Sound.Fade(0.3f, 2.f);

	m_SE.m_pBuffer = m_SE.CreateSound("Assets/Sound/SE/se_7.mp3", false);
	m_SE.m_pSpeaker = m_SE.PlaySound(m_SE.m_pBuffer);
	m_SE.m_pSpeaker->SetVolume(0.0f);
	m_SE.m_bFade = false;
	m_SE.m_bFade = m_SE.Fade(0.0f, 0.1f);

	//PushB
	m_Push.Start();
	m_Push.SetScale(Float3(200, 50, 0));
	m_Push.SetTranslate(Float3(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 200, 0));
	m_Push.SetColor(Float4(1, 1, 1, 1.0f));
	m_Push.SetTexKind(BB);
	m_Push.Update();
	m_bAlpha = false;
	m_fAlphaCnt = 10;

	obj->m_Stage = GAME::NO;
	

	m_SelectNum = 0;
	m_nNextCnt = 60;
	m_bNext = false;
}

void SelectState::Uninit(Scene * obj)
{
	m_Push.Uninit();

	XAUDIO2_VOICE_STATE state;
	//ソースボイスの状況を取得
	m_Sound.m_pSpeaker->GetState(&state);
	//なってる音が一つ以上ならストップ
	if (state.BuffersQueued > 0)
	{
		m_Sound.m_pSpeaker->Stop();
	}
	delete obj->m_pCamera;
	//delete obj->m_pPolygon;
	FADE->Uninit();
}

void SelectState::Update(Scene *obj, HierarchySceneState *parent)
{
	//Cnt終了でNextSceneへ
	if (m_bNext)			m_nNextCnt--;
	if (m_nNextCnt < 1)
	{
		m_nNextCnt = 60;
		m_bNext = false;
		NextScene(obj);
	}

	if (FADE->Update())
	{
		if (IsKeyTrigger(VK_RETURN) || PAD->IsButtonsTrigger(XINPUT_GAMEPAD_B))
		{
			FADE->FadeStart(FADEOUT);
			FADE->SetFadeSpd(60.0f);
			m_bNext = true;
			m_Sound.m_bFade = m_Sound.Fade(0.0f, 0.1f);

			m_SE.m_pBuffer = m_SE.CreateSound("Assets/Sound/SE/Decision.mp3", false);
			m_SE.m_pSpeaker = m_SE.PlaySound(m_SE.m_pBuffer);
			m_SE.m_pSpeaker->SetVolume(0.0f);
			m_SE.m_bFade = false;
			m_SE.m_bFade = m_SE.Fade(1.0f, 0.1f);
		}
		else if (IsKeyTrigger(VK_RIGHT) || PAD->IsButtonsTrigger(XINPUT_GAMEPAD_DPAD_RIGHT))
		{
			m_SE.m_pSpeaker = m_SE.PlaySound(m_SE.m_pBuffer);
			m_SE.m_pSpeaker->SetVolume(0.0f);
			m_SE.m_bFade = false;
			m_SE.m_bFade = m_SE.Fade(1.0f, 0.1f);
			m_SelectNum++;
		}
		else if (IsKeyTrigger(VK_LEFT) || PAD->IsButtonsTrigger(XINPUT_GAMEPAD_DPAD_LEFT))
		{
			m_SE.m_pSpeaker = m_SE.PlaySound(m_SE.m_pBuffer);
			m_SE.m_pSpeaker->SetVolume(0.0f);
			m_SE.m_bFade = false;
			m_SE.m_bFade = m_SE.Fade(1.0f, 0.1f);
			m_SelectNum--;
		}
		if (m_SelectNum < 0)		m_SelectNum = 3;
		if (m_SelectNum > 3)		m_SelectNum = 0;
	}

	if (PAD->IsLTriggerTrigger())	obj->m_Stage = GAME::ONE;
	if (PAD->IsRTriggerTrigger())	obj->m_Stage = GAME::TWO;


	//サウンドの更新Fadeが呼ばれたら機能する
	m_Sound.Update();
	m_SE.Update();
	//ポリゴンの更新
	SelectUpdate();
	CharaUpdate();
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
	//カメラの更新
	obj->m_pCamera->Update();
}

void SelectState::Draw(Scene *obj, HierarchySceneState * parent)
{
	for (int i = 0; i < 2; i++)	m_SelectPoly[i].Draw();
	for (int i = 0; i < 4; i++)	m_CharaPoly[i].Draw();
	m_Push.Draw();
	FADE->Draw();
}

void SelectState::SelectInit()
{
	for (int i = 0; i < 2; i++)
	{
		m_SelectPoly[i].Start();
		m_SelectPoly[i].SetTexKind(NULL_TEX);
		m_SelectPoly[i].SetScale(Float3(150, 40, 0));
		m_SelectPoly[i].SetTranslate(Float3(100, SCREEN_HEIGHT / 2 + 25, 0));
		if (i != 0)		m_SelectPoly[i].SetColor(Float4(1, 0.4, 0.2, 0.6));
		else  m_SelectPoly[i].SetColor(Float4(1, 0.1, 0.1, 0.6));
	}
}

void SelectState::SelectUpdate()
{
	static int Cnt;
	Cnt++;
	if (Cnt > 6)
	{
		for (int i = 0; i < 2; i++)
		{
			ParallelProjection::Vertex *Vertex = m_SelectPoly[i].GetVertex();
			Cnt = 0;

			float Correction = 0.02;
			if (i != 0)
			{
				Vertex[0].pos.x = -0.2 + ((rand() % 4) * Correction);
				Vertex[1].pos.x = 0.8 + ((rand() % 4) * Correction);
				Vertex[2].pos.x = 0 + ((rand() % 4) * Correction);
				Vertex[3].pos.x = 1 + ((rand() % 4) * Correction);

				Vertex[0].pos.y = 0 + ((rand() % 4) * Correction);
				Vertex[1].pos.y = -1 + ((rand() % 4) * Correction);
				Vertex[2].pos.y = 1.2 + ((rand() % 4) * Correction);
				Vertex[3].pos.y = 0.4 + ((rand() % 4) * Correction);
			}
			else
			{
				Vertex[0].pos.x = -0.1 + ((rand() % 4) * Correction);
				Vertex[1].pos.x = 1.2 + ((rand() % 4) * Correction);
				Vertex[2].pos.x = -0.2 + ((rand() % 4) * Correction);
				Vertex[3].pos.x = 1.3 + ((rand() % 4) * Correction);

				Vertex[0].pos.y = -0.8 + ((rand() % 4) * Correction);
				Vertex[1].pos.y = -0.65 + ((rand() % 4) * Correction);
				Vertex[2].pos.y = 0.95 + ((rand() % 4) * Correction);
				Vertex[3].pos.y = 0.4 + ((rand() % 4) * Correction);
			}
		}
	}
	for (int i = 0; i < 2; i++)
	{
		m_SelectPoly[i].SetTranslate(Float3(100 + m_fInterval * m_SelectNum, SCREEN_HEIGHT / 2 + 25, 0));
		m_SelectPoly[i].Update();
	}
}

void SelectState::CharaInit()
{
	for (int i = 0; i < 4; i++)
	{
		m_CharaPoly[i].Start();
		m_CharaPoly[i].SetScale(Float3(200, 50, 0));
		m_CharaPoly[i].SetTranslate(Float3(100 + m_fInterval * i, SCREEN_HEIGHT / 2, 0));
		m_CharaPoly[i].SetTexKind((Texture_Kind)(TITLE+i));
	}
}

void SelectState::CharaUpdate()
{
	for (int i = 0; i < 4; i++)
	{
		m_CharaPoly[i].Update();
	}
}

void SelectState::NextScene(Scene *obj)
{
	switch (m_SelectNum)
	{
	case 0:
		obj->SetHierarchyState(TitleScene::GetInstance());
		break;

	case 1:
		obj->m_Mode = GAME::PVP;
		if (obj->m_Stage == GAME::NO)
		{
			int num = rand() % 2;
			if (num == 0)
			{
				obj->m_Stage = GAME::ONE;
			}
			else
			{
				obj->m_Stage = GAME::TWO;
			}
		}
		obj->SetHierarchyState(GameScene::GetInstance());
		break;

	case 2:
		obj->m_Mode = GAME::PVE;
		obj->SetHierarchyState(GameScene::GetInstance());
		break;

	case 3:
		obj->SetHierarchyState(TutorialScene::GetInstance());
		break;
	}
}
