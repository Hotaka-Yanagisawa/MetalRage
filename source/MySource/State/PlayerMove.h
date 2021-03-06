////////////////////////////////////////////////////////////////////////////////////////////
// PlayerMove.h
//----------------------------------------------------------------------------------------
// 作成者：柳沢 帆貴
//----------------------------------------------------------------------------------------
// 移動に関すること
// 
//-----------------------------------------------------------------------------------------
// 2021/01/06	作成
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