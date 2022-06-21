#include "Player.h"
#include "Input.h"
#include "Controller.h"
#include "Object.h"
#include "Bullet.h"
#include "Collider.h"
#include "Scene.h"
#include "Camera.h"
#include "Billboard.h"
#include "HP.h"
#include "Defines.h"
#include "State/PlayerMove.h"
#include "State/GameState.h"
#include "Fade.h"
#include "GlassSmoke.h"

int Player::Num;
ParallelProjection Player::m_Victory;

unsigned int g_DrawNum;

Player::Player()
{
	m_PlayerNum = 0;
	//MAX100ブースト1回で25消費、秒25回復
	m_BoostNum = MAX_BOOST;
	//現在のマガジン内の残弾数０になると自動リロードかな？
	m_MagazineNum = MAGAZINE_SIZE;
	//リロードまでにかかる時間２秒ぐらいでいいか
	m_ReloadTime = 0;
	//リロード中かどうかtrueがリロード中
	m_bReload = false;
	//弾の発射間隔0.5秒くらい？
	m_FireInterval = 0;
	//trueが発射硬直中
	m_bFire = false;
	m_State = PlayerMove::GetInstance();

	Num++;
	m_nHitCheckCnt = 0;
}

Player::~Player()
{
	Num--;

	XAUDIO2_VOICE_STATE state;
	//ソースボイスの状況を取得
	m_Sound.m_pSpeaker->GetState(&state);
	//なってる音が一つ以上ならストップ
	if (state.BuffersQueued > 0)
	{
		m_Sound.m_pSpeaker->Stop();
	}
	if (m_PlayerNum == 0)
	{
		GameState::GetInstance()->m_nWinner = 1;

		Scene::GetInstance()->m_pCamera->SetTarget(nullptr);
	}
	else
	{
		GameState::GetInstance()->m_nWinner = 0;

		Scene::GetInstance()->m_pCamera2P->SetTarget(nullptr);
	}
}

void Player::Start()
{
	g_DrawNum = 0;
	m_bMove = false;
	m_PlayerNum = 0;
	m_Parent->SetAcc(Float3(0.1f));
	GlassSmoke::GetInstance()->Init();
	//---UI
	//HPゲージ
	for (int i = 0; i < 10; i++)
	{
		m_HpGauge[i].Start();
		m_HpGauge[i].SetTexKind(NULL_TEX);
		//m_HpGauge[i].SetColor(Float4(0,1,1,1));
		ParallelProjection::Vertex *Vertex = m_HpGauge[i].GetVertex();
		for (int j = 0; j < 2; j++)
		{
			Vertex[j].pos.x = j + 1;
			//Vertex[j].pos.y += 1;
		}
		if (i > 4)
		{
			m_HpGauge[i].SetScale(50);
			m_HpGauge[i].SetTranslate(Float3(i * 51.0f - 125, SCREEN_HEIGHT -50, 0));
		}
		else
		{
			m_HpGauge[i].SetScale(25);
			m_HpGauge[i].SetTranslate(Float3(i * 26.0f, SCREEN_HEIGHT - 50+25, 0));
		}
	}
	//HP(数字)
	for (int i = 0; i < 3; i++)
	{
		m_HpPoly[i].Start();
		m_HpPoly[i].SetTexKind(NUMBERS);
		m_HpPoly[i].SetSplit(Float2(5, 2));
		m_HpPoly[i].SetScale(100);
		m_HpPoly[i].SetTranslate(Float3(i * -40.0f + 80,SCREEN_HEIGHT -100, 0));
	}
	//残弾数
	m_bulletsPoly.Start();
	m_bulletsPoly.SetTexKind(NUMBERS);
	m_bulletsPoly.SetSplit(Float2(5, 2));
	m_bulletsPoly.SetScale(100);
	m_bulletsPoly.SetTranslate(Float3(SCREEN_WIDTH - 100, SCREEN_HEIGHT - 75, 0));
	//照準
	for (int i = 0; i < 4; i++)
	{
		m_Aim[i].Start();
		m_Aim[i].SetTexKind(AIM);
		m_Aim[i].SetSplit(Float2(2, 2));
		m_Aim[i].SetScale(50);
		m_Aim[i].SetAlpha(0.3f);
		if(i < 2)
			m_Aim[i].SetTranslate(Float3(SCREEN_WIDTH / 2 + i * -40.0f , SCREEN_HEIGHT / 2 -150, 0));
		else
			m_Aim[i].SetTranslate(Float3(SCREEN_WIDTH / 2 + i * -40.0f +80, SCREEN_HEIGHT / 2 - 200, 0));

	}
	//照準
	m_Aim[0].SetTexCoord(Float2(1, 1));
	m_Aim[1].SetTexCoord(Float2(2, 1));
	m_Aim[2].SetTexCoord(Float2(1, 2));
	m_Aim[3].SetTexCoord(Float2(2, 2));
	//ブーストゲージ
	m_BoostGauge.Start();
	m_BoostGauge.SetTexKind(NULL_TEX);
	m_BoostGauge.SetColor(Float4(0, 1, 0, 1));
	m_BoostGauge.SetScale(Float3(400 * m_BoostNum * 0.01f,40,0));
	m_BoostGauge.SetTranslate(Float3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 40, 0));
	//勝利
	m_Victory.Start();
	m_Victory.SetTexKind(VICTORY);
	m_Victory.SetColor(Float4(1, 1, 0, 1));
	m_Victory.SetScale(Float3(SCREEN_WIDTH , SCREEN_HEIGHT, 0));
	m_Victory.SetTranslate(0);

	//サウンド
	m_Sound.m_pBuffer = m_Sound.CreateSound("Assets/Sound/SE/se_1.mp3");
	m_Sound.m_pSpeaker = m_Sound.PlaySound(m_Sound.m_pBuffer);
	m_Sound.m_pSpeaker->SetVolume(0.0f);
	m_Sound.m_bFade = false;
	m_Sound.m_bFade = m_Sound.Fade(0.0f, 0.1f);
	m_Sound.Update();
}

