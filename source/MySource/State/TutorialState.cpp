#include "TutorialState.h"
#include "SelectScene.h"
#include "../Object.h"
#include "../Scene.h"
#include "../Input.h"
#include "../Camera.h"
#include "../Fade.h"
#include "../Defines.h"
#include "../ObjectMgr.h"
#include "../Controller.h"
#include "../Collision.h"
#include "../Shader.h"
#include "../Collider2D.h"
#include "../Enemy.h"
#include "../Player.h"
#include "../Explosion.h"


void TutorialState::Init(Scene *obj)
{
	////カメラクラスの実体化
	obj->m_pCamera = new Camera();
	obj->m_pCamera->Init();
	obj->m_pCamera2P = nullptr;

	//フェード
	FADE->Init();
	FADE->FadeStart(FADEIN);
	FADE->SetFadeSpd(60.0f);

	m_nNextCnt = 180;
	m_bNext = false;
	m_bEnd = false;

	Explosion::GetInstance()->Init();


	for (int i = 0; i < 7; i++)
	{
		m_Poly[i].Start();
		m_Poly[i].SetTranslate(Float3(SCREEN_WIDTH - 200, i * 50, 0));
		m_Poly[i].SetScale(Float3(200, 50, 0));
		m_bClear[i] = false;
	}
	m_Poly[7].Start();
	m_Poly[7].SetTranslate(Float3(SCREEN_WIDTH / 2 -100, 25, 0));
	m_Poly[7].SetScale(Float3(200, 50, 0));
	m_Poly[7].SetColor(Float4(1, 0, 0, 1));
	m_bClear[7] = false;
	m_bCreate = false;

	//当たり判定クラス
	obj->m_pCollision = new Collision();
	obj->m_pCollision->Init();

	//---オブジェクトの作成
	//壁床の生成
													//場所→大きさ
	//前後左右の壁
	ObjectMgr::GetInstance()->CreateField(Float3(50, 25, 0), Float3(0.1, 50, 100), Figure::WALL);//右
	ObjectMgr::GetInstance()->CreateField(Float3(-50, 25, 0), Float3(0.1, 50, 100), Figure::WALL);//左
	ObjectMgr::GetInstance()->CreateField(Float3(0, 25, 50), Float3(100, 50, 0.1), Figure::WALL);//前
	ObjectMgr::GetInstance()->CreateField(Float3(0, 25, -50), Float3(100, 50, 0.1), Figure::WALL);//後ろ
	//床
	ObjectMgr::GetInstance()->CreateField(Float3(0, -1, 0), Float3(100, 2, 100), Figure::WALL, true);

	//プレイヤーの生成
	object = ObjectMgr::GetInstance()->CreatePlayer(Float3(0, 2, -30), Float3(2));
	obj->m_pCamera->SetTarget(object->GetTransform());
	obj->m_pCamera->m_ConNum = 0;
	object->GetComponent<Player>()->m_pCamera = obj->m_pCamera;
	//敵の視野との当たり判定用
	object->AddComponent<Collider2D>();

	//サウンド
	m_Sound.m_pBuffer = m_Sound.CreateSound("Assets/Sound/SE/se_5.mp3", false);
	m_Voice.m_pBuffer = m_Voice.CreateSound("Assets/Sound/SE/voice_1.wav", false);
}

void TutorialState::Uninit(Scene * obj)
{
	FADE->Uninit();
	Explosion::GetInstance()->Uninit();

	delete obj->m_pCamera;
	ObjectMgr::GetInstance()->AllDeleteObject();
}

