#define MAP_MAXHEIGHT 100
#define MAP_MAXWIDTH 600
#define MAP_SIZE 32

class MAP
{
public:
	MAP(int st)throw(int);
	~MAP();
	void Init();
	void Draw();
	void Load(int st)throw(int);
	int getWidth(){ return width; };
	int getHeight(){ return height; };
	int getLimittime(){ return limit_time; };
	int getFirstX(){ return first_x; };
	int getFirstY(){ return first_y; };
	int getMapdata(int, int);
private:
	int width, height;
	int limit_time;
	int first_x, first_y;
	int mapdata[MAP_MAXHEIGHT][MAP_MAXWIDTH];
};

extern MAP *nowMap;