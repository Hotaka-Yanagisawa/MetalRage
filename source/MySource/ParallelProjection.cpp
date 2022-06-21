#include "ParallelProjection.h"
#include "Shader.h"
#include "Object.h"
#include "Camera.h"
#include "Scene.h"
#include "State/GameState.h"

ID3D11ShaderResourceView* ParallelProjection::m_pTex[MAX_KIND];

void ParallelProjection::Start()
{
	m_nTexKind = NULL_TEX;

	Vertex polyVtx[] = {
	{{0,0,0},{1,1,1,1}, {0,0}}, //左上
	{{1,0,0},{1,1,1,1}, {1,0}}, //右上
	{{0,1,0},{1,1,1,1}, {0,1}}, //左下
	{{1,1,0},{1,1,1,1}, {1,1}}, //右下
	};

	for (int i = 0; i < 4; i++)
	{
		m_polyVtx[i] = polyVtx[i];
	}

	m_Buffer.CreateVertexBuffer(m_polyVtx, sizeof(Vertex), _countof(m_polyVtx), true);

	m_Color = 1;
	m_Split = 1;
	m_TexCoord = 1;
	m_Translate = 0;
	m_Scale = 1;
	m_AnimeStart = 0;
	m_AnimeLast = 0;
	m_nCnt = 0;
	m_nAnimeSpd = 1;
	m_bLoop = false;
	ANIME::ANIME_STATE m_eState = ANIME::WAIT;
}

void ParallelProjection::Uninit()
{
}

void ParallelProjection::Update()
{
	//座標更新
	//m_polyVtx->pos = m_Translate;
	// アニメ更新
	if (m_eState == ANIME::PLAY)
	{
		//切り替え
		m_nCnt++;
		if (m_nCnt > m_nAnimeSpd)
		{
			//1周アニメーションが終わったら
			if ((m_TexCoord.x == m_AnimeLast.x) && (m_TexCoord.y == m_AnimeLast.y))
			{
				if (m_bLoop)			//ループする
				{
					m_TexCoord.x = m_AnimeStart.x;
					m_TexCoord.y = m_AnimeStart.y;
				}
				else m_eState = ANIME::END;	//ループしない
			}
			//次の分割画像へ
			else
			{
				// 次の座標
				m_TexCoord.x++;
				// 端までいった
				if (m_TexCoord.x >= m_Split.x)
				{
					m_TexCoord.x = 0.0f;
					m_TexCoord.y += 1.0f;
				}
				// 終端までいった
				if (m_TexCoord.y >= m_Split.y)	m_TexCoord.y = 0.0f;
			}
			// カウントリセット
			m_nCnt = 0;
		}
	}

	// UV座標反映
	float w = 1.0f / m_Split.x;
	float h = 1.0f / m_Split.y;
	float TexX = w * m_TexCoord.x;
	float TexY = h * m_TexCoord.y;
	m_polyVtx[0].uv = { TexX    , TexY };
	m_polyVtx[1].uv = { TexX + w, TexY };
	m_polyVtx[2].uv = { TexX    , TexY + h };
	m_polyVtx[3].uv = { TexX + w, TexY + h };
	// 色反映
	for (int i = 0; i < 4; i++)	m_polyVtx[i].color = m_Color;
}

void ParallelProjection::Draw()
{
	if (m_Parent != nullptr)
	{
		m_Translate = m_Parent->GetTranslate();
		m_Scale = m_Parent->GetScale();
	}

	SHADER->SetTexture(m_pTex[m_nTexKind]);

	//2D描画設定
	if (GameState::GetInstance()->m_nDrawNum == 0)
	{
		Scene::GetInstance()->m_pCamera->Bind2D();
	}
	else if (GameState::GetInstance()->m_nDrawNum == 1)
	{
		if (Scene::GetInstance()->m_pCamera2P != nullptr)
			Scene::GetInstance()->m_pCamera2P->Bind2D();
	}

	//GetCamera()->Bind2D();
	//2D表示でも3Dと考え方は同じで、
	//スクリーン上に表示するために、
	//変換行列で移動、拡縮を行う
	SHADER->SetWorld(
		//指定された幅、高さでポリゴンが表示
		//できるように、もとのポリゴンは幅１にしておく
		DirectX::XMMatrixScaling(m_Scale.x * 1,m_Scale.y * 1, 1) *
		DirectX::XMMatrixTranslation(m_Translate.x, m_Translate.y, 0)
	);
	//SHADER->SetLightAmbient(DirectX::XMFLOAT4(0.3f, 0.3f, 0.3f, 1.f));

	m_Buffer.Write(m_polyVtx);
	m_Buffer.Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	if (GameState::GetInstance()->m_nDrawNum == 0)
	{
		Scene::GetInstance()->m_pCamera->Bind();
	}
	else if (GameState::GetInstance()->m_nDrawNum == 1)
	{
		if (Scene::GetInstance()->m_pCamera2P != nullptr)
			Scene::GetInstance()->m_pCamera2P->Bind();
	}
	SHADER->SetTexture(m_pTex[NULL_TEX]);
}

