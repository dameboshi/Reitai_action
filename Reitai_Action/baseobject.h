typedef struct _Object
{
	bool alive;
	double x, y;
	double vx, vy;
}Object;

class BaseObject{
protected:
	//ここ構造体使わなくてよくね？
	Object object;

	bool alive;
	double x, y;
	double vx, vy;

	double getX(){ return object.x; }
	double getY(){ return object.y; }
	double getVX(){ return object.x; }
	double getVY(){ return object.y; }
	bool getAlive(){ return object.alive; }
};