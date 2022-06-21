#pragma once

#include "ParallelProjection.h"

#define FADE (Fade::GetInstance())

enum eFadeState
{
	WAIT,
	FADEIN,
	FADEOUT,
	MAX_FADE
};

class Fade
{
public:
	static Fade *GetInstance()
	{
		static Fade instance;
		return &instance;
	}

	void Init();
	void Uninit();
	bool Update();
	void Draw();

	void SetState(eFadeState newState) { m_State = newState; }

	eFadeState GetState() { return m_State; }
	void SetAlpha(float newAlpha) { m_Alpha = newAlpha; }
	void SetFadeSpd(float newSpd) { m_FadeSpd = newSpd; }
	void FadeStart(eFadeState);
private:
	Fade();
	~Fade();
	
	float m_Alpha;
	float m_FadeSpd;
	ParallelProjection m_Poly;
	eFadeState m_State;
};


