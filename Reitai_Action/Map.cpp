#include "map.h"
#include "DxLib.h"
#include "common.h"
#include <math.h>

MAP::MAP(int stagenumber)throw(int)
{
	//ロードを行う
	//渡されたステージ番号からマップデータを読み込む
	//ついでにマップの広さ、制限時間も読み込む？
	//主人公の初期位置なんかも欲しいかも

	//マップの初期化
	for (int i = 0; i < MAP_MAXWIDTH; i++)
	{
		for (int j = 0; j < MAP_MAXHEIGHT; j++){
			mapdata[j][i] = 0;
		}
	}

	char buf[MAP_MAXWIDTH];
	int height_buf;//高さの一時保存場所
	int filehandle;

	if (stagenumber != -1){
		filehandle = FileRead_open("map.txt");
		if (filehandle == 0)throw(-1);
	}

	//ファイル読み込み場所をずらす
	FileRead_gets(buf, 4, filehandle);
	height_buf = atoi(buf);
    for (int i = 0; i < stagenumber; i++){
		FileRead_seek(filehandle, height_buf + 4 + 1, SEEK_CUR);//高さ広さ、初期位置の分、マップ高さ、空白の分をずらす
		FileRead_gets(buf, 4, filehandle);
		height_buf = atoi(buf);
	}

	//マップの幅と高さの読み込み
	//FileRead_gets(buf, MAP_MAXHEIGHT, filehandle);
	//height = atoi(buf) * MAP_SIZE;
	height = height_buf * MAP_SIZE;
	FileRead_gets(buf, MAP_MAXWIDTH, filehandle);
	width = atoi(buf) * MAP_SIZE;

	//主人公の初期位置の読み込み
	FileRead_gets(buf, 4, filehandle);
	first_x = atoi(buf) * MAP_SIZE;
	FileRead_gets(buf, 4, filehandle);
	first_y = atoi(buf) * MAP_SIZE;

	
	for (int i = 0; i < height/MAP_SIZE; i++)
	{
		FileRead_gets(buf, width/MAP_SIZE+1, filehandle);
		for (int j = 0; j < width/MAP_SIZE; j++){
			mapdata[j][i] = buf[j] - '0';
		}
	}
	
	FileRead_close(filehandle);
	
	/*
	for (int i = 0; i < height / MAP_SIZE; i++)
	{
		for (int j = 0; j < width / MAP_SIZE; j++){
			printfDx("%d", mapdata[j][i]);
		}
		printfDx("\n");
	}
	*/
	//デバッグ用
	/*
	first_x = 100;
	first_y = 100;
	width = MAP_MAXWIDTH;
	height = 480;
	*/

}

MAP::~MAP()
{
}

void MAP::Load(int stagenumber){
}

void MAP::Draw(int sx,int sy){

	for (int i = 0; i < height/MAP_SIZE; i++){
		for (int j = 0; j < width/MAP_SIZE; j++){
			switch (mapdata[j][i])
			{
			case 0:
				break;
			case 1:
				DrawBox(j * MAP_SIZE -sx, i * MAP_SIZE, j * MAP_SIZE + MAP_SIZE -sx, i * MAP_SIZE + MAP_SIZE, BLACK, FALSE);
				break;
			default:
				break;
			}
		}
	}
}


int MAP::getMapdata(int i, int j){
	return mapdata[i/32][j/32];
}