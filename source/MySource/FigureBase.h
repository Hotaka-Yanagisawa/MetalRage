#pragma once

#include "DrawBuffer.h"
#include <DirectXMath.h>
#include "Component.h"
#include "FloatOperator.h"

namespace Figure
{
	enum Texture
	{
		NULL_TEX,
		WALL,
		DOOR,
		BRICK, 
		WOOD,
		BULLET,

		MAX_TEX,
	};
}


class FigureBase : public Component
{
public:
	struct Vertex
	{
		Float3 pos;
		DirectX::XMFLOAT4 color;
		DirectX::XMFLOAT2 uv;
	};

	FigureBase();
	//FigureBase(Float3 pos);
	~FigureBase();

	static void InitTexture();
	static void UninitTexture();

	virtual void Start();
	virtual void Update();
	virtual void Draw();

	void SetPos(Float3);
	void SetPos(float x, float y, float z);
	void SetTexNum(Figure::Texture Kind) { m_TexKind = Kind; }
	virtual void SetScale(Float3);
	virtual void SetScale(float w, float h, float d);

private:
	//float m_width, m_height, m_depth;

protected:
	Figure::Texture m_TexKind;
	Float3 m_pos;
	Float3 m_Scale;
	static ID3D11ShaderResourceView* m_pTexture[Figure::MAX_TEX];
	DrawBuffer m_buffer;
};


