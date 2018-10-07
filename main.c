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
void drawdino(UBYTE jumping);
void drawbg();

UINT8 frame,i,j,playery,backgroundtileoffset,backgroundscene,jump_array[] = {-26,-12,-6,-3,-1,1,3,6, 12, 26};
INT8 jumpindex,speed = 8;
UBYTE hasmovedy,apressed,running;

unsigned char blankmap[] =
{
  0x00
};

void main() {

	init();
	
	while(1) {
		checkInput();
		updateSwitches();			// Make sure the SHOW_SPRITES and SHOW_BKG switches are on each loop
		wait_vbl_done();			// Wait until VBLANK to avoid corrupting visual memory		
		if(running) {
			checkjumping();
			drawdino(hasmovedy); // always move dino if moved or not so that we process jump or left right in the same place
			drawbg();			
			delay(80);
		}
	}
	
}

void cls(){
	// write a clear sprite to every screen block
	for (j=0 ; j != 32 ; j++){
		for (i=0 ; i != 32 ; i++){		
			set_bkg_tiles(i,j,1,1,blankmap);
		}
	}
	move_bkg(0,3);
}

void drawdino(UBYTE jumping){

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
	// for each move of 8 (a tile) load in the next tile from the next scene
	scroll_bkg(speed,0);
	
	set_bkg_tiles(backgroundtileoffset % 32,10,1,1,&map[backgroundtileoffset]);
	set_bkg_tiles(backgroundtileoffset % 32,11,1,1,&map[backgroundtileoffset+32]);
	
	backgroundtileoffset++;
	if(backgroundtileoffset==96){
		// we have reached end of 2nd scene first row so reset offset to 0, first scene first row
		backgroundtileoffset = 0;
	}
	else if(backgroundtileoffset==32){
		// has reached end of 1st scene first row so jump to start of 2nd scene first row
		backgroundtileoffset = 64;
	}
	
}

void init() {
	playery = 80;
	backgroundtileoffset = 64; // at start of next scene
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

	set_bkg_tiles(0,10,32,2,map); // draw first background

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
	if((joypad() & J_A) && apressed == 0 && running) // only want to jump once per keypress
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