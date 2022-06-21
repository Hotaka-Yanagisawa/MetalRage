////////////////////////////////////////////////////////////////////////////////////////////
// PlayerMove.h
//----------------------------------------------------------------------------------------
// ì¬ÒF–ö‘ò ”¿‹M
//----------------------------------------------------------------------------------------
// ˆÚ“®‚ÉŠÖ‚·‚é‚±‚Æ
// 
//-----------------------------------------------------------------------------------------
// 2021/01/06	ì¬
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "PlayerState.h"

class PlayerMove :public PlayerState
{
public:
	static PlayerMove *GetInstance()
	{
		static PlayerMove instance;
		return &instance;
	}

	virtual void Init(Player *obj);
//	virtual void Uninit(Player *obj);
	virtual void Update(Player *obj);
//	virtual void Draw(Player *obj);
	virtual void ChangeState(Player * obj, PlayerState *newState);
};