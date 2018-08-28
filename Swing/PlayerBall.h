#pragma once
#include <string>
#include "VECTOR2.h"
#include "Obj.h"

class PlayerBall :
	public Obj
{
public:
	PlayerBall();
	~PlayerBall();
	//void Draw();

private:
	void Move(void);
};