#include "Billboard.h"
#include "Shader.h"
#include "Object.h"
#include "Camera.h"
#include "Scene.h"
#include "State/GameState.h"
//#include "Texture.h"

ID3D11ShaderResourceView* Billboard::m_pTex[MAX_KIND];

void Billboard::Start()
{
	m_nTexKind = AIM;
	//m_polyVtx = new Vertex[4];

	m_polyVtx[0].pos = { -0.5f, 0.5f, 0 };
	m_polyVtx[1].pos = { 0.5f, 0.5f, 0 };
	m_polyVtx[2].pos = { -0.5f, -0.5f, 0 };
	m_polyVtx[3].pos = { 0.5f, -0.5f, 0 };

	for (int i = 0; i < 4; ++i)
		m_polyVtx[i].color = Float4(1, 1, 1, 1);

	m_polyVtx[0].uv = { 0, 0 };
	m_polyVtx[1].uv = { 1, 0 };
	m_polyVtx[2].uv = { 0, 1 };
	m_polyVtx[3].uv = { 1, 1 };

	long idx[] = { 0,1,2, 1,3,2 };

	// バッファ作成
	m_Buffer.CreateVertexBuffer(m_polyVtx, sizeof(Vertex), 4, true);
	m_Buffer.CreateIndexBuffer(idx, sizeof(idx) / sizeof(long));

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

void Billboard::Uninit()
{

}

void Billboard::Update()
{
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

void Billboard::Draw()
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
		Scene::GetInstance()->m_pCamera->Bind();
	}
	else if (GameState::GetInstance()->m_nDrawNum == 1)
	{
		if (Scene::GetInstance()->m_pCamera2P != nullptr)
			Scene::GetInstance()->m_pCamera2P->Bind();
	}
	// 逆行列取得

	DirectX::XMMATRIX InvCamera = DirectX::XMMatrixInverse(0, Scene::GetInstance()->m_pCamera->GetView());
	DirectX::XMFLOAT4X4 mat;
	DirectX::XMStoreFloat4x4(&mat, InvCamera);
	mat._41 = 0; mat._42 = 0; mat._43 = 0;
	InvCamera = DirectX::XMLoadFloat4x4(&mat);
	
	Float3 Scale = m_Scale;
	Scale.x *= 0.5f;
	Scale.y *= 0.5f;
	Scale.z *= 0.5f;

	SHADER->SetWorld(
		InvCamera
		* DirectX::XMMatrixScaling(Scale.x, Scale.y, Scale.z)
		
		* DirectX::XMMatrixTranslation(m_Translate.x,m_Translate.y,m_Translate.z));

	m_Buffer.Write(m_polyVtx);
	m_Buffer.Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	SHADER->SetTexture(m_pTex[NULL_TEX]);
}

void Billboard::InitTexture()
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
			LoadTextureFromFile("Assets/expSmall.png", &m_pTex[i]);
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
			LoadTextureFromFile("Assets/Smoke2.png", &m_pTex[i]);
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
		case MAX_KIND:
			break;
		default:
			break;
		}

	}
}

void Billboard::UninitTexture()
{
	for (int i = 0; i < MAX_KIND; i++)
	{
		SAFE_RELEASE(m_pTex[i]);
	}
}

void Billboard::SetAnime(int Start, int Num, int AnimeSpd, bool Loop)
{
	if (m_eState == ANIME::PLAY) return;

	// 開始位置
	m_AnimeStart.x = Start % (int)m_Split.x;
	m_AnimeStart.y = Start / (int)m_Split.x;
	m_TexCoord.x = m_AnimeStart.x;
	m_TexCoord.y = m_AnimeStart.y;
	// 終了位置
	m_AnimeLast.x = ((int)m_AnimeStart.x + Num) % (int)m_Split.x;
	m_AnimeLast.y = (int)m_AnimeStart.y + ((int)m_AnimeStart.x + Num) / (int)m_Split.y;

	m_nAnimeSpd = AnimeSpd;
	m_bLoop = Loop;
	m_eState = ANIME::PLAY;
	m_nCnt = 0;
}
