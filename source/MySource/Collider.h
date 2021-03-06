#pragma once

#include "Component.h"
#include "Cube.h"
#include <list>
#include "FloatOperator.h"
#include "Defines.h"

#define COLLIDER_LIST (Collider::m_List)

enum ObjectCollisionType
{
	COLLISION_STATIC,	// 静止している物体
	COLLISION_DYNAMIC,	// 動いている物体
	COLLISION_OVERLAP,	// 貫通する物体
};

class Object;

class Collider : public Component	
{
public:
	Collider();
	//Collider(Object *);
	~Collider();
	void Start() override;
	void Uninit() override;

	void Update() override;
	void Draw() override;

	void SetTranslate(Float3 newTranslate);

	void SetTranslate(float x, float y, float z);
	void SetScale(Float3 newScale);
	void SetScale(float x, float y, float z); 
	void SetCollisionType(ObjectCollisionType newCollisionType) { m_CollisionType = newCollisionType; }
	ObjectCollisionType GetCollisionType() { return m_CollisionType; }
	

	static std::list<Collider*> m_List;

private:
#ifndef DEB
	Cube *m_Cube;
#endif
	Float3 m_Scale;
	Float3 m_Translate;
	ObjectCollisionType m_CollisionType;
};
