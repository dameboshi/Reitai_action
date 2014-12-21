#include "DxLib.h"
#include "game.h"

const int BLACK = GetColor(0, 0, 0);
const int RED = GetColor(255, 0, 0);
const int WHITE = GetColor(255, 255, 255);

class Camera{
public:
	Camera(){
		scrollx = 0;
		scrolly = 0;
	}
	int scrollx;
	int scrolly;

	void ScrollMove(int x, int y){
		scrollx = x - 320;
		scrolly = y;
		if (scrollx < 0)scrollx = 0;
	}
};

extern Camera camera;