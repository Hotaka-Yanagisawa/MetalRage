#pragma once

#include "Collider.h"

//--- �萔
// �����蔻����s���g�ݍ��킹�̍ő吔
// ���ق�Ƃ̓��X�g�\���Ő����Ȃ��ق����悢
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
	//int m_registerNum;	//�o�^������

};



