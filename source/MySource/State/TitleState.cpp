#include "TitleState.h"
#include "SelectScene.h"
#include "../Billboard.h"
#include "../Object.h"
#include "../Scene.h"
#include "../Input.h"
#include "../Camera.h"
#include "../Shader.h"
#include "../Defines.h"
#include "../Fade.h"
#include "../Controller.h"


void TitleState::Init(Scene *obj)
{
	//パーティクル	
	m_par.Init();
	//ビューポートの設定
	GetContext()->RSSetViewports(1, &GetVp(2));
	//カメラクラスの実体化
	obj->m_pCamera = new Camera();
	obj->m_pCamera->Init();
	obj->m_pCamera->Bind2D();
	obj->m_pCamera2P = nullptr;
	//タイトルロゴ
	m_Logo.Start();
	m_Logo.SetScale(Float3(800,250,0));
	m_Logo.SetTranslate(Float3(SCREEN_WIDTH / 2 -400, SCREEN_HEIGHT / 2 -200, 0));
	m_Logo.SetColor(Float4(1, 0, 0, 1));
	m_Logo.SetTexKind(LOGO);
	m_Logo.Update();
	//PushB
	m_Push.Start();
	m_Push.SetScale(Float3(200, 50, 0));
	m_Push.SetTranslate(Float3(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 200, 0));
	m_Push.SetColor(Float4(1, 1, 1, 1.0f));
	m_Push.SetTexKind(BB);
	m_Push.Update();
	m_bAlpha = false;
	m_fAlphaCnt = 10;
	//フェード
	FADE->Init();
	//サウンド
	m_Sound.m_pBuffer = m_Sound.CreateSound("Assets/Sound/BGM/bgm_1.mp3", true);
	m_Sound.m_pSpeaker = m_Sound.PlaySound(m_Sound.m_pBuffer);
	m_Sound.m_pSpeaker->SetVolume(0.0f);
	m_Sound.m_bFade = false;
	m_Sound.m_bFade = m_Sound.Fade(0.3f, 1.f);

	m_nNextCnt = 60;
	m_bNext = false;
}

void TitleState::Uninit(Scene * obj)
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
	m_Logo.Uninit();
	m_Push.Uninit();
}

void TitleState::Update(Scene *obj, HierarchySceneState * parent)
{
	m_par.Set(0);
	m_par.Update();
	//Fadeが呼ばれたら機能する
	m_Sound.Update();
	m_SE.Update();
	if (m_bNext)			m_nNextCnt--;
	if(m_nNextCnt < 1)		obj->SetHierarchyState(SelectScene::GetInstance());
	
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
	}
	obj->m_pCamera->Update();
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

void TitleState::Draw(Scene *obj, HierarchySceneState * parent)
{
	SHADER->Bind(VS_WORLD, PS_PHONG);

	m_par.Draw();
	m_Logo.Draw();
	m_Push.Draw();
	FADE->Draw();
}
