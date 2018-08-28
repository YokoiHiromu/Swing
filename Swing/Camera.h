#pragma once
#include <memory>
#include <DxLib.h>
#include "Obj.h"
#include "PlayerBall.h"
#include "VECTOR2.h"

class Camera
{
public:
	Camera();
	~Camera();
	void UpData(void);
	void UpDataPL(void);
	VECTOR2 &GetPos(void);
	bool SetPos(VECTOR2 pos);
	bool SetPos(int x, int y);
	bool SetTarget(std::weak_ptr<Obj> target);
	bool SetTarget(PlayerBall target);
	bool SetVibFlag(bool vibFlag);
	void Draw(void);

	void DamageVib(void);
	

private:
	VECTOR2 pos;
	std::weak_ptr<Obj> target;
	PlayerBall targetPL;
	RECT antiMoveRect;

	VECTOR2 now = { 0, 0 };
	VECTOR2 old = { 99, 99 };

	bool vibFlag = false;
	bool vibFlagOld = false;
};