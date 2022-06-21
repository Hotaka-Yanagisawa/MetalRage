#include "GameState.h"
#include "ResultScene.h"
#include "SelectScene.h"
#include "../Shader.h"
#include "../Camera.h"
#include "../Player.h"
#include "../Collision.h"
#include "../Object.h"
#include "../Enemy.h"
#include "../Collider.h"
#include "../HP.h"
#include "../Billboard.h"
#include "../ParallelProjection.h"
#include "../Scene.h"
#include "../Input.h"
#include "../ObjectMgr.h"
#include "../DirectX.h"
#include "../Defines.h"
#include "../Fade.h"
#include "../Controller.h"
#include "../Explosion.h"
#include "../GlassSmoke.h"

#define NEXT_CNT (180.0f)
//Trajectory *g_Trajectory;

void GameState::Init(Scene *obj)
{
	//フェード
	FADE->Init();
	FADE->FadeStart(FADEIN);
	FADE->SetFadeSpd(60.0f);

	//エフェクト初期化
	Explosion::GetInstance()->Init();

	////カメラクラスの実体化
	obj->m_pCamera = new Camera();
	obj->m_pCamera->Init();
	obj->m_pCamera2P = new Camera();
	obj->m_pCamera2P->m_ConNum = 1;
	obj->m_pCamera2P->Init();

	//当たり判定クラス
	obj->m_pCollision = new Collision();
	obj->m_pCollision->Init();

	//**********************************************************
	//作られたオブジェクトの順番にDrawなどの処理が行われる
	//そのため2DのUIをDrawするプレイヤーは最後にクリエイトしよう
	//**********************************************************
	//---オブジェクトの作成
	//壁床の生成
													//場所→大きさ
	//前後左右の壁
	ObjectMgr::GetInstance()->CreateField(Float3(50, 25, 0), Float3(0.1, 50, 100), Figure::WALL);
	ObjectMgr::GetInstance()->CreateField(Float3(-50, 25, 0), Float3(0.1, 50, 100), Figure::WALL);
	ObjectMgr::GetInstance()->CreateField(Float3(0, 25, 50), Float3(100, 50, 0.1), Figure::WALL);
	ObjectMgr::GetInstance()->CreateField(Float3(0, 25, -50), Float3(100, 50, 0.1), Figure::WALL);
	//床
	ObjectMgr::GetInstance()->CreateField(Float3(0, -1, 0), Float3(100, 2, 100), Figure::WALL,true);
	if (obj->m_Stage == GAME::ONE)
	{
		//箱
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 7; j++)
			{
			ObjectMgr::GetInstance()->CreateField(
				Float3(-45 + j * 15, 4, -45 + i * 15),
				Float3(3, 8, 3),
				Figure::BRICK, true);
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
	//プレイヤーの生成
	Object *object;
	object = ObjectMgr::GetInstance()->CreatePlayer(Float3(0,1,-35),Float3(2));
	obj->m_pCamera->SetTarget(object->GetTransform());
	obj->m_pCamera->m_ConNum = 0;
	object->GetComponent<Player>()->m_pCamera = obj->m_pCamera;
	//軌跡
	
	//プレイヤー2の生成
	object = ObjectMgr::GetInstance()->CreatePlayer(Float3(0, 1, 35), Float3(2),1);
	obj->m_pCamera2P->SetTarget(object->GetTransform());
	object->GetComponent<Player>()->m_pCamera = obj->m_pCamera2P;
	//ウィンドサイズの再設定
	obj->m_pCamera->m_ScreenWidth = (float)SCREEN_WIDTH / 2;
	obj->m_pCamera2P->m_ScreenWidth = (float)SCREEN_WIDTH / 2;
	
	for (auto obj : OBJ_LIST) obj->Update();

	m_nDrawNum = 0;
	m_bNext = false;
	m_NextCnt = NEXT_CNT;
	m_nWinner = 0;
}

void GameState::Uninit(Scene * obj)
{
	m_nDrawNum = 0;
	delete obj->m_pCamera;
	delete obj->m_pCamera2P;
	Explosion::GetInstance()->Uninit();
	ObjectMgr::GetInstance()->AllDeleteObject();
}

void GameState::Update(Scene *obj, HierarchySceneState * parent)
{
	m_Voice.Update();
	obj->m_pCamera->Update();
	obj->m_pCamera2P->Update();

	for (auto it = OBJ_LIST.begin(); it != OBJ_LIST.end(); )
	{
		if (!(*it)->GetUse())
		{
			Object *temp = *it;
			++it;
			delete temp;
			continue;
		}
		++it;
	}


	if (FADE->Update())
	{
		for (auto obj : OBJ_LIST) obj->Update();

		if (IsKeyTrigger(VK_RETURN) || PAD->IsButtonsTrigger(XINPUT_GAMEPAD_BACK))
		{
			FADE->FadeStart(FADEOUT);
			FADE->SetFadeSpd(NEXT_CNT);
			m_bNext = true;
		}
		if (Player::Num < 2 && m_NextCnt == NEXT_CNT)
		{
			FADE->FadeStart(FADEOUT);
			FADE->SetFadeSpd(NEXT_CNT);
			m_bNext = true;
		}
	}
	obj->m_pCollision->Update();
	Explosion::GetInstance()->Update();
	//g_Trajectory->Update();

	if (m_bNext)
	{
		--m_NextCnt;
		if (m_NextCnt == 150)
		{
			if (m_nWinner == 0)
			{
				//サウンド
				m_Voice.m_pBuffer = m_Voice.CreateSound("Assets/Sound/SE/voice_2_1.wav", false);
				m_Voice.m_pSpeaker = m_Voice.PlaySound(m_Voice.m_pBuffer);
				m_Voice.m_pSpeaker->SetVolume(0.0f);
				m_Voice.m_bFade = false;
				m_Voice.m_bFade = m_Voice.Fade(0.5f, 0.1f);
			}
			else
			{
				//サウンド
				m_Voice.m_pBuffer = m_Voice.CreateSound("Assets/Sound/SE/voice_2_2.wav", false);
				m_Voice.m_pSpeaker = m_Voice.PlaySound(m_Voice.m_pBuffer);
				m_Voice.m_pSpeaker->SetVolume(0.0f);
				m_Voice.m_bFade = false;
				m_Voice.m_bFade = m_Voice.Fade(0.5f, 0.1f);
			}
		}
		if (m_NextCnt <= 0)
		{
			m_bNext = false;
			obj->SetHierarchyState(SelectScene::GetInstance());
		}
	}
}

void GameState::Draw(Scene *obj, HierarchySceneState *parent)
{
	for (m_nDrawNum = 0; m_nDrawNum < 2; m_nDrawNum++)
	{
		SHADER->Bind(VS_WORLD, PS_PHONG);
		GetContext()->RSSetViewports(1, &GetVp(m_nDrawNum));

		//3Dの描画設定
		if (m_nDrawNum != 1)obj->m_pCamera->Bind();
		else obj->m_pCamera2P->Bind();

		for (auto list : OBJ_LIST)	list->Draw();

		GlassSmoke::GetInstance()->Draw();

		Explosion::GetInstance()->Draw();
		//EnableCulling(false);
		//g_Trajectory->Draw();
		//EnableCulling(true);
		
		FADE->Draw();
		SHADER->SetTexture(NULL);
	}
}
