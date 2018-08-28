#include "Enemy.h"
#include "GameTask.h"
#include "MapCtl.h"
#include "ImageMng.h"

Enemy::Enemy()
{
	ID = CHIP_PL;
	addMove = 3;
	moveDistance = 0;
	moveLimit = 5 * lpMapCtl.GetChipSize();
	moveInv = 30;

	radius = 100;
	angle = 0;
	angSpeed = (float)0.065;
} 

Enemy::~Enemy()
{
}

void Enemy::UpData()
{
	Move();
}

bool Enemy::CollisionProcessing(void)
{
	DamageProcessing();
	ReverseMove();
	return false;
}

//c‰¡“™‚ÌˆÚ“®A§ŒÀ‚³‚ê‚½‹——£‚ği‚Ş
void Enemy::Move(void)
{
	
	if (moveDistance <= moveLimit)
	{
		moveDistance++;
		switch (mode)
		{
		case MODE_UP_DOWN:
			pos.y += addMove;
			break;

		case MODE_RIGHT_LEFT:
			pos.x += addMove;
			break;

		}
	}	
	else
	{
		moveInv = 30;
		moveDistance = 0;
		addMove *= -1;
	}
	//else if (mode == Circle)
	//{
	//	angle += angSpeed;
	//	pos.x += cos(angle) *radius;
	//	pos.y += sin(angle) *radius;
	//}
}

void Enemy::Draw(void)
{
	if (imageName.length() == 0)
	{
		return;
	}
	VECTOR2 drawOffset = GameTask::GetInstance().GetDrawOffSet();
	DrawExtendGraph(pos.x + drawOffset.x, pos.y + drawOffset.y, pos.x + drawOffset.x + size, pos.y + drawOffset.y + size, IMAGE_ID(imageName)[CHIP_DAMAGE], true);
}
