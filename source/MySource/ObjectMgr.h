#pragma once

#include "FloatOperator.h"
#include "Transform.h"
#include "Cube.h"

class Object;
enum Object_Type;

class ObjectMgr
{
public:
	static ObjectMgr *GetInstance()
	{
		static ObjectMgr instance;
		return &instance;
	}

	Object *CreateObject(Object_Type);
	Object *CreatePlayer(Float3 Translate, Float3 Scale, int Controller = 0);
	Object *CreateEnemy(Float3 Translate, Float3 Scale, Transform *Transform);
	Object *CreateField(Float3 Translate, Float3 Scale, Figure::Texture Kind, bool Floor = false);
	Object *CreateCollider(Float3 Translate, Float3 Scale, int Player = 0);
	void AllDeleteObject();
private:
	ObjectMgr() {}
	~ObjectMgr() {}

};