void TutorialState::Update(Scene *obj, HierarchySceneState * parent)
{
	m_Sound.Update();
	m_Voice.Update();
	if (m_bNext && !m_bCreate)
	{
		m_bCreate = true;
		ObjectMgr::GetInstance()->CreateEnemy(Float3(0, 2, 0), Float3(2),object->GetTransform());
		m_Sound.m_pBuffer = m_Sound.CreateSound("Assets/Sound/SE/se_6.wav", false);
		m_Sound.m_pSpeaker = m_Sound.PlaySound(m_Sound.m_pBuffer);
		m_Sound.m_pSpeaker->SetVolume(0.0f);
		m_Sound.m_bFade = false;
		m_Sound.m_bFade = m_Sound.Fade(2.0f, 1.f);
	}
	if (m_bNext && Enemy::m_Num <= 0)
	{
		if (m_nNextCnt == 180)
		{
			m_Poly[7].SetColor(Float4(0, 0, 1, 1));
			FADE->FadeStart(FADEOUT);
			FADE->SetFadeSpd(180.0f);
		}
		m_nNextCnt--;
	}

	if (m_nNextCnt == 120)
	{
		if (!(Player::Num <= 0) && m_bNext)
		{
			m_Voice.m_pSpeaker = m_Voice.PlaySound(m_Voice.m_pBuffer);
			m_Voice.m_pSpeaker->SetVolume(0.0f);
			m_Voice.m_bFade = false;
			m_Voice.m_bFade = m_Voice.Fade(2.0f, 1.f);
		}
	}
	if (m_bEnd && !m_bNext)
	{
		if (m_nNextCnt == 180)
		{
			FADE->FadeStart(FADEOUT);
			FADE->SetFadeSpd(180.0f);
		}
		m_nNextCnt--;
	}
	if (m_nNextCnt < 1)
	{
		//m_nNextCnt = 180;
		m_bNext = false;
		m_bEnd = false;
		obj->SetHierarchyState(SelectScene::GetInstance());
	}

	//いくつチュートリアルclearしたか
	int ClearNum = 0;
	//クリアしたものの色は青に
	for (int i = 0; i < 7; i++)
	{
		if (m_bClear[i])
		{
			++ClearNum;
			m_Poly[i].SetColor(Float4(0, 0, 1, 1));
		}
		m_Poly[i].Update();
	}
	m_Poly[7].Update();

	obj->m_pCamera->Update();

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
		TutorialUpdate();
		//終了条件
		if (ClearNum >= 7 && !m_bNext)
		{
			m_bNext = true;
		}
		//強制終了
		if (IsKeyTrigger(VK_RETURN) || PAD->IsButtonsTrigger(XINPUT_GAMEPAD_BACK) && Enemy::m_Num <= 0)
		{
			FADE->FadeStart(FADEOUT);
			FADE->SetFadeSpd(60.0f);
			m_bCreate = true;
			//m_bNext = true;
			m_bEnd = true;
		}
	}
	obj->m_pCollision->Update();
	Explosion::GetInstance()->Update();

}

void TutorialState::Draw(Scene *obj, HierarchySceneState * parent)
{
	SHADER->Bind(VS_WORLD, PS_PHONG);

	//3Dの描画設定
	obj->m_pCamera->Bind();
	for (auto list : OBJ_LIST)	list->Draw();
	
	FADE->Draw();
	for (int i = 0; i < 7; i++)
	{
		switch (i)
		{
		case 0:
			m_Poly[i].SetTexKind(Texture_Kind::TUTORIAL1);
			break;
		case 1:
			m_Poly[i].SetTexKind(Texture_Kind::TUTORIAL2);
			break;
		case 2:
			m_Poly[i].SetTexKind(Texture_Kind::TUTORIAL3);
			break;
		case 3:
			m_Poly[i].SetTexKind(Texture_Kind::TUTORIAL4);
			break;
		case 4:
			m_Poly[i].SetTexKind(Texture_Kind::TUTORIAL5);
			break;
		case 5:
			m_Poly[i].SetTexKind(Texture_Kind::TUTORIAL6);
			break;
		case 6:
			m_Poly[i].SetTexKind(Texture_Kind::TUTORIAL7);
			break;
		}
		m_Poly[i].Draw();
	}
	if (m_bCreate && m_bNext)
	{
		m_Poly[7].SetTexKind(Texture_Kind::TUTORIAL8);
		m_Poly[7].Draw();
	}
	Explosion::GetInstance()->Draw();

	FADE->Draw();
	SHADER->SetTexture(NULL);

}

