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
	int direction;//0���E�A1����
	int jump_count;
	bool jump_flag;
	bool onGround;//0���n��A1����
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