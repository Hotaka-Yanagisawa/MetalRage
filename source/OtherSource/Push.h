#pragma once

#include "Component.h"

class Push : public Component
{
public:
	Push() {};
	~Push() {};

	virtual void Start();

	virtual void OnCollision(Object *obj);
protected:
private:

};