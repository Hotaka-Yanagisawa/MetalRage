#include "FigureBase.h"
#include "Shader.h"
#include"Object.h"
#include "Texture.h"

ID3D11ShaderResourceView* FigureBase::m_pTexture[Figure::MAX_TEX];

FigureBase::FigureBase()
	: m_pos(0), m_Scale(1)
{
	m_Parent = nullptr;
}


FigureBase::~FigureBase()
{
}

void FigureBase::InitTexture()
{
	for (int i = 0; i < Figure::MAX_TEX; i++)
	{
		
		switch (i)
		{
		case Figure::NULL_TEX:
			m_pTexture[i] = NULL;
			break;
		case Figure::WALL:
			LoadTextureFromFile("Assets/carbon.jpg", &m_pTexture[i]);
			break;
		case Figure::DOOR:
			LoadTextureFromFile("Assets/Logo.png", &m_pTexture[i]);
			break;
		case Figure::BRICK:
			LoadTextureFromFile("Assets/Brick.jpg", &m_pTexture[i]);
			break;
		case Figure::WOOD:
			LoadTextureFromFile("Assets/Wood.jpg", &m_pTexture[i]);
			break;
		}

	}
}

void FigureBase::UninitTexture()
{
	for (int i = 0; i < Figure::MAX_TEX; i++)
	{
		SAFE_RELEASE(m_pTexture[i]);
	}
}

void FigureBase::Start()
{
	if(m_Parent != nullptr)
	m_pos = m_Parent->GetTranslate();
	m_TexKind = Figure::Texture::WALL;
}

void FigureBase::Update()
{
	if (m_Parent != nullptr)
	{
		m_pos = m_Parent->GetTranslate();
	}
}

void FigureBase::SetPos(Float3 newPos)
{
	m_pos = newPos;
}

void FigureBase::SetPos(float x, float y, float z)
{
	m_pos.x = x;
	m_pos.y = y;
	m_pos.z = z;
}

void FigureBase::SetScale(Float3 newSize)
{
	m_Scale = newSize;
}

void FigureBase::SetScale(float x, float y, float z)
{
	m_Scale.x = x;
	m_Scale.y = y;
	m_Scale.z = z;
}

void FigureBase::Draw()
{
	SHADER->SetTexture(m_pTexture[m_TexKind]);
	SHADER->SetWorld(DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	m_buffer.Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}