#pragma once

class Object;

class Component
{
public:
	Component() {}
	virtual ~Component() {}
	//親、核
	virtual void Start() {}
	virtual void Uninit() { delete this; }
	virtual void Update() {}
	virtual void Draw() {}

	//当たっている時の処理
	virtual void OnCollision(Object *) {}
	//*************設計案****************************
	//当たった時の処理
	//Objectにさらにstd::Vector<Object *>を追加して
	//AがBと当たっている時に
	//find(B)でAが持つVector<Object *>にBのアドレスが
	//あった場合は処理を行わない。なかったら行う
	//AとBが当たってなかったら
	//find(B)でアドレスがあった場合ReMoveする
	//************************************************
	virtual void OnCollisionEnter(Object *) {}

	Object *m_Parent = nullptr;
	bool m_bRemove = false;
};
