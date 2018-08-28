#include <DxLib.h>
#include "GameTask.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	GameTask::Create();
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) != 1)
	{
		GameTask::GetInstance().UpData();
	}
	GameTask::GetInstance().Destroy();
	DxLib_End();
	return 0;
}