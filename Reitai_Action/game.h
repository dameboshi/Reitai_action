enum GAMESTATE{
	GAME_LOGO,
	GAME_TITLE,
	GAME_WORLDMAP,
	GAME_MAIN,
	GAME_OVER,
	GAME_CLEAR,
};

class Game{
private:
	static int Sx, Sy;//画面サイズ
	int Cb;//カラービット数
	int timer;

	void drawGameLogo();
	void drawGameTitle();
	void drawGameWorldMap();
	void drawGameMain();
	void drawGameClear();
	void drawGameOver();

	GAMESTATE nowstate;
	GAMESTATE setGameState(GAMESTATE);
public:
	void doMainLoop(int);
	void loadfile()throw(int);
	static int getSx(){ return Sx; };
	static int getSy(){ return Sy; };
};