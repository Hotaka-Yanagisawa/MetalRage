#include "StartGameState.h"
#include "PvEState.h"
#include "GameState.h"
#include "../Object.h"
#include "../Scene.h"
#include "../Input.h"
#include "../Camera.h"
#include "../Fade.h"
#include "../Controller.h"
#include "../ObjectMgr.h"
#include "../Collision.h"
#include "../Player.h"
#include "../Shader.h"

void StartGameState::Init(Scene *obj)
{
	////カメラクラスの実体化
	obj->m_pCamera = new Camera();
	obj->m_pCamera->Init();
	obj->m_pCamera->SetRadius(30.0f);
	obj->m_pCamera2P = nullptr;

	//PushB
	m_Push.Start();
	m_Push.SetScale(Float3(200, 50, 0));
	m_Push.SetTranslate(Float3(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 200, 0));
	m_Push.SetColor(Float4(1, 1, 1, 1.0f));
	m_Push.SetTexKind(BB);
	m_Push.Update();


	obj->m_pCollision = new Collision();
	obj->m_pCollision->Init();

	//---オブジェクトの作成
	//壁床の生成
													//場所→大きさ
	//前後左右の壁
	ObjectMgr::GetInstance()->CreateField(Float3(50, 25, 0), Float3(0.1, 50, 100), Figure::WALL);
	ObjectMgr::GetInstance()->CreateField(Float3(-50, 25, 0), Float3(0.1, 50, 100), Figure::WALL);
	ObjectMgr::GetInstance()->CreateField(Float3(0, 25, 50), Float3(100, 50, 0.1), Figure::WALL);
	ObjectMgr::GetInstance()->CreateField(Float3(0, 25, -50), Float3(100, 50, 0.1), Figure::WALL);
	//床
	ObjectMgr::GetInstance()->CreateField(Float3(0, -1, 0), Float3(100, 2, 100), Figure::WALL, true);
	if (obj->m_Stage == GAME::ONE)
	{
		//箱
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				ObjectMgr::GetInstance()->CreateField(Float3(-45 + j * 15, 4, -45 + i * 15), Float3(3, 8, 3), Figure::BRICK, true);
			}
		}
	}
	if (obj->m_Stage == GAME::TWO)
	{
		ObjectMgr::GetInstance()->CreateField(Float3(0, 0, 0), Float3(10, 4, 10), Figure::WOOD, true);
		ObjectMgr::GetInstance()->CreateField(Float3(-4, 3, 0), Float3(2, 1, 2), Figure::WOOD, true);
		ObjectMgr::GetInstance()->CreateField(Float3(20, 0, -10), Float3(10, 4, 10), Figure::WOOD, true);
		ObjectMgr::GetInstance()->CreateField(Float3(20, 0, 10), Float3(10, 4, 10), Figure::WOOD, true);
		ObjectMgr::GetInstance()->CreateField(Float3(-25, 0, 0), Float3(5, 4, 70), Figure::WOOD, true);
		ObjectMgr::GetInstance()->CreateField(Float3(-22.5, 0, 0), Float3(30, 10, 2), Figure::WOOD, true);
	}

	//フェード
	FADE->Init();
	FADE->FadeStart(FADEIN);
	FADE->SetFadeSpd(60.0f);
	//サウンド
	m_Sound.m_pBuffer = m_Sound.CreateSound("Assets/Sound/BGM/bgm_4.mp3", true);
	m_Sound.m_pSpeaker = m_Sound.PlaySound(m_Sound.m_pBuffer);
	m_Sound.m_pSpeaker->SetVolume(0.0f);
	m_Sound.m_bFade = false;
	m_Sound.m_bFade = m_Sound.Fade(0.1f, 1.f);

	m_nNextCnt = 60;
	m_bNext = false;
	m_bAlpha = false;
	m_fAlphaCnt = 10;
}

void StartGameState::Uninit(Scene * obj)
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
	ObjectMgr::GetInstance()->AllDeleteObject();
}

void StartGameState::Update(Scene *obj, HierarchySceneState * parent)
{
	//Fadeが呼ばれたら機能する
	m_Sound.Update();
	if (m_bNext)			m_nNextCnt--;
	if (m_nNextCnt < 1)
	{
		switch (obj->m_Mode)
		{
		case GAME::PVP:
			obj->Uninit();
			parent->ChangeState(obj, GameState::GetInstance());
			break;
		case GAME::PVE:
			obj->Uninit();
			parent->ChangeState(obj, PvEState::GetInstance());
			break;
		default:
			break;
		}
	}
	if (FADE->Update())
	{
		for (auto obj : OBJ_LIST) obj->Update();

		if (IsKeyTrigger(VK_RETURN) || PAD->IsButtonsTrigger(XINPUT_GAMEPAD_B))
		{
			FADE->FadeStart(FADEOUT);
			FADE->SetFadeSpd(60.0f);
			m_bNext = true;
			m_Sound.m_bFade = m_Sound.Fade(0.0f, 0.1f);
		}
	}
	obj->m_pCollision->Update();

	obj->m_pCamera->Update();

	if(obj->m_pCamera->GetYAngle() <= 5.0f)
		obj->m_pCamera->SetYAngle(5.0f);

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

void StartGameState::Draw(Scene *obj, HierarchySceneState * parent)
{
	SHADER->Bind(VS_WORLD, PS_PHONG);

	//3Dの描画設定
	obj->m_pCamera->Bind();
	for (auto list : OBJ_LIST)	list->Draw();

	m_Push.Draw();
	FADE->Draw();
}
