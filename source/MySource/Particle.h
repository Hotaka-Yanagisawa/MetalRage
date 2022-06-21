#pragma once

#include "Billboard.h"

#define MAX_PARTICLE (30)

class Particle
{
public:
	struct Param
	{
		Billboard m_Bb;
		bool bExist;
		float fLife;
		Float3 Move;
	};

	Particle();
	~Particle();

	void Init();
	void Uninit();
	void Update();
	void Draw();
	void Set(Float3 Translate);

	Param *GetParam() { return m_Particle; }

private:

	Param m_Particle[MAX_PARTICLE];
};