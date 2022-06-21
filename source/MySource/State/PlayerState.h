////////////////////////////////////////////////////////////////////////////////////////////
// PlayerState.h
//----------------------------------------------------------------------------------------
// 作成者：柳沢 帆貴
//----------------------------------------------------------------------------------------
// プレイヤーの状態に関することの抽象クラス
//-----------------------------------------------------------------------------------------
// 2020/12/12	作成
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