void Player::Uninit()
{
	GlassSmoke::GetInstance()->Uninit();
}

void Player::Update()
{
	//---共通処理
	CommonUpdate();

	m_State->Update(this);
	GlassSmoke::GetInstance()->Update();
	float y = m_CameraXzAngle * 3.141519f / 180.0f;
	m_Parent->SetRotate(Float3(0, 360 * 3.14f/180.0f - y, 0));
}

void Player::Draw()
{
	//対戦モード以外
	if (FADE->GetState() == WAIT)
	{
		if (Scene::GetInstance()->GetState() != GameState::GetInstance())
		{
			int Hp = m_Parent->GetComponent<HP>()->GetHp();
			int DrawNum;
			DrawNum = (Hp + 44) / 45;
			//GlassSmoke::GetInstance()->Draw();
			for (int i = 0; i < DrawNum; i++)	m_HpGauge[i].Draw();
			for (int i = 0; i < 3; i++)		m_HpPoly[i].Draw();
			m_bulletsPoly.Draw();

			for (int i = 0; i < 4; i++)		m_Aim[i].Draw();

			m_BoostGauge.Draw();
		}
		else
		{
			//（対戦モードのみ）1周の処理でDrawは4回呼ばれる(プレイヤー*2+画面分割数*2=4)
			//0回目はプレイヤー0番目のHP値を画面0番目の画面に描画
			//1回目はプレイヤー1番目のHP値を画面0番目の画面に描画
			//2回目はプレイヤー0番目のHP値を画面1番目の画面に描画
			//3回目はプレイヤー1番目のHP値を画面1番目の画面に描画
			//よって必要な0番目と3番目だけDrawする

			if (g_DrawNum % 4 == 0 || g_DrawNum % 4 == 3)
			{
				int Hp = m_Parent->GetComponent<HP>()->GetHp();
				int DrawNum;
				DrawNum = (Hp + 44) / 45;
				//GlassSmoke::GetInstance()->Draw();
				for (int i = 0; i < DrawNum; i++)	m_HpGauge[i].Draw();
				for (int i = 0; i < 3; i++)		m_HpPoly[i].Draw();
				m_bulletsPoly.Draw();
				
				for (int i = 0; i < 4; i++)		m_Aim[i].Draw();
				m_BoostGauge.Draw();

			}
		}
	++g_DrawNum;
	if (g_DrawNum > 3) g_DrawNum = 0;
	}
	if (FADE->GetState() == FADEOUT)
	{
		if (Num < 2)
		{
			if (Scene::GetInstance()->GetState() == GameState::GetInstance())
			{
				if (m_PlayerNum == 0)
				{
					if (g_DrawNum % 4 == 0 || g_DrawNum % 4 == 2)		m_Victory.Draw();
				}
				else
				{
					if (g_DrawNum % 4 == 1 || g_DrawNum % 4 == 3)		m_Victory.Draw();
				}
				++g_DrawNum;
				if (g_DrawNum > 3) g_DrawNum = 0;
			}
		}
	}
}

