////////////////////////////////////////////////////////////////////////////////////////////
// PlayerJump.h
//----------------------------------------------------------------------------------------
// �쐬�ҁF���� ���M
//----------------------------------------------------------------------------------------
// �ړ��Ɋւ��邱��
// 
//-----------------------------------------------------------------------------------------
// 2021/01/06	�쐬
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "PlayerState.h"

class PlayerJump :public PlayerState
{
public:
	static PlayerJump *GetInstance()
	{
		static PlayerJump instance;
		return &instance;
	}

	virtual void Init(Player *obj);
	//	virtual void Uninit(Player *obj);
	virtual void Update(Player *obj);
	//	virtual void Draw(Player *obj);
	virtual void ChangeState(Player * obj, PlayerState *newState);
};