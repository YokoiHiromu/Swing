#include <DxLib.h>
#include "GameTask.h"
#include "BreakBlock.h"
#include "DamageBlock.h"
#include "SpinBall.h"
#include "ClearBlock.h"
#include "WarpBlock.h"
#include "Enemy.h"
#include "MapCtl.h"
#include "ImageMng.h"


#define VIEW_AREA_CNT_X (46)
#define VIEW_AREA_CNT_Y (34)

#define GAME_AREA_CNT_X (VIEW_AREA_CNT_X*2)
#define GAME_AREA_CNT_Y (VIEW_AREA_CNT_Y*2)
#define CHIP_SIZE		(16)
#define DRAW_OFFSET		(2)


#define ID_NAME "MAP_DATA"		// ̧�ق�ID����`
#define ID_VER 0x01					// ̧�ق��ް�ޮݔԍ�

MapCtl *MapCtl::s_Instance = nullptr;

void MapCtl::Create()
{
	if (!s_Instance)
	{
		s_Instance = new MapCtl();
	}
}

void MapCtl::Destroy()
{
	if (s_Instance)
	{
		delete s_Instance;
	}
	s_Instance = nullptr;
}

//edit��SetChip�ŌĂ΂��̂͂���
bool MapCtl::SetMapData(VECTOR2 pos, CHIP_TYPE id, int size)
{
	VECTOR2 tmpPos(pos / CHIP_SIZE);
	if (tmpPos.y >= (int)mapID.size())
	{
		return false;
	}
	if (tmpPos.x >= (int)mapID[tmpPos.y].size())
	{
		return false;
	}
	mapID[tmpPos.y][tmpPos.x] = id;
	mapSize[tmpPos.y][tmpPos.x] = size;
	return true;
}

bool MapCtl::SetMapData(VECTOR2 pos, CHIP_TYPE id, int size, ENEMY_MODE mode)
{
	VECTOR2 tmpPos(pos / CHIP_SIZE);
	if (tmpPos.y >= (int)mapID.size())
	{
		return false;
	}
	if (tmpPos.x >= (int)mapID[tmpPos.y].size())
	{
		return false;
	}
	mapID[tmpPos.y][tmpPos.x] = id;
	mapSize[tmpPos.y][tmpPos.x] = size;
	enemyMode[tmpPos.y][tmpPos.x] = mode;
	return false;
}

CHIP_TYPE MapCtl::GetMapData(VECTOR2 pos)
{
	VECTOR2 tmpPos(pos / CHIP_SIZE);
	if (tmpPos.y >= (int)mapID.size())
	{
		return CHIP_BLANK;
	}
	if (tmpPos.x >= (int)mapID[tmpPos.y].size())
	{
		return CHIP_BLANK;
	}
	return  (CHIP_TYPE)mapID[tmpPos.y][tmpPos.x];
}

//�`��ɂ͂�����p���Ă���
CHIP_TYPE MapCtl::GetMapData(int x, int y)
{
	if (y >= (int)mapID.size())
	{
		return CHIP_BLANK;
	}
	if (x >= (int)mapID[y].size())
	{
		return CHIP_BLANK;
	}
	return  (CHIP_TYPE)mapID[y][x];
}

int MapCtl::GetMapSize(int x, int y)
{
	return  (int)mapSize[y][x];
}

ENEMY_MODE MapCtl::GetEnemyMode(int x, int y)
{

	return (ENEMY_MODE)enemyMode[y][x];
}