void Player::OnCollision(Object *obj)
{
	switch (obj->GetType())
	{
	case PLAYER:
		break;
	case ENEMY:
		break;
	case BULLET:
		break;
	case FIELD:
		break;
	case MAX:
		break;
	default:
		break;
	}
}

//弾生成(二発)
void Player::CreateBullet()
{
	//マガジン内が２以下なら処理を行わない
	if (m_MagazineNum < 2) return;
	//打つ分マガジン内から弾減らす
	m_MagazineNum -= 2;
	//マガジンが空になったら強制リロード
	if (m_MagazineNum <= 0 && !m_bReload)
	{
		Reload();
	}
	//発射間隔
	m_FireInterval = FIRE_INTERVAL;
	m_bFire = true;

	const float RAD = 3.141519f / 180.0f;
	Object *obj;
	for (int i = 0; i < 2; i++)
	{
		obj = new Object();
		obj->SetType(BULLET);
		obj->AddComponent<Bullet>()->SetCameraAngle(m_CameraXzAngle, m_CameraYAngle);
		obj->GetComponent<Bullet>()->SetLord(m_Parent);
		obj->GetComponent<Bullet>()->SetNum(i);
		obj->GetComponent<Bullet>()->SetAttack(30);
		obj->AddComponent<Collider>()->SetScale(0.2f);
		obj->AddComponent<Cube>();
		obj->GetComponent<Cube>()->SetScale(obj->GetScale());
		obj->GetComponent<Cube>()->SetTexNum(Figure::BRICK);
		obj->SetTranslate(m_Parent->GetTranslate());
		if (i == 0)
		{
			Float3 Add(cosf(m_CameraXzAngle * RAD) * 0.5f, 0, sinf(m_CameraXzAngle * RAD) *0.5f);
			obj->AddTranslate(Add);
		}
		else
		{
			Float3 Add(-cosf(m_CameraXzAngle * RAD) * 0.5f, 0, -sinf(m_CameraXzAngle * RAD) * 0.5f);
			obj->AddTranslate(Add);
		}
		obj->SetRotate(m_Parent->GetRotate());
	}

	//エフェクト
	GlassSmoke::GetInstance()->Set(m_Parent->GetTranslate());

	//サウンド
	m_Sound.m_pBuffer = m_Sound.CreateSound("Assets/Sound/SE/se_1.mp3");
	m_Sound.m_pSpeaker = m_Sound.PlaySound(m_Sound.m_pBuffer);
	m_Sound.m_pSpeaker->SetVolume(0.0f);
	m_Sound.m_bFade = false;
	m_Sound.m_bFade = m_Sound.Fade(0.7f, 0.1f);
	m_Sound.Update();
}

