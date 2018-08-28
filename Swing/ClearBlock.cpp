#include <iostream>
#include <DxLib.h>
#include "ClearBlock.h"
#include "GameTask.h"

ClearBlock::ClearBlock()
{
	size = 16;
	ID = CHIP_CLEAR;
}

ClearBlock::~ClearBlock()
{
}

bool ClearBlock::CollisionProcessing(void)
{
	int count = lpGameTask.player->GetCleCnt();
	count--;
	lpGameTask.player->SetCleCnt(count);
	return true;
}