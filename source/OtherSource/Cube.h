#ifndef __CUBE_H__
#define __CUBE_H__

#include "FigureBase.h"
#include <DirectXMath.h>

class Cube : public FigureBase 
{
public:
	Cube();
	Cube(Float3, Float3);
	~Cube();

	void SetScale(Float3);

	void Draw();
	
};



#endif // !__CUBE_H__