void Player::Boost()
{
	//ブーストゲージ残量が少ないと処理飛ばす
	if (m_BoostNum < BOOST_USAGE) return;
	if (m_Parent->GetAcc().x > 0.1f) return;
	if (!m_bMove) return;
	const float fAcc = 0.5f;
	m_BoostNum -= BOOST_USAGE;
	if (PAD->IsButtonsPress(XINPUT_GAMEPAD_DPAD_UP, m_PlayerNum) || PAD->IsLStickUp(m_PlayerNum))
	{
		m_Parent->SetAcc(fAcc);
	}
	//else if (IsKeyPress('S'))
	//{
	//	//m_Parent->GetTransform()->Move.x = -cosf((m_CameraXzAngle + 90) * RAD) * fAcc;
	//	//m_Parent->GetTransform()->Move.z = -sinf((m_CameraXzAngle + 90) * RAD) * fAcc;
	//}
	else if (PAD->IsButtonsPress(XINPUT_GAMEPAD_DPAD_RIGHT, m_PlayerNum) || PAD->IsLStickRight(m_PlayerNum))
	{
		m_Parent->SetAcc(fAcc);
	}
	else if (PAD->IsButtonsPress(XINPUT_GAMEPAD_DPAD_LEFT, m_PlayerNum) || PAD->IsLStickLeft(m_PlayerNum))
	{
		m_Parent->SetAcc(fAcc);
	}
//#ifndef DEB
	if (IsKeyPress('W'))
	{
		m_Parent->SetAcc(fAcc);
	}
	//else if (IsKeyPress('S'))
	//{
	//	//m_Parent->GetTransform()->Move.x = -cosf((m_CameraXzAngle + 90) * RAD) * fAcc;
	//	//m_Parent->GetTransform()->Move.z = -sinf((m_CameraXzAngle + 90) * RAD) * fAcc;
	//}
	else if (IsKeyPress('D'))
	{
		m_Parent->SetAcc(fAcc);
	}
	else if (IsKeyPress('A'))
	{
		m_Parent->SetAcc(fAcc);
	}
	//else if (!IsKeyPress('S'))
	//{
	//	m_Parent->SetAcc(0.5);
	//	//m_Parent->GetTransform()->Move.x = -cosf((m_CameraXzAngle + 90) * RAD) * fAcc;
	//	//m_Parent->GetTransform()->Move.z = -sinf((m_CameraXzAngle + 90) * RAD) * fAcc;
	//}
//#endif
		//サウンド
	m_Sound.m_pBuffer = m_Sound.CreateSound("Assets/Sound/SE/se_3.mp3");
	m_Sound.m_pSpeaker = m_Sound.PlaySound(m_Sound.m_pBuffer);
	m_Sound.m_pSpeaker->SetVolume(0.0f);
	m_Sound.m_bFade = false;
	m_Sound.m_bFade = m_Sound.Fade(1.0f, 0.1f);
	m_Sound.Update();
}

void Player::BoostUpdate()
{
	m_BoostNum += BOOST_RECOVERY / 60.0f;
	if (m_BoostNum > MAX_BOOST) m_BoostNum = MAX_BOOST;
}

void Player::Reload()
{
	if (m_MagazineNum >= MAGAZINE_SIZE) return;
	m_ReloadTime = RELOAD_TIME;
	m_bReload = true;
	//サウンド
	m_Sound.m_pBuffer = m_Sound.CreateSound("Assets/Sound/SE/se_2.mp3");
	m_Sound.m_pSpeaker = m_Sound.PlaySound(m_Sound.m_pBuffer);
	m_Sound.m_pSpeaker->SetVolume(0.0f);
	m_Sound.m_bFade = false;
	m_Sound.m_bFade = m_Sound.Fade(0.5f, 1.f);
	m_Sound.Update();

}

void Player::ReloadUpdate()
{
	if (m_bReload)
	{
		m_ReloadTime -= 1.0f / 60.0f;
		if (m_ReloadTime < 0)
		{
			m_ReloadTime = 0;

			m_MagazineNum = MAGAZINE_SIZE;
			m_bReload = false;
		}
	}
}

void Player::FireUpdate()
{
	if (m_bFire)
	{
		m_FireInterval -= 1.0f / 60.0f;
		if (m_FireInterval <= 0)
		{
		m_FireInterval = 0;
			m_bFire = false;
		}
	}
}

