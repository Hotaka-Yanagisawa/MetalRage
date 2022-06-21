#pragma once

#include "Collider.h"

//--- 定数
// 当たり判定を行う組み合わせの最大数
// ※ほんとはリスト構造で制限ないほうがよい
#define MAX_COLLISION_REGISTER (1000)

class Collision
{
public:
	Collision();
	~Collision();

	bool Init();
	void Uninit();
	void Update();

	bool IsCollidingFanAndPoint(Fan fan, Float2 point);

	void Register(Collider *pA, Collider * pB);

private:
	void Push(Collider *pDynamic, Collider *pStatic);

private:
	//Collider *m_pList[MAX_COLLISION_REGISTER][2];
	//int m_registerNum;	//登録した数

};



