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
	
	//����|�C���g�̍��W
	static Float3 m_decidedPoints[19][19];
	//���Ɉړ�����ꏊ
	Float3 m_MovePoint;
	int m_nPointNum;
	Billboard m_Placemark;
	static int m_Num;
	Transform *m_pPlayerTransform;
protected:
private:
	HierarchyEnemyState *m_HierarchyState;	//�K�w
	EnemyState *m_State;					//���
	Fan m_fan;


	//---�}�K�W��&�����[�h---
//�}�K�W���̍ő僊���[�h���W���P��̔��˂łQ���ł�
	const int MAGAZINE_SIZE = 10;
	//���݂̃}�K�W�����̎c�e���O�ɂȂ�Ǝ��������[�h���ȁH
	int m_MagazineNum;
	//�����[�h�܂łɂ����鎞�ԂQ�b���炢�ł�����
	const float RELOAD_TIME = 2.0f;
	float m_ReloadTime;
	//�����[�h�����ǂ���
	bool m_bReload;
	//�e�̔��ˊԊu0.5�b���炢�H
	const float FIRE_INTERVAL = 0.2f;
	float m_FireInterval;
	//���ˊԊu�����ǂ���
	bool m_bFire;
};

