#include "Object.h"
#include "Component.h"

std::list<Object*> Object::m_ObjectList;
Object::Object()
{
	m_ObjectList.push_back(this);
	m_Transform = new Transform();
	m_bUse = true;
}
Object::~Object()
{
	m_ObjectList.remove(this);
	delete m_Transform;
	for (auto com : ComponentList)
	{
		delete com;
	}
	ComponentList.clear();
}
void Object::Update() 
{
	auto buff = ComponentList;
	for (auto com : buff)
	{
		if (com->m_bRemove)
		{
			com->Uninit();
			
			ComponentList.remove(com);
			continue;
		}
	}
	auto List = ComponentList;
	for (auto com : List)	com->Update();
	
	m_Transform->Translate += m_Transform->Move;
}

void Object::Draw() { for (auto com : ComponentList)	com->Draw(); }