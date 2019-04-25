//
//! \file hello_demo.c
//!   Screen-entry text demo
//! \date 20060228 - 20080416
//! \author cearn
//
// === NOTES ===
#include <string.h>
#include <stdio.h>
#include <tonc.h>

#include "Z.h"
#include "ZV.h"
#include "LDD.h"
#include "SpriteV.h"
#include "BGV.h"
#include "BG.h"
#include "Sprite.h"
#include "functions.h"
#include <time.h>
#include <stdlib.h>
#include "AmmoBox.h"
#include "AmmoBoxBM.h"

OBJ_ATTR obj_buffer[128];
OBJ_AFFINE *obj_aff_buffer= (OBJ_AFFINE*)obj_buffer;



//=====================================  Player =======================================
int player_x = 0, player_y = 0;
u32 tid= 0, pb= 1;	
OBJ_ATTR *ZV= &obj_buffer[0];
	
//=========================   ZOMBIES    ===========================

Zombies _z[NUMBER_OF_ZOMBIES];

//=================Look at the difference between the "Structure format" and the normal one
Ammo _ammo[NUMBER_OF_BOXES];

//===================================== Tools =====================================


int current_state = 0;
int menuSelection = 0;
int FrmCount = 0;


//===================================== Information =====================================


int AmmoLeft = 0;
int LifesLeft = 3;
int Score = 0;
int TopScore = 0;
int _topscores[NUMBER_OF_SCORES];



//===================================== Function Declaration =====================================


void Update();

//============================== Scores ================================
void CalculateScoreS()
{
	int s;
	int temp = 0;
	
	for (s = 0; s < NUMBER_OF_SCORES; s++)
	{
	//This is for sort the scores!!!!!
		if(_topscores[s] < Score)
		{
			temp = _topscores[s];
			_topscores[s] = Score;
			Score = temp;
		}
	}
}
//==============================  Initialise the Ammo in the ARRAY  ==============================



bool InitAmmo(int X, int Y, int Width, int Height, u32 tid, u32 pb, int obj_number)
{
	int x;
	for (x = 0; x < NUMBER_OF_BOXES; x++)
	{
		_ammo[x].x = X + x*10;
		_ammo[x].y = Y;
		_ammo[x].width = Width;
		_ammo[x].height = Height;
		_ammo[x].active = false;
		_ammo[x].tid = tid;
		_ammo[x].pb = pb;
		_ammo[x].sprite = &obj_buffer[obj_number+x];
		
		//The "x" inside "InitSpawns(x)" is automaticaly linked to what is inside the brackets in "void InitSpawns(int AmmoNumber)"
		InitSpawns(x);
	}
	return true;
}
//================================= Ammo Spawns ==================
void InitSpawns(int AmmoNumber)
{
	
	int Position =rand()%10;
	//int Position =8;
	
	
	switch(Position)
	{
		case 0:
		/*Cause that "x" in "InitSpawns(x)" has been recalled by "int AmmoNumber" we can put "int AmmoNumber"
		and that will be read by the computer as the same "x" that you used for the array.
		*/
		_ammo[AmmoNumber].x = 50;
		_ammo[AmmoNumber].y = 70;
		break;
		
		case 1:
		_ammo[AmmoNumber].x = 200;
		_ammo[AmmoNumber].y = 10;
		break;
		
		case 2:
		_ammo[AmmoNumber].x = 80;
	    _ammo[AmmoNumber].y = 120;
		
		break;
		
		case 3:
		_ammo[AmmoNumber].x = 20;
		_ammo[AmmoNumber].y = 130;
		break;
		
		case 4:
		_ammo[AmmoNumber].x = 104;
	    _ammo[AmmoNumber].y = 80;
		break;
		
		case 5:
		_ammo[AmmoNumber].x = 160;
		_ammo[AmmoNumber].y = 100;
		break;
		
		case 6:
		_ammo[AmmoNumber].x = 220;
        _ammo[AmmoNumber].y = 30;
		break;
		
		case 7:
		_ammo[AmmoNumber].x = 127;
        _ammo[AmmoNumber].y = 130;
		break;
		
		case 8:
		_ammo[AmmoNumber].x = 220;
        _ammo[AmmoNumber].y = 150;
		break;
		
		case 9:
		_ammo[AmmoNumber].x = 230;
        _ammo[AmmoNumber].y = 70;
		break;
		default:
		_ammo[AmmoNumber].x = 152;
        _ammo[AmmoNumber].y = 232;
		
	}   
}       
//================================= Init Zombies in the ARRAY =====================================



