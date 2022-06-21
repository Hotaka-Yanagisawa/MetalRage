#pragma once

#include "Component.h"
#include <list>
#include "FloatOperator.h"
#include "Defines.h"

#define COLLIDER2D_LIST (Collider2D::m_List)

class Object;

class Collider2D : public Component	
{
public:
	Collider2D();
	~Collider2D();
	void Start() override;
	void Uninit() override;

	void Update() override;
	void Draw() override;

	void SetTranslate(Float3 newTranslate);

	void SetTranslate(float x, float y, float z);
	void SetScale(Float3 newScale);
	void SetScale(float x, float y, float z); 

	static std::list<Collider2D*> m_List;

private:
	Float3 m_Scale;
	Float3 m_Translate;
};
