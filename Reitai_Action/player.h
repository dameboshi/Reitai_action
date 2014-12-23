#include "baseobject.h"
#include "common.h"

enum PLAYERSTATE{
	WALK,
	RUN,
	JUMP,
	CATCH,
};

class Player : public BaseObject{
private:
	const int size = 32;
	int state;
	int direction;//0が右、1が左
	int jump_count;
	bool jump_flag;
	bool onGround;//0が地上、1が空
	int px, py;
	int dx, dy;
public:
	Player();
	~Player();
	void Init(int,int);
	void Calc();
	void Draw(int,int);
	double getX(){ return x; };
	double getY(){ return y; };
};