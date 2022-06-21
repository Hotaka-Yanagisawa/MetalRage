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

	//必要になったので追加
	Camera *m_pCamera;
	//カメラのアングルからプレイヤー移動方向を出す
	float m_CameraXzAngle;
	//これは別
	float m_CameraYAngle;
	//コントローラー用の変数。何Pなのか
	int m_PlayerNum;

	//リロード中かどうか
	bool m_bReload;
	//発射間隔中かどうか
	bool m_bFire;
	//ジャンプ中かどうか
	bool m_bJump;
	//移動中かどうか
	bool m_bMove;

	static int Num;
	
protected:
private:
	PlayerState *m_State;					//状態

	int m_nHitCheckCnt;
	//---ブースト---
	//MAX100ブースト1回で25消費、秒25回復
	const float BOOST_USAGE = 25.0f;
	const float BOOST_RECOVERY = 10.0f;
	const float MAX_BOOST = 100.0f;
	float m_BoostNum;
	//---マガジン&リロード---
	//マガジンの最大リロード数８発１回の発射で２発でる
	const int MAGAZINE_SIZE = 8;
	//現在のマガジン内の残弾数０になると自動リロードかな？
	int m_MagazineNum;
	//リロードまでにかかる時間２秒ぐらいでいいか
	const float RELOAD_TIME = 2.0f;
	float m_ReloadTime;
	//弾の発射間隔0.5秒くらい？
	const float FIRE_INTERVAL = 1.0f;
	float m_FireInterval;

	//---UI
	//HPゲージ
	ParallelProjection m_HpGauge[10];
	//HP数字
	ParallelProjection m_HpPoly[3];
	//残弾数
	ParallelProjection m_bulletsPoly;
	//照準
	ParallelProjection m_Aim[4];
	//ブーストゲージ
	ParallelProjection m_BoostGauge;
	//勝利
	static ParallelProjection m_Victory;

	//---サウンド
	CSound m_Sound;
};