//������map�̏����󂯎��Ɠ�����list�ɒǉ����Ă���
void MapCtl::GetMapData()
{
	auto itr = ObjList.begin();
	int count = lpGameTask.player->GetCleCnt();
	for (int y = DRAW_OFFSET; y < GAME_AREA_CNT_Y + DRAW_OFFSET; y++)
	{
		for (int x = DRAW_OFFSET; x < GAME_AREA_CNT_X + DRAW_OFFSET; x++)
		{
			if ((CHIP_TYPE)mapID[y][x] != CHIP_BLANK)
			{
				switch ((CHIP_TYPE)mapID[y][x])
				{
				case CHIP_BREAK:		//�u���Ă������̂�������ۯ��Ȃ�list�ɒǉ�
					ObjList.push_back(std::make_shared<BreakBlock>());
					break;
				case CHIP_DAMAGE:		//�u���Ă������̂����Ȃ���ۯ��Ȃ�
					ObjList.push_back(std::make_shared<DamageBlock>());
					break;
				case CHIP_SPIN:		//�u���Ă������̂��t��]��ۯ��Ȃ�
					ObjList.push_back(std::make_shared<SpinBall>());
					break;
				case CHIP_CLEAR:		//�u���Ă������̂��ر��ۯ��Ȃ�
					ObjList.push_back(std::make_shared<ClearBlock>());
					count++;
					break;
				case CHIP_ENEMY:			//���Ȃ̂ŉ摜�̎g���܂킵�A��а�Ȃ�
				case CHIP_ENEMY2:
					ObjList.push_back(std::make_shared<Enemy>());
				default:
					break;
				}
				itr++;
				VECTOR2 pos = { x * CHIP_SIZE, y * CHIP_SIZE };
				(*itr)->SetPos(pos);		//mapID�̐擪���珇�ɓ����Ă�(=itr++�Ƃ��ŕ�����Ȃ�)
				(*itr)->SetSize((int)mapSize[y][x]);
				(*itr)->SetMode((ENEMY_MODE)enemyMode[y][x]);
			}
		}
	}
	ObjList.pop_front();					//���̏ꍇ��������ϯ�߂ɐݒu���Ă��Ȃ��ƴװ(��list�ɂ�edit�݂̂��������Ă��Ȃ���)
	lpGameTask.player->SetCleCnt(count);
}

int MapCtl::GetChipSize(void)
{
	return CHIP_SIZE;
}

int MapCtl::GetDrawOffset(void)
{
	return DRAW_OFFSET;
}

bool MapCtl::MapSave()
{
	DataHeader expData = {
		ID_NAME,
		ID_VER,
	{ 0,0 },
	CHIP_SIZE,
	CHIP_SIZE,
	{ 0,0,0 },
	0x00
	};
	static OPENFILENAME     ofn;
	static TCHAR            szPath[MAX_PATH];
	static TCHAR            szFile[MAX_PATH];

	if (szPath[0] == TEXT('\0')) {
		GetCurrentDirectory(MAX_PATH, szPath);
	}
	if (ofn.lStructSize == 0) {
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = GetMainWindowHandle();
		ofn.lpstrInitialDir = szPath;			// �����t�H���_�ʒu
		ofn.lpstrFile = szFile;					// �I���t�@�C���i�[
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrDefExt = TEXT(".map");
		ofn.lpstrFilter = TEXT("IMAGE�t�@�C��(*.map)\0*.map\0");
		ofn.lpstrTitle = TEXT("�G�f�B�b�g�f�[�^��ۑ����܂��B");
		ofn.Flags = OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;
	}
	if (GetSaveFileName(&ofn)) {
		MessageBox(GetMainWindowHandle(), TEXT("�ۑ����܂���"), "", MB_OK);
		FILE *file;
		fopen_s(&file, szFile, "wb");
		fwrite(&expData, sizeof(DataHeader), 1, file);
		for (unsigned int y = 0; y < mapID.size(); y++)
		{
			fwrite(&mapID[y][0], mapID[y].size() * sizeof(unsigned int), 1, file);
			fwrite(&mapSize[y][0], mapSize[y].size() * sizeof(unsigned int), 1, file);
			fwrite(&enemyMode[y][0], enemyMode[y].size() * sizeof(unsigned int), 1, file);

		}
		fclose(file);

		return true;
	}
	else
	{
		return false;
	}
	return true;
}

