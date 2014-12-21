#include "maingame.h"
#include "player.h"
#include "map.h"

MAP *nowMap;
Player *player;
Camera camera;

MainGame::MainGame(int sn){
	stagenumber = sn;
	try{
	    nowMap = new MAP(stagenumber);//ステージ番号を渡す
	}
	catch (int errcode){
		MessageBox(NULL, "ファイル読み込みエラー", "メッセージ", MB_OK);
		return;
	}
	player = new Player();
	Init();
}

void MainGame::Calc(){
	player->Calc();

	BaseState::Calc();
	camera.ScrollMove(player->getX()-nowMap->getFirstX(), player->getY()-nowMap->getFirstY());
}

void MainGame::Init(){
	player->Init(nowMap->getFirstX(), nowMap->getFirstY());
}

void MainGame::Draw(){
	nowMap->Draw(camera.scrollx, camera.scrolly);
	DrawFormatString(0, 20, BLACK, "width = %d,height = %d ", nowMap->getWidth(), nowMap->getHeight());
	DrawFormatString(0, 40, BLACK, "first_x = %d,first_y = %d ", nowMap->getFirstX(), nowMap->getFirstY());
	player->Draw(camera.scrollx,camera.scrolly);
	//printfDx("x = %f.0,y = %f.0 \n",player->getX(),player->getY());
	DrawFormatString(0, 0, BLACK, "x = %.0f,y = %.0f \n", player->getX(), player->getY());
}

void MainGame::Load(){

}

int MainGame::End(){
	if (1)return 0;
}
