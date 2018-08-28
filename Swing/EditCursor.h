#pragma once
#include "Obj.h"
#include "VECTOR2.h"
#include "MapCtl.h"

#define EDIT_KEY_GET_DEF_RNG (30)

class EditCursor :
	public Obj
{
public:
	EditCursor(char(&_keyData)[256], char(&_keyDataOld)[256]);
	~EditCursor();

	void UpData(void);
	void Draw(void);

	void RandomSetChipID(void);

private:
	bool SetChipID(void);
	void Move(void);

	unsigned int keyGetRng;
	unsigned int inputFlam;

	unsigned int keyGetRng_S;
	unsigned int inputFlam_S;

	char(&keyData)[256];
	char(&keyDataOld)[256];

	CHIP_TYPE nowID;
};