void Player::HpPolyUpdate()
{
	int Hp = m_Parent->GetComponent<HP>()->GetHp();
	int Digits = 0;
	while (Hp > 0)
	{
		int temp = Hp % 10;
		m_HpPoly[Digits].SetTexCoord(Float2(temp % 5, temp / 5));

		++Digits;

		Hp /= 10;
	}
	if (Digits < 3) m_HpPoly[2].SetTexCoord(Float2(0));
	if (Digits < 2) m_HpPoly[1].SetTexCoord(Float2(0));

	for (int i = 0; i < 3; i++)	m_HpPoly[i].Update();
}

void Player::CommonUpdate()
{
	//サウンド
	m_Sound.Update();
	//ブースト処理
	BoostUpdate();
	//リロードの処理
	ReloadUpdate();
	//発射硬直処理（発射間隔）
	FireUpdate();
	//ポリゴンの更新
	for (int i = 0; i < 10; i++)	m_HpGauge[i].Update();

	HpPolyUpdate();

	m_bulletsPoly.SetTexCoord(Float2(m_MagazineNum % 5, m_MagazineNum / 5));
	m_bulletsPoly.Update();
	if (m_nHitCheckCnt >= 0)
	{
		--m_nHitCheckCnt;
	}
	for (int i = 0; i < 4; i++)
	{
		int Add = 0;
		if (PAD->IsRTriggerPress(m_PlayerNum)) Add = -30;
		if (PAD->IsLTriggerPress(m_PlayerNum)) Add = 30;
		if (PAD->IsRTriggerPress(m_PlayerNum) && PAD->IsLTriggerPress(m_PlayerNum)) Add = 0;
		//下
		if (i < 2)
		{
			if (!m_bReload)
			{
				m_Aim[i].SetTranslate(Float3
				(SCREEN_WIDTH / 2 + i * -50.0f + Add,
					SCREEN_HEIGHT / 2 - 150,
					0));
			}
			else
			{
				m_Aim[i].SetTranslate(Float3
				(SCREEN_WIDTH / 2 + i * -100.0f + 25.0f + Add,
					SCREEN_HEIGHT / 2 - 100,
					0));
			}
		}
		//上
		else
		{
			if (!m_bReload)
			{
				m_Aim[i].SetTranslate(Float3
				(SCREEN_WIDTH / 2 + i * -50.0f + 100.0f + Add,
					SCREEN_HEIGHT / 2 - 200
					, 0));
			}
			else
			{
				m_Aim[i].SetTranslate(Float3
				(SCREEN_WIDTH / 2 + i * -100.0f + 225.0f + Add,
					SCREEN_HEIGHT / 2 - 250
					, 0));
			}
		}
		if (m_nHitCheckCnt >= 0)	m_Aim[i].SetColor(Float4(1, 0, 0, 0.5f));
		else                        m_Aim[i].SetColor(Float4(1, 1, 1, 0.5f));

		m_Aim[i].Update();
	}
	if (m_BoostNum < BOOST_USAGE)
	{
		m_BoostGauge.SetColor(Float4(1, 0, 0, 0.7f));
	}
	else
	{
		m_BoostGauge.SetColor(Float4(0,1,0,1));
	}
	m_BoostGauge.SetScale(Float3(400 * m_BoostNum * 0.01f, 40, 0));
	m_BoostGauge.Update();

	m_Victory.Update();

	m_Parent->SetMove(Float3(0, m_Parent->GetTransform()->Move.y, 0));
	m_Parent->GetTransform()->Move.y -= 0.01f;
	if (m_Parent->GetTransform()->Move.y < -1)	m_Parent->GetTransform()->Move.y = -1;

	//int Hp = m_Parent->GetComponent<HP>()->GetHp();
	//if (Hp < 1)
	//{
	//	if (m_PlayerNum == 0)
	//	{
	//		GameState::GetInstance()->m_nWinner = 1;
	//	}
	//	else
	//	{
	//		GameState::GetInstance()->m_nWinner = 0;
	//	}
	//}
}

