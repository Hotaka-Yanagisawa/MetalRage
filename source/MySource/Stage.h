#pragma once

#include "Field.h"
#include "Component.h"

class Stage : public Component
{
public:
	Stage();
	~Stage();

	void Start() override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	Field *GetField(int index);
	int GetFieldNum() { return m_nFieldNum; }

private:

	Field **m_ppFields;
	int m_nFieldNum;

};

