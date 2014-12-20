class BaseState{
protected:
	int timer;
public:
	BaseState(){
		timer = 0;
	}
	void Init();
	void Calc();
	void Draw();
	void Load();
};