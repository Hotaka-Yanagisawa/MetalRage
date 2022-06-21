#pragma once

#include "Billboard.h"

class SandSmoke
{
public:
	static SandSmoke *GetInstance()
	{
		static SandSmoke instance;
		return &instance;
	}

#define MAX_SAND_SMOKE (20)

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Set(Float3);

private:
	SandSmoke() {}
	~SandSmoke() {}

	struct SmokeStatus
	{
		bool bExist;
		Billboard bill;
		Float3 move;
	};

	Float3 m_AddScale;

	SmokeStatus m_SmokeStatus[MAX_SAND_SMOKE];

};

