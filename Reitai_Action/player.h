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
	int direction;//0‚ª‰EA1‚ª¶
	int jump_count;
	bool jump_flag;
	int px, py;
	int dx, dy;
public:
	Player();
	~Player();
	void Init(int,int);
	void Calc();
	void Draw();
	double getX(){ return x; };
	double getY(){ return y; };
};