void TutorialState::TutorialUpdate()
{
	//1 移動
	if (!m_bClear[0])
	{
		if (PAD->IsLStickUp())		m_bClear[0] = true;
		if (PAD->IsLStickDown())	m_bClear[0] = true;
		if (PAD->IsLStickRight())	m_bClear[0] = true;
		if (PAD->IsLStickLeft())	m_bClear[0] = true;
		if (m_bClear[0])
		{
			m_Sound.m_pSpeaker = m_Sound.PlaySound(m_Sound.m_pBuffer);
			m_Sound.m_pSpeaker->SetVolume(0.0f);
			m_Sound.m_bFade = false;
			m_Sound.m_bFade = m_Sound.Fade(2.0f, 1.f);
		}
	}
	//2 視点移動
	if (!m_bClear[1])
	{
		if (PAD->IsRStickUp())		m_bClear[1] = true;
		if (PAD->IsRStickDown())	m_bClear[1] = true;
		if (PAD->IsRStickRight())	m_bClear[1] = true;
		if (PAD->IsRStickLeft())	m_bClear[1] = true;
		if (m_bClear[1])
		{
			m_Sound.m_pSpeaker = m_Sound.PlaySound(m_Sound.m_pBuffer);
			m_Sound.m_pSpeaker->SetVolume(0.0f);
			m_Sound.m_bFade = false;
			m_Sound.m_bFade = m_Sound.Fade(2.0f, 1.f);
		}
	}
	//3 ジャンプ
	if (!m_bClear[2])
	{
		if (PAD->IsButtonsTrigger(XINPUT_GAMEPAD_B))m_bClear[2] = true;
		if (m_bClear[2])
		{
			m_Sound.m_pSpeaker = m_Sound.PlaySound(m_Sound.m_pBuffer);
			m_Sound.m_pSpeaker->SetVolume(0.0f);
			m_Sound.m_bFade = false;
			m_Sound.m_bFade = m_Sound.Fade(2.0f, 1.f);
		}
	}
	//4 弾発射
	if (!m_bClear[3])
	{
		if (PAD->IsButtonsTrigger(XINPUT_GAMEPAD_RIGHT_SHOULDER))m_bClear[3] = true;
		if (m_bClear[3])
		{
			m_Sound.m_pSpeaker = m_Sound.PlaySound(m_Sound.m_pBuffer);
			m_Sound.m_pSpeaker->SetVolume(0.0f);
			m_Sound.m_bFade = false;
			m_Sound.m_bFade = m_Sound.Fade(2.0f, 1.f);
		}
	}
	//5 ブースト
	if (!m_bClear[4])
	{
		if (PAD->IsLStickUp()&& PAD->IsButtonsPress(XINPUT_GAMEPAD_LEFT_SHOULDER))
			m_bClear[4] = true;
		
		if (PAD->IsLStickRight() && PAD->IsButtonsPress(XINPUT_GAMEPAD_LEFT_SHOULDER))
			m_bClear[4] = true;
			
		if (PAD->IsLStickLeft() && PAD->IsButtonsPress(XINPUT_GAMEPAD_LEFT_SHOULDER))
			m_bClear[4] = true;

		if (m_bClear[4])
		{
			m_Sound.m_pSpeaker = m_Sound.PlaySound(m_Sound.m_pBuffer);
			m_Sound.m_pSpeaker->SetVolume(0.0f);
			m_Sound.m_bFade = false;
			m_Sound.m_bFade = m_Sound.Fade(2.0f, 1.f);
		}
	}
	//6 リーン
	if (!m_bClear[5])
	{
		if (PAD->IsLTriggerTrigger())	m_bClear[5] = true;
		if (PAD->IsRTriggerTrigger())	m_bClear[5] = true;
		if (m_bClear[5])
		{
			m_Sound.m_pSpeaker = m_Sound.PlaySound(m_Sound.m_pBuffer);
			m_Sound.m_pSpeaker->SetVolume(0.0f);
			m_Sound.m_bFade = false;
			m_Sound.m_bFade = m_Sound.Fade(2.0f, 1.f);
		}
	}
	//7 リロード
	if (!m_bClear[6])
	{
		if(PAD->IsButtonsTrigger(XINPUT_GAMEPAD_X))	m_bClear[6] = true;
		if (m_bClear[6])
		{
			m_Sound.m_pSpeaker = m_Sound.PlaySound(m_Sound.m_pBuffer);
			m_Sound.m_pSpeaker->SetVolume(0.0f);
			m_Sound.m_bFade = false;
			m_Sound.m_bFade = m_Sound.Fade(2.0f, 1.f);
		}
	}
}
