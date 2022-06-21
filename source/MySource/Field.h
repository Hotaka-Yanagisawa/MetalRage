#pragma once

#include "Cube.h"
#include "Shader.h"

class Field
{
public:
	Field(Float3 size);
	virtual ~Field();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	// íléÊìæ
	Float3 GetPos() { return m_pos; }
	Float3 GetScale() { return m_Scale; }
	Float3 GetMove() { return m_move; }
	
	// ílê›íË
	void SetPos(Float3 pos) { m_pos = pos; }
	void SetMove(Float3 move) { m_move = move; }
//protected:
private:
	Float3 m_pos;
	Float3 m_Scale;
	Float3 m_move;

	Cube* m_pCube;

};




