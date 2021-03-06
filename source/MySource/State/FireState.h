////////////////////////////////////////////////////////////////////////////////////////////
// FireState.h
//----------------------------------------------------------------------------------------
// 作成者：柳沢 帆貴
//----------------------------------------------------------------------------------------
// 発射状態に関すること
//-----------------------------------------------------------------------------------------
// 2020/01/11	作成
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
