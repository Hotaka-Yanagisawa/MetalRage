////////////////////////////////////////////////////////////////////////////////////////////
// PatrolState.h
//----------------------------------------------------------------------------------------
// �쐬�ҁF���� ���M
//----------------------------------------------------------------------------------------
// �����Ԃ̊K�w
//-----------------------------------------------------------------------------------------
// 2021/01/09	�쐬
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "HierarchyEnemyState.h"

class Enemy;

// �����グ���
class PatrolState : public HierarchyEnemyState
{
public:
	static PatrolState *GetInstance()
	{
		static PatrolState instance;
		return &instance;
	}

	virtual void Init(Enemy *);
	virtual void Update(Enemy *);
	virtual void ChangeState(Enemy *, EnemyState *);

private:
	PatrolState() {}
};

