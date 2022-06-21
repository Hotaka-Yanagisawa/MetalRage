#pragma once

#include <DirectXMath.h>
#include "Component.h"
#include "FloatOperator.h"
#include "State/PlayerState.h"
#include <list>
#include "ParallelProjection.h"
#include "MySound.h"
#include "Explosion.h"

class Bullet;
class Camera;


class Player : public Component
{
public:
	Player();
	virtual ~Player();

	void Start() override;
	void Uninit()override;
	void Update()override;
	void Draw()  override;
	void OnCollision(Object *) override;

	void CreateBullet();
	void Boost();
	void BoostUpdate();
	void Reload();
	void ReloadUpdate();
	void FireUpdate();
	void HpPolyUpdate();
	void CommonUpdate();
	void MoveUpdate();
	PlayerState *GetState() { return m_State; }
	
	void SetState(PlayerState *newState) { m_State = newState; }
	void SetCameraAngle(float AngleXz, float AngleY) { m_CameraXzAngle = AngleXz; m_CameraYAngle = AngleY; }

	void SetPlayerNum(int num) { m_PlayerNum = num; }
	void SetHitCheck() { m_nHitCheckCnt = 30; }

	//�K�v�ɂȂ����̂Œǉ�
	Camera *m_pCamera;
	//�J�����̃A���O������v���C���[�ړ��������o��
	float m_CameraXzAngle;
	//����͕�
	float m_CameraYAngle;
	//�R���g���[���[�p�̕ϐ��B��P�Ȃ̂�
	int m_PlayerNum;

	//�����[�h�����ǂ���
	bool m_bReload;
	//���ˊԊu�����ǂ���
	bool m_bFire;
	//�W�����v�����ǂ���
	bool m_bJump;
	//�ړ������ǂ���
	bool m_bMove;

	static int Num;
	
protected:
private:
	PlayerState *m_State;					//���

	int m_nHitCheckCnt;
	//---�u�[�X�g---
	//MAX100�u�[�X�g1���25����A�b25��
	const float BOOST_USAGE = 25.0f;
	const float BOOST_RECOVERY = 10.0f;
	const float MAX_BOOST = 100.0f;
	float m_BoostNum;
	//---�}�K�W��&�����[�h---
	//�}�K�W���̍ő僊���[�h���W���P��̔��˂łQ���ł�
	const int MAGAZINE_SIZE = 8;
	//���݂̃}�K�W�����̎c�e���O�ɂȂ�Ǝ��������[�h���ȁH
	int m_MagazineNum;
	//�����[�h�܂łɂ����鎞�ԂQ�b���炢�ł�����
	const float RELOAD_TIME = 2.0f;
	float m_ReloadTime;
	//�e�̔��ˊԊu0.5�b���炢�H
	const float FIRE_INTERVAL = 1.0f;
	float m_FireInterval;

	//---UI
	//HP�Q�[�W
	ParallelProjection m_HpGauge[10];
	//HP����
	ParallelProjection m_HpPoly[3];
	//�c�e��
	ParallelProjection m_bulletsPoly;
	//�Ə�
	ParallelProjection m_Aim[4];
	//�u�[�X�g�Q�[�W
	ParallelProjection m_BoostGauge;
	//����
	static ParallelProjection m_Victory;

	//---�T�E���h
	CSound m_Sound;
};

