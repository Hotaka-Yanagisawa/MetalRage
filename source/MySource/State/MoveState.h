////////////////////////////////////////////////////////////////////////////////////////////
// MoveState.h
//----------------------------------------------------------------------------------------
// �쐬�ҁF���� ���M
//----------------------------------------------------------------------------------------
// �ړ���ԂɊւ��邱��
// 
//-----------------------------------------------------------------------------------------
// 2020/01/07	�쐬
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "EnemyState.h"

class HierarchyEnemyState;

class MoveState :public EnemyState
{
public:
	static MoveState *GetInstance()
	{
		static MoveState instance;
		return &instance;
	}

	virtual void Init(Enemy *);
	virtual void Update(Enemy *, HierarchyEnemyState *parent);
};