#pragma once

#include "Component.h"
#include "State/HierarchyEnemyState.h"
#include "FloatOperator.h"
#include "Defines.h"
#include "Transform.h"
#include "Billboard.h"


class Enemy : public Component
{
public:
	Enemy();
	~Enemy();

	virtual void Start();
	virtual void Update();
	virtual void Draw();

	static void PointsInit();

	EnemyState *GetState() { return m_State; }
	HierarchyEnemyState *GetHierarchyState() { return m_HierarchyState; }

	void SetState(EnemyState *newState);
	void SetHierarchyState(HierarchyEnemyState *newState);
	void SetPlayerTransform(Transform *pPlayerTransform) { m_pPlayerTransform = pPlayerTransform; }

	void CreateBullet();
	
	//巡回ポイントの座標
	static Float3 m_decidedPoints[19][19];
	//次に移動する場所
	Float3 m_MovePoint;
	int m_nPointNum;
	Billboard m_Placemark;
	static int m_Num;
	Transform *m_pPlayerTransform;
protected:
private:
	HierarchyEnemyState *m_HierarchyState;	//階層
	EnemyState *m_State;					//状態
	Fan m_fan;


	//---マガジン&リロード---
//マガジンの最大リロード数８発１回の発射で２発でる
	const int MAGAZINE_SIZE = 10;
	//現在のマガジン内の残弾数０になると自動リロードかな？
	int m_MagazineNum;
	//リロードまでにかかる時間２秒ぐらいでいいか
	const float RELOAD_TIME = 2.0f;
	float m_ReloadTime;
	//リロード中かどうか
	bool m_bReload;
	//弾の発射間隔0.5秒くらい？
	const float FIRE_INTERVAL = 0.2f;
	float m_FireInterval;
	//発射間隔中かどうか
	bool m_bFire;
};

