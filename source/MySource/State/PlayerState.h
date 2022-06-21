////////////////////////////////////////////////////////////////////////////////////////////
// PlayerState.h
//----------------------------------------------------------------------------------------
// �쐬�ҁF���� ���M
//----------------------------------------------------------------------------------------
// �v���C���[�̏�ԂɊւ��邱�Ƃ̒��ۃN���X
//-----------------------------------------------------------------------------------------
// 2020/12/12	�쐬
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once

class Player;
//class HierarchyPlayerState;

class PlayerState
{
public:
	virtual ~PlayerState() {}
	virtual void Init(Player *) = 0;
	//virtual void Uninit(Player *)=0;
	virtual void Update(Player *) = 0;
	virtual void ChangeState(Player * obj, PlayerState *newState) = 0;
	//virtual void Draw(Player *)=0;
	//virtual void Update(Player *, HierarchyPlayerState *) = 0;
};