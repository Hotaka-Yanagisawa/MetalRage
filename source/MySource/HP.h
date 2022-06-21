
#pragma once

#include "Component.h"

class HP : public Component
{
public:
	HP() { m_nHp = 0; };
	~HP() {};

	virtual void Start();
	//virtual void Uninit();
	//virtual void Update();
	//virtual void Draw();

	int GetHp() { return m_nHp; }
	void SetHp(int newHP) { m_nHp = newHP; }
	void ReduceHP(int ReduceVal) { m_nHp -= ReduceVal; }
	//void SetLord(Object* Lord) { m_pLord = Lord; }

	virtual void OnCollision(Object *obj);
protected:
private:
	int m_nHp;
	//Object *m_pLord;

};