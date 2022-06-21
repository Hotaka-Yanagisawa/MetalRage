////////////////////////////////////////////////////////////////////////////////////////////
// FireState.h
//----------------------------------------------------------------------------------------
// �쐬�ҁF���� ���M
//----------------------------------------------------------------------------------------
// ���ˏ�ԂɊւ��邱��
//-----------------------------------------------------------------------------------------
// 2020/01/11	�쐬
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "EnemyState.h"

class HierarchyEnemyState;

class FireState :public EnemyState
{
public:
	static FireState *GetInstance()
	{
		static FireState instance;
		return &instance;
	}

	virtual void Init(Enemy *);
	virtual void Update(Enemy *, HierarchyEnemyState *parent);
};
