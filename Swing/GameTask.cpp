#include <DxLib.h>
#include "GameTask.h"
#include "PlayerBall.h"
#include "EditCursor.h"
#include "ImageMng.h"

GameTask *GameTask::s_Instance = nullptr;

void GameTask::Create()
{
	if (s_Instance == nullptr)
	{
		s_Instance = new GameTask();
	}
}

void GameTask::Destroy()
{
	if (s_Instance)
	{
		delete s_Instance;
	}
	s_Instance = nullptr;
}

int GameTask::UpData()
{
	int rtn_id;
	rtn_id = (this->*GtskPtr)();
	memcpy(keyDataOld, keyData, sizeof(keyDataOld));
	GetHitKeyStateAll(keyData);
	return rtn_id;
}

GameTask::GameTask()
{
	GtskPtr = &GameTask::SysInit;
}

GameTask::~GameTask()
{
}

const VECTOR2 & GameTask::GetDrawOffSet(void)
{
	return{ -(camera->GetPos().x - (lpMapCtl.GetViewAreaSize().x / 2) * lpMapCtl.GetChipSize()), -(camera->GetPos().y - (lpMapCtl.GetViewAreaSize().y / 2) * lpMapCtl.GetChipSize()) };
}

int GameTask::SysInit()
{
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);		// 65536色ﾓｰﾄﾞに設定
	ChangeWindowMode(true);				// true:window　false:ﾌﾙｽｸﾘｰﾝ
	SetWindowText("制作中");
	if (DxLib_Init() == -1)
	{
		return false;	// DXﾗｲﾌﾞﾗﾘ初期化処理
	}
	SetDrawScreen(DX_SCREEN_BACK);		// ひとまずﾊﾞｯｸﾊﾞｯﾌｧに描画
	SetBackgroundColor(0, 0, 255);

	ImageMng::Create();
	MapCtl::Create();
	camera = std::make_unique<Camera>();

	GtskPtr = &GameTask::EditInit;
	return 0;
}


int GameTask::EditInit()
{
	ClsDrawScreen();
	player = new Player(keyData, keyDataOld);
	objList.clear();

	int chipSize = lpMapCtl.GetChipSize();
	//for (auto itr : objList)		//ｲﾃﾚｰﾀｰ
	objList.push_back(std::make_shared<EditCursor>(keyData, keyDataOld));
	for (auto itr = objList.begin(); itr != objList.end(); itr++)
	{
		(*itr)->Init("image/tileset.png", { chipSize, chipSize }, { 8,6 }, { 6,0 }, 0);
		camera->SetTarget((*itr));		//Editの座標取得
	}
	GtskPtr = &GameTask::EditMain;
	return 0;
}

int GameTask::EditMain()
{
	ClsDrawScreen();
	auto itr = objList.begin();
	(*itr)->UpData();
	camera->UpData();
	lpMapCtl.MapDraw();
	(*itr)->Draw();
	camera->Draw();

	if (keyData[KEY_INPUT_F1] && !keyDataOld[KEY_INPUT_F1])
	{
		if (MessageBox(GetMainWindowHandle(),
			"データをセーブしますがよろしいですか？",
			"確認ダイアログ",
			MB_OKCANCEL) == IDOK)
		lpMapCtl.MapSave();
	}
	if (keyData[KEY_INPUT_F2] && !keyDataOld[KEY_INPUT_F2])
	{
		if (MessageBox(GetMainWindowHandle(),
			"データをロードしますがよろしいですか？",
			"確認ダイアログ",
			MB_OKCANCEL) == IDOK)
		lpMapCtl.MapLoad();
	}

	if (keyData[KEY_INPUT_F4] && !keyDataOld[KEY_INPUT_F4])
	{
		lpMapCtl.MapClear();
		(*itr)->RandomSetChipID();
	}

	int chipSize = lpMapCtl.GetChipSize();
	for (int i = 0; i < SCREEN_SIZE_X / chipSize - 3; i++)
	{
		DrawLine((i * chipSize) + (chipSize * 2), 0 + (chipSize * 2), (i * chipSize) + (chipSize * 2), SCREEN_SIZE_Y - 24, 0xffffff, true);
	}
	for (int j = 0; j < SCREEN_SIZE_Y / chipSize - 2; j++)
	{
		DrawLine(0 + (chipSize * 2), (j * chipSize) + (chipSize * 2), SCREEN_SIZE_X - (chipSize * 2), (j * chipSize) + (chipSize * 2), 0xffffff, true);
	}
	ScreenFlip();

	//GameModeに移行しつつlistに追加していく
	if (keyData[KEY_INPUT_F5] && !keyDataOld[KEY_INPUT_F5])
	{
		lpMapCtl.GetMapData();
		for (auto itr = objList.begin(); itr != objList.end(); itr++)
		{
			CHIP_TYPE id = (*itr)->GetID();
			(*itr)->Init("image/tileset.png", { chipSize, chipSize }, { 8,6 }, { id,0 }, 0);
		}
		//GtskPtr = &GameTask::GameTitle;
		GtskPtr = &GameTask::GameInit;
	}
	return 0;
}

int GameTask::GameTitle()
{
	ClsDrawScreen();
	DrawString(0, 0, "space押して", 0, true);
	if (keyData[KEY_INPUT_SPACE] && keyDataOld[KEY_INPUT_SPACE])
	{
		GtskPtr = &GameTask::GameInit;
	}
	ScreenFlip();
	return 0;
}

int GameTask::GameInit()
{
	GtskPtr = &GameTask::GameMain;
	return 0;
}

int GameTask::GameMain()
{
	ClsDrawScreen();
	for (auto itr = objList.begin(); itr != objList.end(); itr++)
	{
		(*itr)->UpData();
		(*itr)->Draw();
	}
	player->UpData();
	camera->UpDataPL();
	player->Draw();
	ScreenFlip();

	if (keyData[KEY_INPUT_F5] && !keyDataOld[KEY_INPUT_F5])		//完成したら戻れないように消す
	{
		lpMapCtl.MapClear();
		GtskPtr = &GameTask::EditInit;
	}
	// (player->FailChack())
	//{
	//	GtskPtr = &GameTask::GameOver;
	//}
	//if (player->ClearChack())
	//{
	//	GtskPtr = &GameTask::GameClear;		//Editにはもどれないように(予定)
	//}
	return 0;
}

int GameTask::GameClear()
{
	ClsDrawScreen();
	SetBackgroundColor(255, 255, 255);
	ScreenFlip();
	if (keyData[KEY_INPUT_F5] && !keyDataOld[KEY_INPUT_F5])
	{
		lpMapCtl.MapClear();
		GtskPtr = &GameTask::EditInit;
		SetBackgroundColor(0, 0, 255);
	}
	return 0;
}

int GameTask::GameOver()
{
	ClsDrawScreen();
	SetBackgroundColor(0, 0, 0);
	ScreenFlip();
	if (keyData[KEY_INPUT_F5] && !keyDataOld[KEY_INPUT_F5])
	{
		lpMapCtl.MapClear();
		GtskPtr = &GameTask::EditInit;
		SetBackgroundColor(0, 0, 255);
	}
	return 0;
}

int GameTask::EditDestroy()
{
	return 0;
}

int GameTask::GameDestroy()
{
	return 0;
}

int GameTask::SysDestroy()
{
	return 0;
}