void InitZombie(int X, int Y, int Width, int Height, u32 tid, u32 pb, int obj_number, int indexBuffer)
{
	_z[obj_number].x =  X;
	_z[obj_number].y = Y;
	_z[obj_number].width = Width;
	_z[obj_number].height = Height;
	_z[obj_number].active = false;
	_z[obj_number].tid = tid;
	_z[obj_number].pb = pb;
	_z[obj_number].sprite = &obj_buffer[indexBuffer];
	
	_z[obj_number].startX = X;
	_z[obj_number].startY = Y;
	_z[obj_number].cur_Step = 0;
	_z[obj_number].Count_Step = 0;
}



//==================================== RESET =====================================================
void Reset()
{
	LifesLeft = 3;

	Score = 0;
	InitAmmo(40, 20, 8,  8, 2, 0, 2);

}
//=================================================================================================



void InitSprites()
{

	obj_set_attr(ZV, 
		ATTR0_TALL,										// Tall, regular sprite
		ATTR1_SIZE_8,									// 8x16p, 
		ATTR2_PALBANK(pb) | tid);						// palbank 0, tile 0
	
//=================Look at the difference between the "Structure format" and the normal one====
	
	int x;
	for (x = 0; x < NUMBER_OF_BOXES; x++)
	{
		obj_set_attr(_ammo[x].sprite, 
			ATTR0_SQUARE,									// Square, regular sprite
			ATTR1_SIZE_8,									// 8x8p, 
			ATTR2_PALBANK(_ammo[x].pb) | _ammo[x].tid);	// palbank 0, tile 0
	}		
//========================================== Zombies =====================================================
	int z;
	for (z = 0; z < NUMBER_OF_ZOMBIES; z++)
	{
		obj_set_attr(_z[z].sprite, 
			ATTR0_TALL,									// Tall, regular sprite
			ATTR1_SIZE_8,									// 8x16p, 
			ATTR2_PALBANK(_z[z].pb) | _z[z].tid);
	}
}
//=================================================================================================



bool Collision(int x, int y)
{

//====================================== Per Pixel for the Background ===============================

	int sprite_x,sprite_y;
	for(sprite_x =0; sprite_x<8; sprite_x++)
	{
		for(sprite_y =0; sprite_y<16; sprite_y++)
		{
			if((SpriteBitmap[sprite_x+sprite_y*8])&&(BGBitmap[(sprite_x+x)+(sprite_y+y)*256]))
			{
				return true;
			}
		}
	}
	
	return false;
}
//=================================================================================================

