////////////////////////////////////////////////////////////////////////////////////////////
// DiscoveryState.h
//----------------------------------------------------------------------------------------
// ì¬ÒF–ö‘ò ”¿‹M
//----------------------------------------------------------------------------------------
// ”­Œ©ó‘Ô‚ÌŠK‘w
//-----------------------------------------------------------------------------------------
// 2021/01/09	ì¬
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "HierarchyEnemyState.h"

class Enemy;

// Šª‚«ã‚°ó‘Ô
class DiscoveryState : public HierarchyEnemyState
{
public:
	static DiscoveryState *GetInstance()
	{
		static DiscoveryState instance;
		return &instance;
	}

	virtual void Init       (Enemy *);
	virtual void Update     (Enemy *);
	virtual void ChangeState(Enemy *, EnemyState *);

private:
	DiscoveryState() {}
};

