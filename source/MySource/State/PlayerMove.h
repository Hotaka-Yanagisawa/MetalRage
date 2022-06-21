////////////////////////////////////////////////////////////////////////////////////////////
// PlayerMove.h
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