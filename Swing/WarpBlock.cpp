#include "WarpBlock.h"
#include "GameTask.h"

WarpBlock::WarpBlock()
{
	size = 16;
}

WarpBlock::~WarpBlock()
{
}

bool WarpBlock::CollisionProcessing(void)
{
	VECTOR2 Pos = {80, 480};		//仮に作成した段階、これをホントに実装するなら乱数
	lpGameTask.player->WarpPos(Pos);
	return true;
}