#include "Collider2D.h"
#include "Object.h"

std::list<Collider2D*> Collider2D::m_List;

Collider2D::Collider2D()
{
	m_Parent = nullptr;
	m_List.push_back(this);
}


Collider2D::~Collider2D()
{
	m_List.remove(this);
}

void Collider2D::Start()
{
	m_Scale = m_Parent->GetScale();
	m_Translate = m_Parent->GetTranslate();
}

void Collider2D::Uninit()
{
}

void Collider2D::Update()
{
	m_Translate = m_Parent->GetTranslate();
}

void Collider2D::Draw()
{
}

void Collider2D::SetTranslate(Float3 newTranslate)
{
	m_Translate = newTranslate;
}

void Collider2D::SetTranslate(float x, float y, float z)
{ 
	m_Translate.x = x; 
	m_Translate.y = y; 
	m_Translate.z = z;
}

void Collider2D::SetScale(Float3 newScale)
{
	m_Scale = newScale;
	m_Parent->SetScale(m_Scale);
}

void Collider2D::SetScale(float x, float y, float z)
{
	m_Scale.x = x;
	m_Scale.y = y;
	m_Scale.z = z;
}
