#pragma once

#include "Component.h"
#include "MySound.h"


class Object;

class Bullet : public Component
{
public:
	Bullet();
	~Bullet();

	virtual void Start();
	virtual void Uninit() { m_pLord = nullptr; }
	virtual void Update();
	virtual void Draw();

	virtual void OnCollision(Object *);

	int GetAttack() { return m_nAttack; }
	Object *GetLord() { return m_pLord; }

	void SetCameraAngle(float AngleXz, float AngleY) { m_CameraXzAngle = AngleXz; m_CameraYAngle = AngleY; }
	void SetLord(Object* Lord) { m_pLord = Lord; }
	void SetNum(int num) { m_Num = num; }
	void SetType(bool type) { m_bType = type; }
	void SetAttack(int atk) { m_nAttack = atk; }
protected:
private:
	static CSound m_Sound;
	int m_nAttack;
	float m_CameraXzAngle;
	float m_CameraYAngle;
	//弾打ったオブジェクトの特定
	Object *m_pLord;
	int m_Num;
	int m_Time;

	bool m_bType;

};