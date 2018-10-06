#include <gb/gb.h>
#include <stdio.h>
#include "sprites.h"
#include "sprites.c"

void init();
void checkInput();
void checkjumping();
void updateSwitches();
void drawdino(BYTE render, BYTE jumping);

unsigned char alpha[] =
{
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

UINT8 frame, i, j;
INT8 jumpindex;
UINT8 player[2];
BYTE hasmovedx,hasmovedy,apressed;
UINT8 jump_array[] = {-26,-12,-6,-3,-1,1,3,6, 12, 26};

void main() {

	init();
	
	while(1) {
		checkjumping();
		checkInput();
		updateSwitches();			// Make sure the SHOW_SPRITES and SHOW_BKG switches are on each loop
		wait_vbl_done();			// Wait until VBLANK to avoid corrupting visual memory		
	}
	
}

void cls(){
	set_bkg_data(0,0,alpha);		// Load 1 tiles into background memory

	for (j=0 ; j != 18 ; j++){
		for (i=0 ; i != 20 ; i++){		
			set_bkg_tiles(i,j,1,1,alpha);
		}
	}		
}

void drawdino(BYTE render, BYTE jumping){
	if(render){
		frame = !frame;
		move_sprite(0,player[0],player[1]);
		move_sprite(1,player[0] + 8,player[1]);
		move_sprite(2,player[0] + 16,player[1]);

		move_sprite(3,player[0],player[1] + 8);
		move_sprite(4,player[0] + 8,player[1] + 8);

		if(frame || jumping){
			set_sprite_tile(5,5); 
			set_sprite_tile(6,6);
		}
		else{
			set_sprite_tile(5,7); 
			set_sprite_tile(6,8);
		}
		move_sprite(5,player[0] ,player[1] + 16);
		move_sprite(6,player[0] + 8,player[1] + 16);		
	}
}

void init() {
	player[0] = 64;
	jumpindex = -1;
	player[1] = 80;
	DISPLAY_ON;						// Turn on the display
	set_sprite_data(0, 9, SpritesData);   /* defines the sprite data */
	
	set_sprite_tile(0,0);            /* defines the tiles numbers */
	set_sprite_tile(1,1); 
	set_sprite_tile(2,2); 
	set_sprite_tile(3,3); 
	set_sprite_tile(4,4); 
	set_sprite_tile(5,5); 
	set_sprite_tile(6,6);	

	cls(); // clear background
	drawdino(1);

}


void updateSwitches() {
	HIDE_WIN;
	SHOW_SPRITES;
	SHOW_BKG;
}

void checkjumping(){
	if(jumpindex > -1){

		player[1] = player[1] + jump_array[jumpindex];
		hasmovedy = 1;

		if(jumpindex == sizeof(jump_array) - 1){
			// at end of jump index so end
			jumpindex = -1;
		}
		else{
			// move to next jump ammount
			jumpindex ++;
		}
	}
	else{
		hasmovedy = 0;
	}
}

void checkInput() {

	if(joypad() & J_RIGHT)   // the & rather than and == means that more than one key can be pressed at once     
	{
		player[0] = player[0] + 2;
		hasmovedx = 1;
	}

	if(joypad() & J_LEFT)           /* see above */
	{
		player[0] = player[0] -2;
		hasmovedx = 1;
	}

	if((joypad() & J_A) && apressed == 0) // only want to jump once per keypress
	{
		apressed = 1;
		// dont jump if already jumping
		if(jumpindex==-1){
			jumpindex = 0;
		}
	}
	else if ((joypad() & J_A) && apressed == 1)
	{
		// do nothing user is still pressing A
	}
	else
	{
		apressed = 0;
	}

	drawdino(hasmovedx | hasmovedy, hasmovedy); // always move dino if moved or not so that we process jump or left right in the same place

	if(hasmovedx)
	{
		delay(60);	
		hasmovedx = 0;	
	}
	else if (hasmovedy){
		// if only moved Y (jump) we still want to wait for 30
		hasmovedy = 0;
 		delay(60);
	}
}