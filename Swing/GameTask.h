#pragma once
#include <memory>
#include <list>
#include "Obj.h"
#include "Player.h"
#include "Camera.h"

#define SCREEN_SIZE_X		800
#define SCREEN_SIZE_Y		600		//å„ÅXïœçX

typedef std::shared_ptr<Obj> obj_ptr;
typedef std::list<obj_ptr> obj_List;

#define lpGameTask	  (GameTask::GetInstance())
#define ObjList		  (lpGameTask.objList)

class GameTask
{
public:
	static void Create();
	static void Destroy();
	static GameTask &GetInstance()
	{
		Create();
		return *s_Instance;
	}
	int UpData();

	const VECTOR2 & GetDrawOffSet(void);

	char keyData[256];
	char keyDataOld[256];
	Player *player;
	obj_List objList;
	std::unique_ptr<Camera> camera;

private:
	GameTask();
	~GameTask();
	int SysInit();
	int EditInit();
	int EditMain();
	int GameTitle();
	int EditDestroy();
	int GameInit();
	int GameMain();
	int GameDestroy();
	int SysDestroy();
	int GameClear();
	int GameOver();
	int (GameTask::*GtskPtr)(void);

	static GameTask *s_Instance;
};