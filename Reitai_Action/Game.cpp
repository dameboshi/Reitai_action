#include "DxLib.h"
#include "game.h"
#include "key.h"
#include "maingame.h"

MainGame *maingame;
int Game::Sx;
int Game::Sy;

void Game::doMainLoop(int scmode){
	ChangeWindowMode(scmode);
	if (DxLib_Init() == -1)return;
	SetMainWindowText("Title����");
	SetDrawScreen(DX_SCREEN_BACK);

	//�t�H���g�쐬
	//largefont = CreateFontToHandle(0, 100, 9, DX_FONTTYPE_ANTIALIASING_EDGE);
	
	try{
		loadfile();					//�e�t�@�C���̓ǂݍ���
	}
	catch (int errcode){
		MessageBox(NULL, "�t�@�C���ǂݍ��݃G���[", "���b�Z�[�W", MB_OK);
		return;
	}

	SetBackgroundColor(255, 255, 255);
	GetScreenState(&Sx, &Sy, &Cb);

	setGameState(GAME_MAIN);
	maingame = new MainGame(0);

	//���C�����[�v
	//���̓G�X�P�[�v�ŗ�����悤�ɂȂ��Ă還
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		_pad.PadInput(DX_INPUT_KEY_PAD1);

		ClsDrawScreen();
		switch (nowstate)
		{
		case GAME_LOGO:
			drawGameLogo();
			break;
		case GAME_TITLE:
			drawGameTitle();
			break;
		case GAME_WORLDMAP:
			drawGameWorldMap();
			break;
		case GAME_MAIN:
			drawGameMain();
			break;
		case GAME_OVER:
			drawGameOver();
			break;
		case GAME_CLEAR:
			drawGameClear();
			break;
		default:
			break;
		}

		ScreenFlip();
		timer++;
		//animcounter++;
	}

	DxLib_End();
}


//---���C������---//
void Game::drawGameLogo(){

}
void Game::drawGameTitle(){

}
void Game::drawGameWorldMap(){

}
void Game::drawGameMain(){
	maingame->Calc();
	maingame->Draw();
	//End�֐���n����setGameState���Ăяo��
}
void Game::drawGameOver(){

}
void Game::drawGameClear(){

}



//gstate���Z�b�g����i��ʐ؂�ւ��j
//�����Ƀ^�C�}�[���������B
GAMESTATE Game::setGameState(GAMESTATE state){
	if (nowstate != state){
		nowstate = state;
		timer = 0;
		if (nowstate == GAME_MAIN){} //Initstage();	
	}
	return nowstate;
}

void Game::loadfile()throw(int){

}


//MAIN�֐�

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Game *game = new Game();
	game->doMainLoop(TRUE);
	delete game;
}