#pragma once

#include "Billboard.h"

class Explosion
{
public:
	static Explosion *GetInstance()
	{
		static Explosion instance;
		return &instance;
	}
	
#define MAX_EXPLOSION (10)

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Set(Float3);

private:
	Explosion();
	~Explosion();
	Billboard m_Bill[MAX_EXPLOSION];
};