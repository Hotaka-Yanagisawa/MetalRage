#pragma once

#include "Component.h"
#include "FloatOperator.h"
#include "DrawBuffer.h"
#include "Texture.h"
#include "Defines.h"


class ParallelProjection : public Component
{
public:
	// í∏ì_èÓïÒ
	struct Vertex
	{
		Float3 pos;
		Float4 color;
		Float2 uv;
	};
	ParallelProjection() {};
	~ParallelProjection() {};

	void Start();
	void Uninit();
	void Update();
	void Draw();

	static void InitTexture();
	static void UninitTexture();

	void SetAnime(int Start, int Num, int AnimeSpd, bool Loop = false);

	void SetColor(Float4 color) { m_Color = color; }
	void SetSplit(Float2 Split) { m_Split = Split; }
	void SetTexCoord(Float2 TexCoord) { m_TexCoord = TexCoord; }
	void SetAlpha(float newAlpha) { m_Color.w = newAlpha; }
	void SetScale(Float3 newScale) { m_Scale = newScale; }
	void SetTranslate(Float3 newTranslate) { m_Translate = newTranslate; }
	void SetTexKind(Texture_Kind Kind) { m_nTexKind = Kind; }

	Vertex *GetVertex() { return m_polyVtx; }
private:
	Float4 m_Color;
	Float3 m_Translate;
	Float3 m_Scale;
	Float2 m_Split;
	Float2 m_TexCoord;
	Float2 m_AnimeStart;
	Float2 m_AnimeLast;
	int m_nCnt;
	int m_nAnimeSpd;
	bool m_bLoop;
	ANIME::ANIME_STATE m_eState;

	Texture_Kind m_nTexKind;

	Vertex m_polyVtx[4];

	static ID3D11ShaderResourceView* m_pTex[MAX_KIND];
	DrawBuffer m_Buffer;
};