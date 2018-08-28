#include <DxLib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "EditCursor.h"
#include "GameTask.h"
#include "MapCtl.h"

EditCursor::EditCursor(char(&_keyData)[256], char(&_keyDataOld)[256]) : keyData(_keyData), keyDataOld(_keyDataOld)
{
	pos = { (lpMapCtl.GetViewAreaSize() / 2) * lpMapCtl.GetChipSize() };
	keyGetRng = EDIT_KEY_GET_DEF_RNG;
	inputFlam = EDIT_KEY_GET_DEF_RNG;

	keyGetRng_S = EDIT_KEY_GET_DEF_RNG;
	inputFlam_S = EDIT_KEY_GET_DEF_RNG;

	size = 16;
	nowID = CHIP_BREAK;
	mode = MODE_UP_DOWN;
}

EditCursor::~EditCursor()
{
}

void EditCursor::UpData(void)
{
	Move();
	SetChipID();
}

void EditCursor::Draw(void)
{
	if ((animCnt / 20) % 2 == 0)
	{
		Obj::Draw(nowID);
	}
	else
	{
		Obj::Draw(CHIP_EDIT);
	}
	animCnt++;
}

//乱数を用いたランダム配置、ただし一部条件あり
void EditCursor::RandomSetChipID(void)
{
	int chipSize = lpMapCtl.GetChipSize();
	VECTOR2 areaSize = lpMapCtl.GetAreaSize();
	srand((unsigned)time(NULL));
	int max = 280;
	for (int i = 0; i < max; i++)
	{
		VECTOR2 pos = { rand() % ((areaSize.x - 2) * chipSize) + 32, rand() % ((areaSize.x - 2) * chipSize) + 32 };
		CHIP_TYPE chipID = (CHIP_TYPE)(rand() % 4 + 1);
		int chipSize = lpMapCtl.GetChipSize();
		//int size = rand() % 16;
		SET_MAP_ID(pos, chipID, chipSize);
	}
}
//使うか今のところ不明

bool EditCursor::SetChipID(void)
{
	VECTOR2 gameArea = MapCtl::GetInstance().GetAreaSize();
	int chipSize = MapCtl::GetInstance().GetChipSize();
	if (keyData[KEY_INPUT_SPACE])
	{
		if (pos.x < gameArea.x*chipSize + 32 && pos.x >= 32
			&& pos.y < gameArea.y*chipSize + 32 && pos.y >= 32)
		{
			SET_MAP_ID2(pos, nowID, size, mode);
		}
	}
	if (keyData[KEY_INPUT_Z])
	{
		SET_MAP_ID(pos, CHIP_BLANK, size);
	}
	return true;
}

void EditCursor::Move(void)
{
	int tmpSize = size;
	if (keyData[KEY_INPUT_W])
	{
		if (size < 48)
		{
			tmpSize += 2;
		}
	}
	if (keyData[KEY_INPUT_S])
	{
		if (size > 16)
		{
			tmpSize -= 2;
		}
	}



	/////////　こ↓こ↓　////////
	if (nowID == CHIP_ENEMY || CHIP_ENEMY2)
	{
		if (keyData[KEY_INPUT_E] && !keyDataOld[KEY_INPUT_E])
		{
			if (nowID == CHIP_ENEMY)
			{
				nowID = CHIP_ENEMY2;
				mode = MODE_RIGHT_LEFT;
			}
			else if (nowID == CHIP_ENEMY2)
			{
				nowID = CHIP_ENEMY;
				mode = MODE_UP_DOWN;
			}
		}
	}
	/////////　こ↑こ↑　////////


	if (keyData[KEY_INPUT_D] && !keyDataOld[KEY_INPUT_D])
	{
		nowID = (CHIP_TYPE)(nowID + 1);
		if (nowID == CHIP_PL)
		{
			nowID = (CHIP_TYPE)(nowID + 1);
		}
		if (nowID > LAST_EDIT_CHIP)
		{
			nowID = (CHIP_TYPE)(START_EDIT_CHIP);
		}
	}
	if (keyData[KEY_INPUT_A] && !keyDataOld[KEY_INPUT_A])
	{
		nowID = (CHIP_TYPE)(nowID - 1);
		if (nowID == CHIP_PL)
		{
			nowID = (CHIP_TYPE)(nowID - 1);
		}
		if (nowID < START_EDIT_CHIP)
		{
			nowID = (CHIP_TYPE)(LAST_EDIT_CHIP);
		}
	}

	if (tmpSize != size)
	{
		inputFlam_S++;
		if (inputFlam_S >= keyGetRng_S)
		{
			size = tmpSize;
			inputFlam_S = 0;
			keyGetRng_S = keyGetRng_S / 2;
			if (keyGetRng_S < 3)
			{
				keyGetRng_S = 3;
			}
		}
	}
	else
	{
		inputFlam_S = EDIT_KEY_GET_DEF_RNG;
		keyGetRng_S = EDIT_KEY_GET_DEF_RNG;
	}

	VECTOR2 tmpPos = pos;
	VECTOR2 gameArea = MapCtl::GetInstance().GetAreaSize();
	int chipSize = lpMapCtl.GetChipSize();
	if (keyData[KEY_INPUT_RIGHT])
	{
		if (pos.x <= gameArea.x*chipSize)
		{
			tmpPos.x += chipSize;
		}
	}
	if (keyData[KEY_INPUT_LEFT])
	{
		tmpPos.x -= chipSize;
		if (tmpPos.x < 32)
		{
			tmpPos.x = 32;
		}
	}
	if (keyData[KEY_INPUT_UP])
	{
		tmpPos.y -= chipSize;
		if (tmpPos.y < 32)
		{
			tmpPos.y = 32;
		}
	}
	if (keyData[KEY_INPUT_DOWN])
	{
		if (tmpPos.y <= gameArea.y*chipSize)
		{
			tmpPos.y += chipSize;
		}
	}

	if (tmpPos != pos)
	{
		inputFlam++;
		if (inputFlam >= keyGetRng)
		{
			pos = tmpPos;
			inputFlam = 0;
			keyGetRng = keyGetRng / 2;
			if (keyGetRng < 3)
			{
				keyGetRng = 3;
			}
		}
	}
	else
	{
		inputFlam = EDIT_KEY_GET_DEF_RNG;
		keyGetRng = EDIT_KEY_GET_DEF_RNG;
	}
}