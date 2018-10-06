#include <gb/gb.h>
#include <stdio.h>
#include "sprites.h"
#include "sprites.c"
#include "background.h"
#include "background.c"
#include "map.h"
#include "map.c"

void init();
void checkInput();
void checkjumping();
void updateSwitches();
void drawdino(BYTE jumping);
void drawbg();

UINT8 frame, i, j;
INT8 jumpindex;
UINT8 playery;
UINT8 backgroundtileoffset,backgroundscene;
INT8 speed = 8;
BYTE hasmovedx,hasmovedy,apressed,running;
UINT8 jump_array[] = {-26,-12,-6,-3,-1,1,3,6, 12, 26};

unsigned char EmptyBackgroundData[] = 
{  
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

void main() {

	init();
	
	while(1) {
		checkjumping();
		checkInput();
		updateSwitches();			// Make sure the SHOW_SPRITES and SHOW_BKG switches are on each loop
		wait_vbl_done();			// Wait until VBLANK to avoid corrupting visual memory		
		if(running) {
			drawdino(hasmovedy); // always move dino if moved or not so that we process jump or left right in the same place
			drawbg(hasmovedx);			
			delay(60);
		}
	}
	
}

void cls(){
	move_bkg(0,3);
	for (j=0 ; j != 18 ; j++){
		for (i=0 ; i != 20 ; i++){		
			set_bkg_tiles(i,j,1,1,0x0B);
		}
	}	
}

void drawdino(BYTE jumping){

	frame = !frame;
	move_sprite(0,64,playery);
	move_sprite(1,72,playery);
	move_sprite(2,80,playery);

	move_sprite(3,64,playery + 8);
	move_sprite(4,72,playery + 8);

	if(frame || jumping){
		set_sprite_tile(5,5); 
		set_sprite_tile(6,6);
	}
	else{
		set_sprite_tile(5,7); 
		set_sprite_tile(6,8);
	}
	move_sprite(5,64,playery + 16);
	move_sprite(6,72,playery + 16);	
}

void drawbg(){
	// if(backgroundoffset == 0){
	// 	if(backgroundscene == 0){
	// 		backgroundscene = 1;
	// 		set_bkg_tiles(0,10,32,2,mapBLK1);
	// 	}
	// 	else{
	// 		backgroundscene = 0;
	// 		set_bkg_tiles(0,10,32,2,mapBLK0);
	// 	}
	// }
	
	// backgroundoffset = backgroundoffset + speed;
	// if(backgroundoffset > 256){  // 32 tiles, 8 pixels each
	// 	backgroundoffset = 0;
	// }		
	// move_bkg(backgroundoffset,0);

	// for each move of 8 (a tile) load in the next tile from the next scene
	backgroundtileoffset++;
	if(backgroundscene == 0){
		set_bkg_tiles(0,10,backgroundtileoffset,1,mapBLK1);
	}
	else{
		set_bkg_tiles(0,10,backgroundtileoffset,1,mapBLK0);
	}	
	

	if(backgroundtileoffset>31){
		backgroundtileoffset = 0;
		if(backgroundscene == 0){
			backgroundscene = 1;
		}
		else{
			backgroundscene = 0;
		}
	}
	scroll_bkg(speed,0);
}

void init() {
	playery = 80;
	backgroundtileoffset = 0;
	backgroundscene = 0; 
	
	jumpindex = -1;
	
	DISPLAY_ON;						// Turn on the display

	set_bkg_data(0, 11, BackgroundData);
	

	set_sprite_data(0, 9, SpritesData);   /* defines the sprite data */
	
	
	set_sprite_tile(0,0);            /* defines the tiles numbers */
	set_sprite_tile(1,1); 
	set_sprite_tile(2,2); 
	set_sprite_tile(3,3); 
	set_sprite_tile(4,4); 
	set_sprite_tile(5,5); 
	set_sprite_tile(6,6);	

		

	cls(); // clear background
	set_bkg_tiles(0,10,32,2,mapBLK0); // draw first background

	drawdino(1);

}


void updateSwitches() {
	HIDE_WIN;
	SHOW_SPRITES;
	SHOW_BKG;
}

void checkjumping(){
	if(jumpindex > -1){

		playery= playery + jump_array[jumpindex];
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
	if(joypad() == J_START){
		running = 1;
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


	if (hasmovedy){
		// if only moved Y (jump) we still want to wait for 60
		hasmovedy = 0;
	}
}