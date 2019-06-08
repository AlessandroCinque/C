#ifndef LDD_H
#define LDD_H

extern OBJ_ATTR obj_buffer[128];
extern OBJ_AFFINE *obj_aff_buffer;

#define NUMBER_OF_ZOMBIES 6
#define NUMBER_OF_BOXES 4
#define NUMBER_OF_SCORES 5

void Reset();
void Update();
void InitSprites();
void InitSpawns(int AmmoNumber);


bool Collision(int x, int y);
bool ZCollision(int x, int y, int zX, int zY);
bool AABBCollision(int x,int y, int sizeX, int sizeY, int x2,int y2, int sizeX2, int sizeY2);


typedef struct Ammo
{
	int x;
	int y;
	int width;
	int height;
	bool active; //You don`t have to set it in the "LDD.c" file, cause always strat from false
	u32 tid;
	u32 pb;
	OBJ_ATTR *sprite;
	
} Ammo;

typedef struct Zombies
{
	int x;
	int y;
	int width;
	int height;
	bool active; //You don`t have to set it in the "LDD.c" file, cause always strat from false
	u32 tid;
	u32 pb;
	OBJ_ATTR *sprite;
	int path[100];
	int startX;
	int startY;
	int cur_Step;
	int Count_Step;
	
} Zombies;

typedef struct ScoreS
{
	int Score;
	int Temp_data;
	int Actual_score;
} ScoreS;



extern Zombies _z[NUMBER_OF_ZOMBIES];
//extern int current_state;

bool InitAmmo(int X, int Y, int Width, int Height, u32 tid, u32 pb, int obj_number);
void InitZombie(int X, int Y, int Width, int Height, u32 tid, u32 pb, int obj_number, int indexBuffer);

#endif 