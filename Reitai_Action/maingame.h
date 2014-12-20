#include "basestate.h"

enum STAGENUMBER{
	s1_1,
	s1_2,
	s1_3,
	s1_4,
	s1_5,
	s1_b,
};

class MainGame : public BaseState{
private:
	int stagenumber;
	int limit_time;
public:
	MainGame(int sn);
	void Init();
	void Calc();
	void Draw();
	void Load();
	int End();
};