void ParallelProjection::InitTexture()
{
	for (int i = 0; i < MAX_KIND; i++)
	{
		switch (i)
		{
		case NULL_TEX:
			m_pTex[i] = NULL;
			break;
		case NUMBERS:
			LoadTextureFromFile("Assets/Number.png", &m_pTex[i]);
			break;
		case EXPLOSION:
			//LoadTextureFromFile("Assets/Number.png", &m_pTex[i]);
			break;
		case FLASH:
			//LoadTextureFromFile("Assets/Number.png", &m_pTex[i]);
			break;
		case BOOSTGAUGE:
			LoadTextureFromFile("Assets/BoostBar.png", &m_pTex[i]);
			break;
		case AIM:
			LoadTextureFromFile("Assets/Aim2.png", &m_pTex[i]);
			break;
		case SMOKE:
			LoadTextureFromFile("Assets/Smoke.png", &m_pTex[i]);
			break;
		case TEX_BULLET:
			LoadTextureFromFile("Assets/abc.png", &m_pTex[i]);
			break;
		case TITLE:
			LoadTextureFromFile("Assets/title.png", &m_pTex[i]);
			break;	
		case PVP:
			LoadTextureFromFile("Assets/pvp.png", &m_pTex[i]);
			break;	
		case PVE:
			LoadTextureFromFile("Assets/pve.png", &m_pTex[i]);
			break;	
		case TUTORIAL:
			LoadTextureFromFile("Assets/tutorial.png", &m_pTex[i]);
			break;
		case TUTORIAL1:
			LoadTextureFromFile("Assets/Tutorial_1.png", &m_pTex[i]);
			break;
		case TUTORIAL2:
			LoadTextureFromFile("Assets/Tutorial_2.png", &m_pTex[i]);
			break;
		case TUTORIAL3:
			LoadTextureFromFile("Assets/Tutorial_3.png", &m_pTex[i]);
			break;
		case TUTORIAL4:
			LoadTextureFromFile("Assets/Tutorial_4.png", &m_pTex[i]);
			break;
		case TUTORIAL5:
			LoadTextureFromFile("Assets/Tutorial_5.png", &m_pTex[i]);
			break;
		case TUTORIAL6:
			LoadTextureFromFile("Assets/Tutorial_6.png", &m_pTex[i]);
			break;
		case TUTORIAL7:
			LoadTextureFromFile("Assets/Tutorial_7.png", &m_pTex[i]);
			break;
		case TUTORIAL8:
			LoadTextureFromFile("Assets/Tutorial_8.png", &m_pTex[i]);
			break;
		case LOGO:
			LoadTextureFromFile("Assets/Logo.png", &m_pTex[i]);
			break;
		case VICTORY:
			LoadTextureFromFile("Assets/victory.png", &m_pTex[i]);
			break;
		case BB:
			LoadTextureFromFile("Assets/BB.png", &m_pTex[i]);
			break;
		case KILLS:
			LoadTextureFromFile("Assets/Kills.png", &m_pTex[i]);
			break;


		case MAX_KIND:
			break;
		default:
			break;
		}
		
	}
}

void ParallelProjection::UninitTexture()
{
	for (int i = 0; i < MAX_KIND; i++)
	{
		SAFE_RELEASE(m_pTex[i]);
	}
}

void ParallelProjection::SetAnime(int Start, int Num, int AnimeSpd, bool Loop)
{
	if (m_eState == ANIME::PLAY) return;

	// 開始位置
	m_AnimeStart.x = Start % (int)m_Split.x;
	m_AnimeStart.y = Start / (int)m_Split.x;
	m_TexCoord.x = m_AnimeStart.x;
	m_TexCoord.y = m_AnimeStart.y;
	// 終了位置
	m_AnimeLast.x = ((int)m_AnimeStart.x + Num) % (int)m_Split.x;
	m_AnimeLast.y = (int)m_AnimeStart.y + ((int)m_AnimeStart.x + Num ) / (int)m_Split.y;

	m_nAnimeSpd = AnimeSpd;
	m_bLoop = Loop;
	m_eState = ANIME::PLAY;
	m_nCnt = 0;
}