bool AABBCollision(int x,int y, int sizeX, int sizeY, int x2,int y2, int sizeX2, int sizeY2)
{
	//===================================================== TOP LEFT:
	int TopLeft_CornerX = x;
	int TopLeft_CornerY = y;
	
	
	if	   (TopLeft_CornerX >= x2 && TopLeft_CornerX <= (x2 + sizeX2)) //...Checking if the oject CORNER is between Player Left AND Right corner.
	{                                    
		if (TopLeft_CornerY >= y2 && TopLeft_CornerY <= (y2 + sizeY2)) //...Checking if the oject CORNER is between Player Top AND Bottom corner.                                  
		{
			return true; //Mean that is colliding
		}
	}
	
	//===================================================== TOP RIGHT:
	int TopRight_CornerX = x + sizeX;
	int TopRight_CornerY = y;

	if	   (TopRight_CornerX >= x2 && TopRight_CornerX <= (x2 + sizeX2)) //...Checking if the oject CORNER is between Player Left AND Right corner.
	{
		if (TopRight_CornerY >= y2 && TopRight_CornerY <= (y2 + sizeY2)) //...Checking if the oject CORNER is between Player Top AND Bottom corner.  
		{
			return true;
		}
	}
	
	//===================================================== BOTTOM LEFT:
	int BottomLeft_CornerX = x;
	int BottomLeft_CornerY = y + sizeY;
	
	
	if     (BottomLeft_CornerX >= x2 && BottomLeft_CornerX <= (x2 + sizeX2)) //...Checking if the oject CORNER is between Player Left AND Right corner.
	{
		if (BottomLeft_CornerY >= y2 && BottomLeft_CornerY <= (y2 + sizeY2)) //...Checking if the oject CORNER is between Player Top AND Bottom corner.
		{
			return true;
		}
	}
	
	//===================================================== BOTTOM RIGHT:
	int BottomRight_CornerX = x + sizeX;
	int BottomRight_CornerY = y + sizeY;

	if     (BottomRight_CornerX >= x2 && BottomRight_CornerX <= (x2 + sizeX2)) //...Checking if the oject CORNER is between Player Left AND Right corner.
	{
		if (BottomRight_CornerY >= y2 && BottomRight_CornerY <= (y2 + sizeY2)) //...Checking if the oject CORNER is between Player Top AND Bottom corner.
		{
			return true;
		}
	}
	
	return false;
}
int main()
{
//=============================================  NOTES  ======================
/*
This is the part dedicated to the GRAPHICS, the GRAPHICS are IMAGES. The SPRTIES are getting their appearance FROM THE GRAPHICS but they ARE NOT the same thing.
We can say that the SPRITES is the number of thimes that we want a graphic to be reproduced on the screen, CAUSE 10 SPRITES CAN USE 1 GRAPHIC.
For this they look the same (cause the graphic is the same)
*/
//============================================================================	
// Load palette
	memcpy(pal_bg_mem, BGVPal, BGVPalLen);
	// Load tiles into CBB 0
	memcpy(&tile_mem[1][0], BGVTiles, BGVTilesLen);
	// Load map into SBB 29
	memcpy(&se_mem[29][0], BGVMap, BGVMapLen);

	// Set up BG0 for a 4bpp 64x32t map, Using charblock 1 and screenblock 29
	REG_BG1CNT= BG_CBB(1) | BG_SBB(29) | BG_4BPP | BG_REG_64x32;
	
	//================================== Player =====================================
	
	// Places the glyphs of a 4bpp boxed PLAYER sprite into LOW object memory (cbb == 4)
	memcpy(&tile_mem[4][0], ZVTiles, ZVTilesLen);
	memcpy(pal_obj_mem, ZVPal, ZVPalLen);
	
	//================================== Ammo =======================================
	
	// Places the glyphs of a 4bpp boxed AMMO sprite into LOW object memory (cbb == 4)
	memcpy(&tile_mem[4][2], AmmoBoxTiles, AmmoBoxTilesLen);
	memcpy(pal_obj_mem, AmmoBoxPal, AmmoBoxPalLen);
		
	// Init BG 0 for text on screen entries.
	tte_init_se_default(0, BG_CBB(0)|BG_SBB(28));
	
	//================================== Zombies ======================================
	
	// Places the glyphs of a 4bpp boxed ZOMBIES sprite into LOW object memory (cbb == 4)
	memcpy(&tile_mem[4][3], ZVTiles, ZVTilesLen);
	memcpy(pal_obj_mem, ZVPal, ZVPalLen);
	
	// Init the amount of memory required to store the current data
	oam_init(obj_buffer, 128);
	
	// Enable multiple backgrounds
	REG_DISPCNT= DCNT_MODE0 | DCNT_BG0;
	
	//int X, int Y, int Width, int Height, u32 tid, u32 pb, int obj_number
	
//========================= RANDOM NUMBERS!!! =============
	srand(time(NULL));
//========================= INIT AMMO BOX ====================
	InitAmmo  (40, 20, 8,  8, 2, 0, 2);	
	
//========================= INIT ZOMBIES====================


	init_zombies();

	
	// Init currently loaded Sprite
	//Ammo Item, int X, int Y, int Width, int Height, u32 tid, u32 pb, OBJ_ATTR *Sprite)
	InitSprites();
	
	
	current_state = 0;
	menuSelection = 0;
	
	while(current_state != 9)
	{
		
		vid_vsync();
		key_poll();
		
		char MainScore[50];
		
		switch (current_state)
		{
//============================================= Main Menu ===========================================
		case 0:
			FrmCount ++;
			tte_write("#{es}");
				
			tte_write("#{P:20,50}");
				
			tte_write("The Labyrinth Of The Dead");
			
			// Scroll Menu Selection
			if (key_hit(KEY_DOWN))
				{
					menuSelection++;
					FrmCount =0;
				}
				
			if (key_hit(KEY_UP))
				{
					menuSelection --;
					FrmCount =0;
				}
				
			if (menuSelection > 2)
				{
					menuSelection = 0;
				}
				
			if (menuSelection < 0)
				{
					menuSelection = 2;
				}
///============== MOVING TO Attractive Mode ============	
			if(FrmCount == 200 )
			{
				player_x = -240, player_y = -160;
				
				//Resetting position and the steps
				_z[5].x= 0 , _z[5].y = 0;
				_z[5].cur_Step = 0;
				_z[5].Count_Step = 0;
				//================================
				
				current_state = 6;
				FrmCount = 0;
				REG_DISPCNT= DCNT_MODE0 | DCNT_BG0 | DCNT_BG1 | DCNT_OBJ | DCNT_OBJ_1D;
			}
				
			switch (menuSelection)
			{
			case 0:
				
				tte_write("#{P:100,80}");
				
				tte_write("Start<-");

				tte_write("#{P:75,90}");
				
				tte_write("Instructions");
				
				tte_write("#{P:80,100}");
				
				tte_write("High Scores");
				
//============== MOVING TO Game Play ============
				if (key_hit(KEY_START))
				{
					current_state = 1;
					menuSelection = 0;
					_z[5].x= 240 , _z[5].y = 160;
					_z[5].cur_Step = 0;
					
					REG_DISPCNT= DCNT_MODE0 | DCNT_BG0 | DCNT_BG1 | DCNT_OBJ | DCNT_OBJ_1D;
				}
				
			break;
			
			case 1:
//============== MOVING TO Instructions ============
				
				tte_write("#{P:100,80}");
				
				tte_write("Start");
				
				tte_write("#{P:75,90}");
				
				tte_write("Instructions<-");
				
				tte_write("#{P:80,100}");
				
				tte_write("High Scores");
				
				if (key_hit(KEY_START))
				{
					current_state = 4;
					menuSelection = 0;
					REG_DISPCNT= DCNT_MODE0 | DCNT_BG0 ;
				}
				
			break;
				
				
				
			case 2:
			
				
				tte_write("#{P:100,80}");
				
				tte_write("Start");
				
				tte_write("#{P:75,90}");
				
				tte_write("Instructions");
				
				tte_write("#{P:80,100}");
				
				tte_write("High Scores<-");
				
//============== MOVING TO High Scores ============
				if (key_hit(KEY_START))
				{
					current_state = 5;
					menuSelection = 0;
					
					REG_DISPCNT= DCNT_MODE0 | DCNT_BG0 ;
				}
				break;	
			}
			
		break;
			
			
//======================================= Game Play ======================================
		case 1:
			tte_write("#{es}");
			
			
			//Turning Lifes INT Into String
			tte_write("#{P:3,153}");
				
			char Health[50];
			sprintf(Health,"Lifes:%d",LifesLeft);
				
			tte_write(Health);
			//Turning Score INT Into String
			tte_write("#{P:150,153}");
			
			
			sprintf(MainScore,"Score:%d",Score);
				
			tte_write(MainScore);
			
			
			
		//==================== Pausing ======================
			
			if (key_hit(KEY_SELECT))
			{
				current_state = 2;
				
				REG_DISPCNT= DCNT_MODE0 | DCNT_BG0;
			} 
			
			Update();
			
			//Refresh current buffers (Need to be done each gameplay loop)
			oam_copy(oam_mem, obj_buffer, 128);
			
			
		break;
			
			
//======================= Pause ============================
		case 2:
			
			tte_write("#{P:80,80}");
				
			tte_write("Press Start");
			
			tte_write("#{P:80,100}");
				
			tte_write("To Resume");
			
			
			//Resuming
			if (key_hit(KEY_START))
			{
				current_state = 1;
				REG_DISPCNT= DCNT_MODE0 | DCNT_BG0 | DCNT_BG1 | DCNT_OBJ | DCNT_OBJ_1D;
			}
			
		break;
			
//============================================= GAME OVER ==============================
		case 3:
			tte_write("#{es}");
			REG_DISPCNT= DCNT_MODE0 | DCNT_BG0;
			
			
			tte_write("#{P:80,30}");				
			tte_write("Game Over");
			
			tte_write("#{P:78,50}");
				
			tte_write("Press Start");
			
			tte_write("#{P:86,60}");
				
			tte_write("To Replay");
			
			
			tte_write("#{P:80,80}");
			
			sprintf(MainScore,"Your Score:%d",Score);
			
			tte_write(MainScore);
			
			
			//Replaying
			if (key_hit(KEY_START))
			{
				CalculateScoreS();
				Reset();
				current_state = 0;
				REG_DISPCNT= DCNT_MODE0 | DCNT_BG0;
			}
			
			
			
		break;
			
			
		case 4://Instructions
			
			tte_write("#{es}");
			REG_DISPCNT= DCNT_MODE0 | DCNT_BG0;
				
			tte_write("#{P:0,30}");				
			tte_write("Avoid the Zombies,collect the cakes,use the arrows for move around and press BackSPace to PAUSE the Game");
				
			tte_write("#{P:0,70}");
				
			tte_write("Press start to go back to the MAIN MENU");
				
				
			//Replaying
			if (key_hit(KEY_START))
			{
				Reset();
				current_state = 0;
				REG_DISPCNT= DCNT_MODE0 | DCNT_BG0;
			}
			
			
		break;
//============================================= SCORES MENU ==============================
		case 5:
			tte_write("#{es}");
				
			//Turning Score INT Into String
			int StringPx = 50;
			int StringPy = 50;
			int s;
			
			for (s = 0; s < NUMBER_OF_SCORES; s++)
			{
//This --->"StringPy+=10;" would be easier but! That employed more understaing skills!
				sprintf(MainScore,"#{P:%d,%d}",StringPx,StringPy+20*s);
			    tte_write(MainScore);
				
				sprintf(MainScore,"TopScore:%d",_topscores[s]);
				tte_write(MainScore);
			}
				
			//Moving back to the MAIN MENU
			REG_DISPCNT= DCNT_MODE0 | DCNT_BG0;
			if (key_hit(KEY_START))
			{
				Reset();
				current_state = 0;
				REG_DISPCNT= DCNT_MODE0 | DCNT_BG0;
			}
		break;
//===================================== ATTRACTIVE MODE!!! ==================================
		case 6:
			tte_write("#{es}");
			
			
			tte_write("#{P:5,50}");
			
			tte_write("Press Strat to run the game!");
			
			
			if (key_hit(KEY_START))
			{
				Reset();
				current_state = 0;
				player_x = 0, player_y = 0;
				REG_DISPCNT= DCNT_MODE0 | DCNT_BG0;
			}
			Update();
			
			
			//Refresh current buffers (Need to be done each gameplay loop)
			oam_copy(oam_mem, obj_buffer, 128);	
		break;
		}
	}
	
	return 0;
}
//=================================================================================================