bool MapCtl::MapLoad()
{
	bool rtnFlg = true;
	DataHeader expData = {
		ID_NAME,
		ID_VER,
	{ 0,0 },
	CHIP_SIZE,
	CHIP_SIZE,
	{ 0,0,0 },
	0x00
	};
	static OPENFILENAME     ofn;
	static TCHAR            szPath[MAX_PATH];
	static TCHAR            szFile[MAX_PATH];

	if (szPath[0] == TEXT('\0'))
	{
		GetCurrentDirectory(MAX_PATH, szPath);
	}
	if (ofn.lStructSize == 0)
	{
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = GetMainWindowHandle();
		ofn.lpstrInitialDir = szPath;			// �����t�H���_�ʒu
		ofn.lpstrFile = szFile;					// �I���t�@�C���i�[
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrFilter = TEXT("IMAGE�t�@�C��(*.map)\0*.map\0");
		ofn.lpstrTitle = TEXT("�G�f�B�b�g�f�[�^��I�����܂��B");
		ofn.Flags = OFN_FILEMUSTEXIST;
	}
	if (GetOpenFileName(&ofn))
	{
		MessageBox(GetMainWindowHandle(), TEXT("�G�f�B�b�g�f�[�^���J���܂���"), "", MB_OK);
		FILE *file;
		fopen_s(&file, szFile, "rb");
		fread(&expData, sizeof(DataHeader), 1, file);
		for (unsigned int y = 0; y < mapID.size(); y++)
		{
			fread(&mapID[y][0], mapID[y].size() * sizeof(unsigned int), 1, file);
			fread(&mapSize[y][0], mapSize[y].size() * sizeof(unsigned int), 1, file);
			fread(&enemyMode[y][0], enemyMode[y].size() * sizeof(unsigned int), 1, file);
		}

		fclose(file);
	}
	else
	{
		rtnFlg = false;
	}

	return rtnFlg;

}

int MapCtl::MapInit(void)
{
	return 0;
}

void MapCtl::MapDraw()
{
	VECTOR2 getOffSet = lpGameTask.GetDrawOffSet();
	for (int y = DRAW_OFFSET; y < GAME_AREA_CNT_Y + DRAW_OFFSET; y++)
	{
		for (int x = DRAW_OFFSET; x < GAME_AREA_CNT_X + DRAW_OFFSET; x++)
		{
			if (GET_MAP_ID2(x, y) != CHIP_BLANK)
			{
				int size = GET_MAP_SIZE(x, y);
				DrawExtendGraph(x*CHIP_SIZE + getOffSet.x, y*CHIP_SIZE + getOffSet.y, x*CHIP_SIZE + size + getOffSet.x, y*CHIP_SIZE + size + getOffSet.y,
					IMAGE_ID("image/tileset.png")[GET_MAP_ID2(x, y)], true);
			}
		}
	}
}

void MapCtl::MapClear()
{
	for (int y = DRAW_OFFSET; y < GAME_AREA_CNT_Y + DRAW_OFFSET; y++)
	{
		for (int x = DRAW_OFFSET; x < GAME_AREA_CNT_X + DRAW_OFFSET; x++)
		{
			mapID[y][x] = CHIP_BLANK;
			enemyMode[y][x] = MODE_UP_DOWN;
		}
	}
}

VECTOR2 MapCtl::GetViewAreaSize(void)
{
	return VECTOR2(VIEW_AREA_CNT_X, VIEW_AREA_CNT_Y);
}

VECTOR2 MapCtl::GetAreaSize(void)
{
	return VECTOR2(GAME_AREA_CNT_X, GAME_AREA_CNT_Y);
}

MapCtl::MapCtl()
{
	mapID.resize(GAME_AREA_CNT_Y + DRAW_OFFSET);
	mapSize.resize(GAME_AREA_CNT_Y + DRAW_OFFSET);
	enemyMode.resize(GAME_AREA_CNT_Y + DRAW_OFFSET);
	for (int y = 0; y < GAME_AREA_CNT_Y + DRAW_OFFSET; y++)
	{
		mapID[y].resize(GAME_AREA_CNT_X + DRAW_OFFSET);
		mapSize[y].resize(GAME_AREA_CNT_X + DRAW_OFFSET);
		enemyMode[y].resize(GAME_AREA_CNT_X + DRAW_OFFSET);
	}
	MapClear();
}


MapCtl::~MapCtl()
{
}
