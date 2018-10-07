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
void playjump();

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
	
	set_bkg_tiles(backgroundtileoffset % 32,10,1,1,&map[backgroundtileoffset]); // draw 1 tile from first line of map
	set_bkg_tiles(backgroundtileoffset % 32,11,1,1,&map[backgroundtileoffset + 64]); // draw 1 tile from second line of map, offsetting map aray to the second line
	
	backgroundtileoffset++;
	if(backgroundtileoffset==64){
		// we have reached end of 2nd scene first row so reset offset to 0, first scene first row
		backgroundtileoffset = 0;
	}
	
}

void playjump(){
	// se https://github.com/bwhitman/pushpin/blob/master/src/gbsound.txt
	// turn on sound
	NR52_REG = 0x80; // turn on sound registers

	// there are 8 buts in this order, a 1 enables that chanel a 0 disables
	// 7	Channel 4 to Main SO2 output level control (Left)
	// 6	Channel 3 to Main SO2 output level control (Left)
	// 5	Channel 2 to Main SO2 output level control (Left)
	// 4	Channel 1 to Main SO2 output level control (Left)
	// 3	Channel 4 to Main SO1 output level control (Right)
	// 2	Channel 3 to Main SO1 output level control (Right)
	// 1	Channel 2 to Main SO1 output level control (Right)
	// 0	Channel 1 to Main SO1 output level control (Right)
	// so if you construct chanel 1 on as 0001 0001 (left and right chanel) which ix x11 in hex

	// NR50 controls volume
	// again 8 bytes
	// 7	Output Vin to Main SO2 output level control (1: on; 0: off) LEAVE ALONE
	// 6-4	SO2 (Left) Main Output level (volume)
	// 3	Output Vin to Main SO1 output level control (1: on; 0: off) LEAVE ALONE
	// 2-0	SO1 (Right) Main Output level (volume)	
	// 	0111 0111 is 0x77 in hex and the max volume
	NR50_REG = 0x77;

	NR51_REG = 0x11; // select chanel 1 to output sound 

	// chanel 1 register 0, Sweep settings
	// 7	Unused
	// 6-4	Sweep time(update rate) (if 0, sweeping is off)
	// 3	Sweep Direction (1: decrease, 0: increase)
	// 2-0	Sweep RtShift amount (if 0, sweeping is off)
	// 0001 0110 is 0x1E, sweet time 1, sweep direction up, shift ammount 110 (6 decimal)
	NR10_REG = 0x16; 

	// chanel 1 register 1: Wave pattern duty and sound length
	// Channels 1 2 and 4
	// 7-0	Wave pattern duty cycle 0-256, duty cycle is how long a square wave is "on" vs "of" so 50% (128) is both equal.
	// 0001 0000 is 0x10, duty cycle 16 of 256 which is 6.25% duty cycle
	NR11_REG = 0x10;

	// chanel 1 register 2: Volume Envelope (Makes the volume get louder or quieter each "tick")
	// On Channels 1 2 and 4
	// 7-4	(Initial) Channel Volume
	// 3	Volume sweep direction (0: down; 1: up)
	// 2-0	Length of each step in sweep (if 0, sweeping is off)
	// NOTE: each step is n/64 seconds long, where n is 1-7	
	// 0111 0011 is 0x73, volume 7, sweep down, step length 3
	NR12_REG = 0x73;

	// chanel 1 register 3: Frequency LSbs (Least Significant bits) and noise options
	// for Channels 1 2 and 3
	// 7-0	8 Least Significant bits of frequency (3 MSbs are in register 4)
	NR13_REG = 0x00;

	// chanel 1 register 4: Playback and frequency MSbs
	// Channels 1 2 3 and 4
	// 7	Initialize (trigger channel start, AKA channel INIT) (Write only)
	// 6	Consecutive select/length counter enable (Read/Write). When "0", regardless of the length of data on the NR11 register, sound can be produced consecutively.  When "1", sound is generated during the time period set by the length data contained in register NR11.  After the sound is ouput, the Sound 1 ON flag, at bit 0 of register NR52 is reset.
	// 5-3	Unused
	// 2-0	3 Most Significant bits of frequency
	// 1000 0011 is 0x83, initialize, set consecutive,  
	NR14_REG = 0x83;	
}

void init() {
	playery = 80;
	backgroundtileoffset = 32; // at start of next scene
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

	set_bkg_tiles(0,10,32,1,map); // draw first background
	set_bkg_tiles(0,11,32,1,&map[96]); // draw first background

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
			playjump();
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