#include "PvEState.h"
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
#include "../Collider2D.h"
#include "../Controller.h"
#include "../Explosion.h"
#include "../GlassSmoke.h"

void PvEState::Init(Scene *obj)
{
	CntTimer = 0;
	NextTime = 30;
	m_bNext = false;
	m_NextCnt = 60;
	CreateEnemyTime = NextTime;
	m_nKillsNum = 0;

	Explosion::GetInstance()->Init();

	//敵を倒した数
	for (int i = 0; i < 2; i++)
	{
		m_Poly[i].Start();
		m_Poly[i].SetTexKind(NUMBERS);
		m_Poly[i].SetSplit(Float2(5, 2));
		m_Poly[i].SetScale(100);
		m_Poly[i].SetTranslate(Float3(SCREEN_WIDTH - 100 - i * 50, 75, 0));
	}

	//フェード
	FADE->Init();
	FADE->FadeStart(FADEIN);
	FADE->SetFadeSpd(60.0f);

	////カメラクラスの実体化
	obj->m_pCamera = new Camera();
	obj->m_pCamera->Init();

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
	//箱
	//ObjectMgr::GetInstance()->CreateField(Float3(0, 0, 0), Float3(10, 4, 10), true);
	//プレイヤーの生成
	object = ObjectMgr::GetInstance()->CreatePlayer(Float3(0, 2, -30), Float3(2));
	obj->m_pCamera->SetTarget(object->GetTransform());
	obj->m_pCamera->m_ConNum = 0;
	object->GetComponent<Player>()->m_pCamera = obj->m_pCamera;

	//敵の視野との当たり判定用
	object->AddComponent<Collider2D>();

	//敵の生成
	ObjectMgr::GetInstance()->CreateEnemy(Float3(0, 5.5f, 0), Float3(3), object->GetTransform());
	//ビューポートの設定
	GetContext()->RSSetViewports(1, &GetVp(2));
}

void PvEState::Uninit(Scene * obj)
{
	delete obj->m_pCamera;
	Explosion::GetInstance()->Uninit();
	for (int i = 0; i < 2; i++)	m_Poly[i].Uninit();
	ObjectMgr::GetInstance()->AllDeleteObject();
}

void PvEState::Update(Scene *obj, HierarchySceneState * parent)
{
	if(CntTimer < 310)		++CntTimer;
	if (CntTimer % 60 == 0)	NextTime -= 5;
	CreateEnemyTime -= 1.0f / 60.0f;
	if (CreateEnemyTime <= 0)
	{
		CreateEnemyTime = NextTime;
		if (Enemy::m_Num < 10)
		ObjectMgr::GetInstance()->CreateEnemy(Float3(rand() % 90 - 45, 5.5f, rand() % 90 - 45), Float3(3), object->GetTransform());
	}

	if (Enemy::m_Num == 0)
	{
		ObjectMgr::GetInstance()->CreateEnemy(Float3(rand() % 90 - 45, 5.5f, rand() % 90 - 45), Float3(3), object->GetTransform());
	}

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
		if (IsKeyTrigger(VK_RETURN) || PAD->IsButtonsTrigger(XINPUT_GAMEPAD_BACK) || Player::Num < 1)
		{
			FADE->FadeStart(FADEOUT);
			FADE->SetFadeSpd(60.0f);
			m_bNext = true;
		}
	}

	obj->m_pCollision->Update();
	Explosion::GetInstance()->Update();

	int KillNum = m_nKillsNum;
	int Digits = 0;
	while (KillNum > 0)
	{
		int temp = KillNum % 10;
		m_Poly[Digits].SetTexCoord(Float2(temp % 5, temp / 5));

		++Digits;

		KillNum /= 10;
	}
	
	if (Digits < 1) m_Poly[0].SetTexCoord(Float2(0));

	if (Digits < 2) m_Poly[1].SetTexCoord(Float2(0));

	for (int i = 0; i < 2; i++)	m_Poly[i].Update();
	
	if (m_bNext)
	{
		--m_NextCnt;
		if (m_NextCnt == 50)
		{
			//サウンド
			m_Voice.m_pBuffer = m_Voice.CreateSound("Assets/Sound/SE/voice_2_1.wav", false);
			m_Voice.m_pSpeaker = m_Voice.PlaySound(m_Voice.m_pBuffer);
			m_Voice.m_pSpeaker->SetVolume(0.0f);
			m_Voice.m_bFade = false;
			m_Voice.m_bFade = m_Voice.Fade(0.5f, 0.1f);
		}
		if (m_NextCnt <= 0)
		{
			obj->SetHierarchyState(ResultScene::GetInstance());
		}
	}
}

void PvEState::Draw(Scene *obj, HierarchySceneState *parent)
{
	SHADER->Bind(VS_WORLD, PS_PHONG);

	//3Dの描画設定
	obj->m_pCamera->Bind();
	for (auto list : OBJ_LIST)	list->Draw();
	
	GlassSmoke::GetInstance()->Draw();

	Explosion::GetInstance()->Draw();

	for (int i = 0; i < 2; i++)	m_Poly[i].Draw();

	FADE->Draw();
	SHADER->SetTexture(NULL);
}
