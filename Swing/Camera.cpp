#include "Camera.h"
#include "MapCtl.h"
#include "ImageMng.h"
#include "GameTask.h"

Camera::Camera()
{
	pos = { 0,0 };
}

Camera::~Camera()
{
}

//ｴﾃﾞｨｯﾄ用のUpData
void Camera::UpData(void)
{
	if (target.expired())
	{
		return;
	}
	VECTOR2 tmpPos = target.lock()->GetPos();

	if (tmpPos.x >= antiMoveRect.left && tmpPos.x < antiMoveRect.right)
	{
		pos.x = tmpPos.x;
	}
	if (tmpPos.y >= antiMoveRect.top && tmpPos.y < antiMoveRect.bottom)
	{
		pos.y = tmpPos.y;
	}
}

//ｹﾞｰﾑ中、ﾌﾟﾚｲﾔｰ追従のUpData
void Camera::UpDataPL(void)
{
	VECTOR2 gameArea = MapCtl::GetInstance().GetAreaSize();
	VECTOR2 viewArea = MapCtl::GetInstance().GetViewAreaSize();
	int chipSize = MapCtl::GetInstance().GetChipSize();
	VECTOR2 tmpPos = targetPL.GetPos();
	if (tmpPos.x >= antiMoveRect.left && tmpPos.x < antiMoveRect.right)
	{
		//ｶﾒﾗの追従(x)を一定距離で行う、細かい修正は必要だが大まかにはok
		now.x = (tmpPos.x / (viewArea.x / 3 * chipSize));
		if (now.x != old.x)
		{
			pos.x = tmpPos.x;
		}
		old.x = now.x;

	}
	else
	{
		//xが左のの限界を超えたら
		if (tmpPos.x < antiMoveRect.left)
		{
			pos.x = viewArea.x / 2 * chipSize;
		}
		//xが右のの限界を超えたら
		else if (tmpPos.x > antiMoveRect.right)
		{
			pos.x = 1104;
		}
	}

	if (tmpPos.y >= antiMoveRect.top && tmpPos.y < antiMoveRect.bottom)
	{
		//ｶﾒﾗの追従(y)を一定距離で行う、細かい修正は必要だが大まかにはok
		now.y = (tmpPos.y / (viewArea.x / 3 * chipSize));
		if (now.y != old.y)
		{
			pos.y = tmpPos.y;
		}
		old.y = now.y;
	}
	else
	{
		//yが上の限界を超えたら
		if (tmpPos.y < antiMoveRect.top)
		{
			pos.y = viewArea.y / 2 * chipSize;
		}
		//yが下の限界を超えたら
		else if (tmpPos.y > antiMoveRect.bottom)
		{
			pos.y = 900 - 84;
		}
	}
	if (vibFlag && !vibFlagOld)
	{
		DamageVib();
	}
	vibFlagOld = vibFlag;
}

VECTOR2 &Camera::GetPos(void)
{
	return pos;
}

bool Camera::SetPos(VECTOR2 pos)
{
	this->pos = pos;

	return true;
}

bool Camera::SetPos(int x, int y)
{
	pos = { x,y };
	return true;
}

bool Camera::SetTarget(std::weak_ptr<Obj> target)
{
	this->target	 = target;
	VECTOR2 viewArea = MapCtl::GetInstance().GetViewAreaSize();
	VECTOR2 gameArea = MapCtl::GetInstance().GetAreaSize();
	int chipSize	 = MapCtl::GetInstance().GetChipSize();
	VECTOR2 tmpPos   = (viewArea / 2)*chipSize;

	antiMoveRect = { tmpPos.x,tmpPos.y,((gameArea.x+1)*chipSize - tmpPos.x), ((gameArea.y+1)*chipSize - tmpPos.y) };

	return true;
}

bool Camera::SetTarget(PlayerBall target)
{
	this->targetPL = target;
	VECTOR2 viewArea = MapCtl::GetInstance().GetViewAreaSize();
	VECTOR2 gameArea = MapCtl::GetInstance().GetAreaSize();
	int chipSize = MapCtl::GetInstance().GetChipSize();
	VECTOR2 tmpPos = (viewArea / 2)*chipSize;

	antiMoveRect = { tmpPos.x,tmpPos.y,((gameArea.x + 1)*chipSize - tmpPos.x), ((gameArea.y + 1)*chipSize - tmpPos.y) };

	return true;
}

bool Camera::SetVibFlag(bool vibFlag)
{
	this->vibFlag = vibFlag;
	return true;
}

void Camera::Draw(void)
{
	int chipSize = MapCtl::GetInstance().GetChipSize();
	VECTOR2 viewArea = MapCtl::GetInstance().GetViewAreaSize();
	//DrawLine(chipSize + 8, chipSize * 6, (viewArea.x - 8)*chipSize, (viewArea.y - 6)*chipSize)

	DrawGraph(pos.x, pos.y, IMAGE_ID("image/tileset.png")[CHIP_PL], true);
}

void Camera::DamageVib(void)
{
	//int vibTime = 0;
	//for (vibTime; vibTime <= 30; vibTime++)
	//{
	//	pos.x += vibTime;
	//}
}