void Player::MoveUpdate()
{
	const float RAD = 3.141519f / 180.0f;
	//const float Move = 5.0f / 60;
	if (m_PlayerNum == 0)
	{
		m_CameraXzAngle = Scene::GetInstance()->m_pCamera->GetXzAngle();
		m_CameraYAngle = Scene::GetInstance()->m_pCamera->GetYAngle();
	}
	else
	{
		m_CameraXzAngle = Scene::GetInstance()->m_pCamera2P->GetXzAngle();
		m_CameraYAngle = Scene::GetInstance()->m_pCamera2P->GetYAngle();
	}
	m_bMove = false;
	m_Parent->SetMove(Float3(0,m_Parent->GetMove().y, 0));
	if (PAD->IsLStickUp(m_PlayerNum))
	{
		m_Parent->GetTransform()->Move.x += cosf((m_CameraXzAngle + 90) * RAD) * m_Parent->GetAcc().x;
		m_Parent->GetTransform()->Move.z += sinf((m_CameraXzAngle + 90) * RAD) * m_Parent->GetAcc().z;
		m_bMove = true;
	}
	if (PAD->IsLStickDown(m_PlayerNum))
	{
		m_Parent->GetTransform()->Move.x += -cosf((m_CameraXzAngle + 90) * RAD) * m_Parent->GetAcc().x;
		m_Parent->GetTransform()->Move.z += -sinf((m_CameraXzAngle + 90) * RAD) * m_Parent->GetAcc().z;
		//m_bMove = true;
	}
	if (PAD->IsLStickRight(m_PlayerNum))
	{
		m_Parent->GetTransform()->Move.x += cosf(m_CameraXzAngle * RAD) * m_Parent->GetAcc().x;
		m_Parent->GetTransform()->Move.z += sinf(m_CameraXzAngle * RAD) * m_Parent->GetAcc().z;
		m_bMove = true;
	}
	if (PAD->IsLStickLeft(m_PlayerNum))
	{
		m_Parent->GetTransform()->Move.x += -cosf(m_CameraXzAngle * RAD) * m_Parent->GetAcc().x;
		m_Parent->GetTransform()->Move.z += -sinf(m_CameraXzAngle * RAD) * m_Parent->GetAcc().z;
		m_bMove = true;
	}
//#ifndef DEB
	if (m_PlayerNum == 0)
	{
		if (IsKeyPress('W'))
		{
			m_Parent->GetTransform()->Move.x = cosf((m_CameraXzAngle + 90) * RAD) * m_Parent->GetAcc().x;
			m_Parent->GetTransform()->Move.z = sinf((m_CameraXzAngle + 90) * RAD) * m_Parent->GetAcc().z;
			m_bMove = true;
		}
		else if (IsKeyPress('S'))
		{
			m_Parent->GetTransform()->Move.x = -cosf((m_CameraXzAngle + 90) * RAD) * m_Parent->GetAcc().x;
			m_Parent->GetTransform()->Move.z = -sinf((m_CameraXzAngle + 90) * RAD) * m_Parent->GetAcc().z;
			//m_bMove = true;
		}
		else if (IsKeyPress('D'))
		{
			m_Parent->GetTransform()->Move.x = cosf(m_CameraXzAngle * RAD) * m_Parent->GetAcc().x;
			m_Parent->GetTransform()->Move.z = sinf(m_CameraXzAngle * RAD) * m_Parent->GetAcc().z;
			m_bMove = true;
		}
		else if (IsKeyPress('A'))
		{
			m_Parent->GetTransform()->Move.x = -cosf(m_CameraXzAngle * RAD) * m_Parent->GetAcc().x;
			m_Parent->GetTransform()->Move.z = -sinf(m_CameraXzAngle * RAD) * m_Parent->GetAcc().z;
			m_bMove = true;
		}
	}
//#endif
	if (m_Parent->GetAcc().x > 0.1f) m_Parent->GetTransform()->Acc.x -= 0.01f;
	else m_Parent->GetTransform()->Acc.x = 0.1f;
	if (m_Parent->GetAcc().z > 0.1f) m_Parent->GetTransform()->Acc.z -= 0.01f;
	else m_Parent->GetTransform()->Acc.z = 0.1f;
}
