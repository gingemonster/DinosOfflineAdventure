#include <gb/gb.h>
#include <stdio.h>
#include "sprites.h"
#include "sprites.c"
#include "background.h"
#include "background.c"
#include "map.h"
#include "map.c"

// =========================================================
// Global variables, constants etc
// =========================================================
void init();
void checkInput();
void checkjumping();
void updateSwitches();
void drawdino(UBYTE);
void scrollbgandenemies();
void playjump();
void playstep();
void drawcacti(UINT8,UINT8,UINT8);
void enablesound();
void setupinitialsprites(); 
void setupinitialbackground();
UINT8 getScreenQuadrant(UINT8 screenoffset);

const unsigned char blankmap[]={0x00};
const UINT8 jump_array[] = {-26,-12,-6,-3,-1,1,3,6, 12, 26};
const UINT8 speed = 2;
const UINT8 skipframesforspriteanim = 10;
UINT16 lastscreenquadrantrendered,currentscreenquadrant,nextscene,screenpixeloffset;
UINT8 frame,i,j,playery;
INT8 jumpindex;
UBYTE hasmovedy,apressed,running;
UINT8 enemysprites[];

void main() {

	init();
	
	while(1) {
		checkInput();
		updateSwitches();			// Make sure the SHOW_SPRITES and SHOW_BKG switches are on each loop
		wait_vbl_done();			// Wait until VBLANK to avoid corrupting visual memory		
		if(running) {
			checkjumping();
			drawdino(hasmovedy); // always move dino if moved or not so that we process jump or left right in the same place
			scrollbgandenemies();			
			delay(10);
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

// =========================================================
// Screen drawing functions
// =========================================================

void drawdino(UBYTE jumping){
	move_sprite(0,34,playery);
	move_sprite(1,42,playery);
	move_sprite(2,50,playery);

	move_sprite(3,34,playery + 8);
	move_sprite(4,42,playery + 8);

	// dont want to play anim every frame so skip some
	if(screenpixeloffset % skipframesforspriteanim == 0){
		frame = !frame;
		if(frame || jumping){
			set_sprite_tile(5,5); 
			set_sprite_tile(6,6);
		}
		else{
				set_sprite_tile(5,7); 
				set_sprite_tile(6,8);
				playstep();
		}
	}
	move_sprite(5,34,playery + 16);
	move_sprite(6,42,playery + 16);	
}

void drawcacti(UINT8 x, UINT8 y, UINT8 spritenum){
	set_sprite_tile(spritenum,9); 
	set_sprite_tile(spritenum+1,10);
	move_sprite(spritenum,x,y);
	move_sprite(spritenum+1,x,y+8);
	enemysprites[0] = spritenum;
	enemysprites[1] = spritenum + 1;
}

void scrollbgandenemies(){
	// for each move of 8 (a tile) load in the next tile from the next scene
	scroll_bkg(speed,0);
	screenpixeloffset += speed;

	// get the quadrant of vram the left edge of the screen (screenpixeloffset) is currently in
	currentscreenquadrant = getScreenQuadrant(screenpixeloffset);

	if(lastscreenquadrantrendered!=currentscreenquadrant){
		// have just scrolled into new quadrant of screen so time to render previous quadrant
		set_bkg_tiles(lastscreenquadrantrendered*8,10,8,1,&map[(nextscene * 32) + (lastscreenquadrantrendered * 8)]); // first row
		set_bkg_tiles(lastscreenquadrantrendered*8,11,8,1,&map[64 + (nextscene * 32) + (lastscreenquadrantrendered * 8)]); // second row

		//set_bkg_tiles(lastscreenquadrantrendered*8,10,8,1,&map[32]);
		//1 * 32 = 32 + 0 * 8 = 32;

		lastscreenquadrantrendered = currentscreenquadrant;
	}


	if(screenpixeloffset>=256){
		// we have reached end of screen so reset
		screenpixeloffset = 0;
		if(nextscene==1){
			nextscene = 0;
		}
		else{
			nextscene = 1;
		}
	}

	// scroll enemies
	for(i=0;i!=2;i++){
		scroll_sprite(enemysprites[i],-speed/2,0);
		scroll_sprite(enemysprites[i],-speed/2,0);
	}
}

UINT8 getScreenQuadrant(UINT8 screenoffset){
	if(screenoffset < 64){
		return 0;
	}
	if(screenoffset < 128){
		return 1;
	}
	if(screenoffset < 192){
		return 2;
	}
	return 3;	
}

// =========================================================
// Sound functions
// =========================================================

void enablesound(){
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


	NR51_REG = 0xFF; // set all chanels


	// NR50 controls volume
	// again 8 bytes
	// 7	Output Vin to Main SO2 output level control (1: on; 0: off) LEAVE ALONE
	// 6-4	SO2 (Left) Main Output level (volume)
	// 3	Output Vin to Main SO1 output level control (1: on; 0: off) LEAVE ALONE
	// 2-0	SO1 (Right) Main Output level (volume)	
	// 	0111 0111 is 0x77 in hex and the max volume
	NR50_REG = 0x77;
}

void playjump(){
	// see https://github.com/bwhitman/pushpin/blob/master/src/gbsound.txt
	// chanel 1 register 0, Sweep settings
	// 7	Unused
	// 6-4	Sweep time(update rate) (if 0, sweeping is off)
	// 3	Sweep Direction (1: decrease, 0: increase)
	// 2-0	Sweep RtShift amount (if 0, sweeping is off)
	// 0001 0110 is 0x1E, sweet time 1, sweep direction up, shift ammount 110 (6 decimal)
	NR10_REG = 0x16; 

	// chanel 1 register 1: Wave pattern duty and sound length
	// Channels 1 2 and 4
	// 5-0 sound length
	// 7-6	Wave pattern duty cycle 0-3, duty cycle is how long a square wave is "on" vs "of" so 50% (2) is both equal.
	// 0001 0000 is 0x10, duty cycle 0, wave length 10
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

void playstep(){
	NR41_REG = 0x01;
	NR42_REG = 0x11;
	NR43_REG = 0x00;
	NR44_REG = 0xC0;
}

// =========================================================
// Initialisation functions at very start of game
// =========================================================

void init() {
	playery = 80;
	jumpindex = -1;
	screenpixeloffset = 0;

	setupinitialbackground(); // create initial background
	setupinitialsprites(); // create initial sprites

	

	drawdino(1);
	drawcacti(90,81,7);
	enablesound();
}

void setupinitialsprites(){
	set_sprite_data(0, 12, SpritesData);   /* defines the sprite data */
	
	// dino
	set_sprite_tile(0,0);            /* defines the tiles numbers */
	set_sprite_tile(1,1); 
	set_sprite_tile(2,2); 
	set_sprite_tile(3,3); 
	set_sprite_tile(4,4); 
	set_sprite_tile(5,5); 
	set_sprite_tile(6,6);
}

void setupinitialbackground(){
	cls(); // clear background so that all tiles are blank to start with

	set_bkg_data(0, 11, BackgroundData); // load background data into tileset
	set_bkg_tiles(0,10,32,1,map); // draw first background row
	set_bkg_tiles(0,11,32,1,&map[96]); // draw secind background row	

	nextscene = 1; // set next backgroundscene to draw
	screenpixeloffset = 0; // set initial screen scroll offset
	lastscreenquadrantrendered = 0; // set the last screen quadrant rendered
}

void updateSwitches() {
	DISPLAY_ON;	
	HIDE_WIN;
	SHOW_SPRITES;
	SHOW_BKG;
}

// =========================================================
// Event handlers
// =========================================================

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