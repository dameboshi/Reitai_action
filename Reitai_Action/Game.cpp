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
	SetMainWindowText("Title未定");
	SetDrawScreen(DX_SCREEN_BACK);

	//フォント作成
	//largefont = CreateFontToHandle(0, 100, 9, DX_FONTTYPE_ANTIALIASING_EDGE);
	
	try{
		loadfile();					//各ファイルの読み込み
	}
	catch (int errcode){
		MessageBox(NULL, "ファイル読み込みエラー", "メッセージ", MB_OK);
		return;
	}

	SetBackgroundColor(255, 255, 255);
	GetScreenState(&Sx, &Sy, &Cb);

	setGameState(GAME_MAIN);
	maingame = new MainGame(0);

	//メインループ
	//今はエスケープで落ちるようになってるｄ
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


//---メイン部分---//
void Game::drawGameLogo(){

}
void Game::drawGameTitle(){

}
void Game::drawGameWorldMap(){

}
void Game::drawGameMain(){
	maingame->Calc();
	maingame->Draw();
	//End関数を渡してsetGameStateを呼び出す
}
void Game::drawGameOver(){

}
void Game::drawGameClear(){

}



//gstateをセットする（画面切り替え）
//同時にタイマーも初期化。
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


//MAIN関数

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Game *game = new Game();
	game->doMainLoop(TRUE);
	delete game;
}