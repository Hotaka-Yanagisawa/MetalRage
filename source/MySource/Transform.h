#pragma once
#include "FloatOperator.h"

struct Transform
{
	Float3 Translate;
	Float3 Rotate;
	Float3 Scale;
	Float3 Move;
	Float3 Acc;
	Transform() :Translate(0), Rotate(0), Scale(1), Move(0),Acc(1) {}
};