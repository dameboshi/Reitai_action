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
	static int Sx, Sy;//��ʃT�C�Y
	int Cb;//�J���[�r�b�g��
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