#include <DxLib.h>
#include <math.h>
#include "VECTOR2.h"
#include "Obj.h"
#include "GameTask.h"
#include "Player.h"
#include "ImageMng.h"
#include "Camera.h"

Obj::Obj()
{
}

Obj::~Obj()
{
}

void Obj::Init(std::string filename, VECTOR2 divSize, VECTOR2 divCnt, VECTOR2 chipOffset, int speed)
{
	lpImageMng->GetID(filename, divSize, divCnt, chipOffset);// GetID(filename, divSize, divCnt, chipOffSet);
	imageName = filename;

	this->divSize = divSize;
	this->divCnt = divCnt;
	this->chipOffset = chipOffset;
}

bool Obj::CollisionChack_Circle_Circle(VECTOR2 cirPos, int PlSize)
{
	int radius1 = (size / 2);
	int radius2 = (PlSize / 2);
	VECTOR2 pos1 = (pos + (size / 2));
	VECTOR2 pos2 = (cirPos + (PlSize / 2));
	if ((abs(pos1.x - pos2.x) * abs(pos1.x - pos2.x)) + (abs(pos1.y - pos2.y) * abs(pos1.y - pos2.y))
		<= ((radius1 + radius2) * (radius1 + radius2)))
	{
		//PlayerBall‚Ì»²½Þ‚ªŒÄ‚Ño‚µ‚½Žq‚Ì»²½Þ‚æ‚è‘å‚«‚¢‚Æ‚«
		if (size <= PlSize || ID != CHIP_BREAK)
		{
			return true;
		}
		else if (size > PlSize)
		{
			DamageProcessing();		//ÌÞÛ¯¸‚ª‰ó‚ê‚¸‚ÉÀÞÒ°¼Þ‚ðŽó‚¯‚é
			ReverseMove();
		}
	}
	return false;
}

void Obj::DamageProcessing()
{
	if (!(lpGameTask.player->GetState()))
	{
		int playerLife = lpGameTask.player->GetLife();
		playerLife--;
		lpGameTask.player->SetLife(playerLife);
		DamageFlag = true;
		lpGameTask.camera->DamageVib();
	}
}

VECTOR2 Obj::GetPos()
{
	return pos;
}

int Obj::GetSize()
{
	return size;
}

bool Obj::GetDFlag()
{
	return DamageFlag;
}

CHIP_TYPE Obj::GetID()
{
	return ID;
}

void Obj::SetPos(const VECTOR2 & pos)
{
	this->pos = pos;
}

void Obj::SetSize(const int & size)
{
	this->size = size;
}

void Obj::SetMode(const ENEMY_MODE & mode)
{
	this->mode = mode;
}

void Obj::Draw(void)
{
	if (imageName.length() == 0)
	{
		return;
	}
	VECTOR2 drawOffset = GameTask::GetInstance().GetDrawOffSet();
	DrawExtendGraph(pos.x + drawOffset.x, pos.y + drawOffset.y, pos.x + drawOffset.x + size, pos.y + drawOffset.y + size, IMAGE_ID(imageName)[(chipOffset.x + chipOffset.y*divCnt.x)], true);
}

void Obj::Draw(unsigned int id)
{
	if (IMAGE_ID(imageName).size() <= id)
	{
		return;
	}
	//DrawGraph(pos.x , pos.y , IMAGE_ID(imageName)[id], true);
	VECTOR2 drawOffset = GameTask::GetInstance().GetDrawOffSet();
	DrawExtendGraph(pos.x + drawOffset.x, pos.y + drawOffset.y, pos.x + drawOffset.x + size, pos.y + drawOffset.y + size, IMAGE_ID(imageName)[id], true);
}
void Obj::UpData(void)
{

}

bool Obj::CollisionProcessing()
{
	return false;
}

void Obj::Move()
{
}

void Obj::ReverseMove(void)
{
	float angSpeed = lpGameTask.player->GetAngSpeed();
	lpGameTask.player->SetAngSpeed(angSpeed *= -1);
}

void Obj::RandomSetChipID()
{
}