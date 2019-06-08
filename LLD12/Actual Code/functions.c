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
#include "LDD.h"
//We did this for redefine some numbers.
#include "functions.h"



void init_zombies()
{
	
	InitZombie(20, 10, 8, 16, 3, 0, 0, 6);
//The first number is"Wich Zombie" the second is the "Number of the steps" and the final one is the "Direction"
	
	_z[0].path[0]=70;//NUMBER OF STEPS
	_z[0].path[1]=DOWN;//DIRECTION
	
	_z[0].path[2]=37;
	_z[0].path[3]=RIGHT;
	
	_z[0].path[4]=70;
	_z[0].path[5]=UP;
	
	_z[0].path[6]=37;
	_z[0].path[7]=LEFT;
	
	_z[0].path[8]=0;
	_z[0].path[9]=RESET;
	

	InitZombie(50, 20, 8, 16, 3, 0, 1, 7);
	
	_z[1].path[0]=70;//NUMBER OF STEPS
	_z[1].path[1]=DOWN;//DIRECTION
	
	_z[1].path[2]=20;
	_z[1].path[3]=RIGHT;
	
	_z[1].path[4]=20;//NUMBER OF STEPS
	_z[1].path[5]=DOWN;//DIRECTION
	
	_z[1].path[6]=34;
	_z[1].path[7]=RIGHT;
	
	_z[1].path[8]=90;
	_z[1].path[9]=UP;
	
	_z[1].path[10]=54;
	_z[1].path[11]=LEFT;
	
	_z[1].path[12]=0;
	_z[1].path[13]=RESET;
	
	InitZombie(200, 40, 8, 16, 3, 0, 2, 8);
	
	_z[2].path[0]=72;
    _z[2].path[1]=DOWN;
    
    _z[2].path[2]=50;
    _z[2].path[3]=LEFT;
    
    _z[2].path[4]=25;
    _z[2].path[5]=DOWN;
   
    _z[2].path[6]=68;
    _z[2].path[7]=RIGHT;
    
    _z[2].path[8]=97;
    _z[2].path[9]=UP;
    
    _z[2].path[10]=18;
    _z[2].path[11]=LEFT;
    
    _z[2].path[12]=0;
    _z[2].path[13]=RESET;

	InitZombie(00, 140, 8, 16, 3, 0, 3, 9);
	
	_z[3].path[0]=104;
    _z[3].path[1]=RIGHT;
    
    _z[3].path[2]=120;
    _z[3].path[3]=UP;
    
    _z[3].path[4]=25;
    _z[3].path[5]=LEFT;
   
    _z[3].path[6]=100;
    _z[3].path[7]=DOWN;
    
    _z[3].path[8]=79;
    _z[3].path[9]=LEFT;
    
    _z[3].path[10]=20;
    _z[3].path[11]=DOWN;
    
    _z[3].path[12]=0;
    _z[3].path[13]=RESET;
	
	InitZombie(136, 0, 8, 16, 3, 0, 4, 10);
	
	_z[4].path[0]= 64;
	_z[4].path[1]= DOWN;
	
	_z[4].path[2]= 39;
	_z[4].path[3]= RIGHT;
	
	_z[4].path[4]= 20;
	_z[4].path[5]= UP;
   
	_z[4].path[6]= 53;
	_z[4].path[7]= RIGHT;
	
	_z[4].path[8]= 44;
	_z[4].path[9]= UP;
	
	_z[4].path[10]= 92;
	_z[4].path[11]= LEFT;
	
	_z[4].path[12]= 0;
	_z[4].path[13]= RESET;
	
InitZombie(0, 0, 8, 16, 3, 1, 5, 11);
	//if(current_state == 6)
	//{
		
		
		_z[5].path[0]= 96;
		_z[5].path[1]= DOWN;
		
		_z[5].path[2]= 57;
		_z[5].path[3]= RIGHT;
		
		_z[5].path[4]= 26;
		_z[5].path[5]= DOWN;
		
		_z[5].path[6]= 40;
		_z[5].path[7]= LEFT;
		
		_z[5].path[8]= 20;
		_z[5].path[9]= DOWN;
		
		_z[5].path[10]=110;
		_z[5].path[11]=RIGHT;
		
		_z[5].path[12]=54;
		_z[5].path[13]=UP;
		
		_z[5].path[14]=23;
		_z[5].path[15]=LEFT;
		
		_z[5].path[16]=24;
		_z[5].path[17]=UP;
		
		_z[5].path[18]=35;
		_z[5].path[19]=RIGHT;
		
		_z[5].path[20]=60;
		_z[5].path[21]=UP;
		
		_z[5].path[22]=80;
		_z[5].path[23]=RIGHT;
		
		_z[5].path[24]=140;
		_z[5].path[25]=DOWN;
		
		_z[5].path[26]=150;
		_z[5].path[27]=LEFT;
		
		_z[5].path[28]=144;
		_z[5].path[29]=UP;
		
		_z[5].path[30]=69;
		_z[5].path[31]=LEFT;
		
		_z[5].path[32]=0;
		_z[5].path[33]=RESET;
	//}	
	
}   

void update_zombies()
{

	int z;
	for(z = 0; z<NUMBER_OF_ZOMBIES; z++)
	{
	
		if(_z[z].Count_Step == 0)
		{
			int StepCount = _z[z].cur_Step;
			
			//This makes the code read how many steps left to change direction
			_z[z].Count_Step = _z[z].path[StepCount];
			
			//This one here makes the code read the direction
			_z[z].cur_Step++;
			
		}	
	
		int Direction = _z[z].path[_z[z].cur_Step];
		
		switch(Direction)
		{
		//You can find out how we managed to substitute the numbers in "Reset" etc. in the function.h!!!
			case RESET:
				_z[z].cur_Step = 0;
				break;
			case UP:
				_z[z].y--;
				_z[z].Count_Step--;
				if(_z[z].Count_Step == 0)
				{
					_z[z].cur_Step++;
					
				}	
				break;
			case RIGHT:
				_z[z].x++;
				_z[z].Count_Step--;
				if(_z[z].Count_Step == 0)
				{
					_z[z].cur_Step++;
					
				}	
				break;
			case DOWN:
				_z[z].y++;
				_z[z].Count_Step--;
				if(_z[z].Count_Step == 0)
				{
					_z[z].cur_Step++;
					
				}
				break;
			case LEFT:
				_z[z].x--;
				_z[z].Count_Step--;
				if(_z[z].Count_Step == 0)
				{
					_z[z].cur_Step++;
					
				}	
				break;
			default:
				break;		
		}
		_z[z].sprite->attr2= ATTR2_BUILD(_z[z].tid, _z[z].pb, 0);
		obj_set_pos(_z[z].sprite, _z[z].x, _z[z].y);
		
	}
	
	
	//_z[3].sprite->attr2= ATTR2_BUILD(_z[3].tid, _z[3].pb, 0);
	//obj_set_pos(_z[3].sprite, _z[3].x, _z[3].y);
	//obj_set_pos(_z[3].sprite, 10, 10);
	
	//obj_set_pos(_z[1].sprite, 100, 100);*/
		
}








