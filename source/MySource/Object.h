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
	//�I�u�W�F�N�g�������Ă���R���|�[�l���g���擾
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

	//�I�u�W�F�N�g�����R���|�[�l���g��ǉ�
	template<class T>
	T* AddComponent()
	{
		T* buff = new T();
		buff->m_Parent = this;
		ComponentList.push_back(buff);
		buff->Start();
		return buff;
	}

	//�I�u�W�F�N�g�������Ă���R���|�[�l���g�̃��X�g
	std::list<Component*> ComponentList;
	//�I�u�W�F�N�g�̃��X�g
	static std::list<Object*> m_ObjectList;
	//�Q�b�^�[
	Transform *GetTransform() { return m_Transform; }
	Float3 GetTranslate() { return m_Transform->Translate; }
	Float3 GetRotate() { return m_Transform->Rotate; }
	Float3 GetScale() { return m_Transform->Scale; }
	Float3 GetMove() { return m_Transform->Move; }
	Float3 GetAcc() { return m_Transform->Acc; }
	Object_Type GetType() { return m_eObjType; }
	bool GetUse() { return m_bUse; }
	//�Z�b�^�[
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
	bool m_bUse;	//�g�p�ς݂Ȃ�false�ɂ���delete
};