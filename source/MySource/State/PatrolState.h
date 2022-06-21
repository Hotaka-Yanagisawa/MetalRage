////////////////////////////////////////////////////////////////////////////////////////////
// PatrolState.h
//----------------------------------------------------------------------------------------
// ì¬ÒF–ö‘ò ”¿‹M
//----------------------------------------------------------------------------------------
// „‰ñó‘Ô‚ÌŠK‘w
//-----------------------------------------------------------------------------------------
// 2021/01/09	ì¬
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "HierarchyEnemyState.h"

class Enemy;

// Šª‚«ã‚°ó‘Ô
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

