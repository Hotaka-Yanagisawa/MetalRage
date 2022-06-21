#pragma once

#include "Billboard.h"

class GlassSmoke
{
public:
	static GlassSmoke *GetInstance()
	{
		static GlassSmoke instance;
		return &instance;
	}

#define MAX_GLASS_SMOKE (2)

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Set(Float3);

private:
	GlassSmoke() {}
	~GlassSmoke() {}

	struct SmokeStatus
	{
		bool bExist;
		Billboard bill;
		Float3 move;
	};

	Float3 m_AddScale;

	SmokeStatus m_SmokeStatus[MAX_GLASS_SMOKE];

};