void Update()
{


	//================================== Player vs Background ==================================



	if ((key_is_down(KEY_RIGHT))&&(!Collision(player_x + 1, player_y)))
	{
		player_x++;
	}
	////TRANSLATION: 1)If the key is pressed &&(and) is not (!) colliding && (and) is not less than 0, YOU CAN MOVE.
	if ((key_is_down(KEY_LEFT))&&(!Collision(player_x - 1, player_y)) && (player_x > 0))
	{
		player_x--;
	}
	////TRANSLATION: 1)If the key is pressed &&(and) is not (!) colliding && (and) is not less than 0, YOU CAN MOVE.
	if ((key_is_down(KEY_UP))&&(!Collision(player_x, player_y - 1))&& (player_y > 0))
	{
		player_y--;
	}
	
	if ((key_is_down(KEY_DOWN))&&(!Collision(player_x, player_y + 1)))
	{
		player_y++;
	}
	
	
	
	//====================== COLLISION with Ammo ============================
	int a;
	for (a = 0; a < NUMBER_OF_BOXES; a++)
	{
		
		if (AABBCollision(_ammo[a].x, _ammo[a].y, _ammo[a].width, _ammo[a].height, player_x,player_y,8,16) == true)
		{	
			//Resetting Ammo Count
			
			Score++;
			InitSpawns(a);
		}	
	}
	int i;
	for(i = 0; i < NUMBER_OF_ZOMBIES; i++)
	{
		
		//Player Loosing a Life and Also Being Reset to the Start
		
		if (AABBCollision(player_x, player_y,8,16, _z[i].x, _z[i].y, 8, 16) && (LifesLeft > 0))
		{
			LifesLeft -=1;
			
			
			player_x = 0;
			player_y = 0;
		}
		
	}
	//=============================================== Winning the Game & Loosing the Game ===============================================
	//Game Over
	if (LifesLeft == 0)
	{
		current_state = 3;
	}
	//============================================================================================
	// increment/decrement starting tile with R/L
	tid += bit_tribool(key_hit(-1), KI_R, KI_L);

	// flip
	if(key_hit(KEY_A))	// horizontally
		ZV->attr1 ^= ATTR1_HFLIP;
	if(key_hit(KEY_B))	// vertically
		ZV->attr1 ^= ATTR1_VFLIP;
	
	// make it glow (via palette swapping)
	//pb= key_is_down(KEY_SELECT) ? 1 : 0;


	// Hey look, it's one of them build macros!
	ZV->attr2= ATTR2_BUILD(tid, pb, 0);
	obj_set_pos(ZV, player_x, player_y);

	
	//=================Look at the difference between the "Structure format" and the normal one=====
	int x;
	for (x = 0; x < NUMBER_OF_BOXES; x++)
	{
		_ammo[x].sprite->attr2= ATTR2_BUILD(_ammo[x].tid, _ammo[x].pb, 0);
		obj_set_pos(_ammo[x].sprite, _ammo[x].x, _ammo[x].y);
	}
	//===============================================================================================
	
	update_zombies();
}
