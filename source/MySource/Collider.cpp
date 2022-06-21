#include "Collider.h"
#include "Object.h"

std::list<Collider*> Collider::m_List;

Collider::Collider()
{
	m_Parent = nullptr;
	m_CollisionType = ObjectCollisionType::COLLISION_DYNAMIC;
	m_List.push_back(this);
}


Collider::~Collider()
{
	m_List.remove(this);
#ifndef DEB
	delete m_Cube;
#endif
}

void Collider::Start()
{
	m_Scale = m_Parent->GetScale();
	m_Translate = m_Parent->GetTranslate();
#ifndef DEB
	m_Cube = new Cube(m_Translate, m_Scale);
#endif
}

void Collider::Uninit()
{
}

void Collider::Update()
{
	m_Translate = m_Parent->GetTranslate();
#ifndef DEB
	m_Cube->SetPos(m_Translate);
#endif
}

void Collider::Draw()
{
#ifndef DEB
	m_Cube->Draw();
#endif
}

void Collider::SetTranslate(Float3 newTranslate)
{
	m_Translate = newTranslate;
#ifndef DEB
	m_Cube->SetPos(m_Translate);
#endif
}

void Collider::SetTranslate(float x, float y, float z)
{ 
	m_Translate.x = x; 
	m_Translate.y = y; 
	m_Translate.z = z;
#ifndef DEB
	m_Cube->SetPos(m_Translate); 
#endif
}

void Collider::SetScale(Float3 newScale)
{
	m_Scale = newScale;
#ifndef DEB
	m_Cube->SetScale(m_Scale);
#endif
	m_Parent->SetScale(m_Scale);
}

void Collider::SetScale(float x, float y, float z)
{
	m_Scale.x = x;
	m_Scale.y = y;
	m_Scale.z = z;
#ifndef DEB
	m_Cube->SetScale(m_Scale);
#endif
}
