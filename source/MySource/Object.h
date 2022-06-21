#pragma once

#include <list>
#include "Transform.h"

#define OBJ_LIST (Object::m_ObjectList)

enum Object_Type
{
	PLAYER,
	ENEMY,
	BULLET,
	FIELD,
	FLOOR,
	COLLIDER,

	MAX
};

using namespace DirectX;

class Component;

class Object
{
public:

	Object();
	~Object();
	void Update();
	void Draw();
	//オブジェクトが持っているコンポーネントを取得
	template<class T>
	T* GetComponent()
	{
		for (auto com : ComponentList)
		{
			T* buff = dynamic_cast<T*>(com);
			if (buff != nullptr)
				return buff;
		}
		return nullptr;
	}

	//オブジェクトが持つコンポーネントを追加
	template<class T>
	T* AddComponent()
	{
		T* buff = new T();
		buff->m_Parent = this;
		ComponentList.push_back(buff);
		buff->Start();
		return buff;
	}

	//オブジェクトが持っているコンポーネントのリスト
	std::list<Component*> ComponentList;
	//オブジェクトのリスト
	static std::list<Object*> m_ObjectList;
	//ゲッター
	Transform *GetTransform() { return m_Transform; }
	Float3 GetTranslate() { return m_Transform->Translate; }
	Float3 GetRotate() { return m_Transform->Rotate; }
	Float3 GetScale() { return m_Transform->Scale; }
	Float3 GetMove() { return m_Transform->Move; }
	Float3 GetAcc() { return m_Transform->Acc; }
	Object_Type GetType() { return m_eObjType; }
	bool GetUse() { return m_bUse; }
	//セッター
	void SetTransform(Transform *newTransform) { m_Transform = newTransform; }
	void SetTransform(Transform newTransform) { m_Transform = &newTransform; }
	void SetTranslate(Float3 newTranslate) { m_Transform->Translate = newTranslate; }
	void SetRotate(Float3 newRotate) { m_Transform->Rotate = newRotate; }
	void SetScale(Float3 newScale) { m_Transform->Scale = newScale; }
	void SetMove(Float3 newMove) { m_Transform->Move = newMove; }
	void SetAcc(Float3 newAcc) { m_Transform->Acc = newAcc; }
	void SetUse(bool state) { m_bUse = state; }
	void SetType(Object_Type Type) { m_eObjType = Type; }

	void AddTranslate(Float3 Add) { m_Transform->Translate += Add; }
	

private:
	Transform *m_Transform;
	Object_Type m_eObjType;
	bool m_bUse;	//使用済みならfalseにしてdelete
};