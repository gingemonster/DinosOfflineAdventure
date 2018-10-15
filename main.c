#include <gb/gb.h>
#include <stdio.h>
#include <string.h>
#include <rand.h>
#include <gb/drawing.h>
#include <gb/font.h>
#include "sprites.h"
#include "sprites.c"
#include "background.h"
#include "background.c"
#include "map.h"
#include "map.c"


// =========================================================
// Global variables, constants etc
// =========================================================
//generical character structure: id, position, graphics
struct PG {
	UBYTE spritemapids[9]; // dino needs 7, and cacti 2, but to create a generic drawing and moving function everything will assume an 3x3 grid and just not full some
	UBYTE startspriteid; // the first sprite id in the collection
	UINT8 x;
	UINT8 y;
	UINT8 width;
	UINT8 height;
	UBYTE graphic;
	UBYTE initialized;
};

void resetgame();
void drawscore();
void checkInput();
void checkjumping();
void updateSwitches();
void drawdino(UBYTE);
void scrollbgandobstacles();
void playjump();
void playstep();
void enablesound();
void setupinitialsprites(); 
void setupinitialbackground();
void setupinitialwindow();
UBYTE shouldrenderanimationframe();
UINT8 getscreenquadrant(UINT8 screenoffset);
void setupcharactersprites(struct PG* character);
void movecharactersprites(struct PG* character);
void generatenextobstacles();
UBYTE checkanycollisions();
UBYTE checkcollides(struct PG* one,struct PG* two, UINT8 minx);

const unsigned char blankmap[]={0x00};
const UINT8 jump_array[] = {-26,-6,-3,-1,1,3,6, 26};
const UBYTE dinospritemap[] = {0,1,2,3,4,255,5,6,255}; // use 255 to indicate none as there is no concept of array null values, they would eval to 0
const UBYTE smallcactispritemap[] = {11,255,255,10,255,255,255,255,255}; // use 255 to indicate none as there is no concept of array null values, they would eval to 0
const UBYTE largecactispritemap[] = {9,255,255,10,255,255,255,255,255}; // use 255 to indicate none as there is no concept of array null values, they would eval to 0
const UINT8 speed = 2;
UINT8 skipframesforspriteanim;
UINT16 lastscreenquadrantrendered,currentscreenquadrant,nextscene,screenpixeloffset, laststarttime;
UINT8 frame,lastspriteid;
INT8 h,i,j,k,jumpindex,lastobstacleindex;
UBYTE hasmovedy,apressed,running,gameover;


struct PG obstacles[4]; // 4 in vram at once
struct PG dino;

void main() {
	
	enablesound();
	resetgame();
	
	
	while(1) {
		checkInput();
		updateSwitches();			// Make sure the SHOW_SPRITES and SHOW_BKG switches are on each loop
		wait_vbl_done();			// Wait until VBLANK to avoid corrupting visual memory

		if(running) {
			drawscore();
			checkjumping();
			drawdino(hasmovedy); // always move dino if moved or not so that we process jump or left right in the same place
			scrollbgandobstacles();
			if(checkanycollisions()==1){
				set_sprite_tile(1,12); // draw dinos SUPRISE eye
				running = 0;
				gameover = 1;

				// TODO show game over

				delay(1000); // otherwise user immediately will reset
			}
		}
	}
	
}

UBYTE checkanycollisions(){
	// for each obstacle on screen check if dino collides
	
	for(k=0;k!=4;k++){
		if(obstacles[k].initialized==1){
			if(checkcollides(&dino,&obstacles[k],54) == 1){
				return 1;
			}
		}
	}
	return 0;
}

UBYTE checkcollides(struct PG* one, struct PG* two, UINT8 minx){
	// using width and height of each look at x position 
	// and see if two rectangles overlap range at all
	// dino is always in quadrant 0 so not point checking objects
	// that are outside it so x < minx
	if(one->x > minx | two->x > minx){
		return 0;
	}
	return 
		((one->x >= two->x && one->x <= two->x + two->width) ||
		(two->x >= one->x && two->x <= one->x + one->width)) &&
		((one->y <= two->y && one->y >= two->y - two->height) ||
		(two->y <= one->y && two->y >= one->y - one->height));
}

void cls(){
	// write a clear sprite to every background block
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
	// animate legs and play step sound
	// dont want to play anim every frame so skip some
	
	if(shouldrenderanimationframe()){
		if(frame==0 || jumping){
			// both legs down
			frame = 1;
			set_sprite_tile(5,5); 
			set_sprite_tile(6,6);
		}
		else if(frame==1){
				// right leg up
				set_sprite_tile(5,5); 
				set_sprite_tile(6,8);
				playstep();			
				frame=2;
		}	
		else{
				// left leg up
				set_sprite_tile(5,7); 
				set_sprite_tile(6,6);
				playstep();					
				frame=0;
		}
	}
}

void movecharactersprites(struct PG* character){
	h = 0; // h needed to keep track of sprite maps that are not empty
	
	// dont bother moving a character if its not initialized, probably empty obstacle
	if(character->initialized==1){
		for(i=0;i!=3;i++){
			for(j=0;j!=3;j++){
				// increment characters sprite map through all 3x3 grid of sprite maps, checking if any should be ignored
				if(character->spritemapids[(i * 3 + j)] != 255){
					move_sprite(character->startspriteid + h,character->x + (j*8),character->y + (i*8));
					h++;
				}
			}
		}
	}
}

void scrollcharactersprites(struct PG* character, INT8 x, INT8 y){
	h = 0; // h needed to keep track of sprite maps that are not empty
	
	// dont bother moving a character if its not initialized, probably empty obstacle
	if(character->initialized==1){
		for(i=0;i!=3;i++){
			for(j=0;j!=3;j++){
				// increment characters sprite map through all 3x3 grid of sprite maps, checking if any should be ignored
				if(character->spritemapids[(i * 3 + j)] != 255){
					scroll_sprite(character->startspriteid + h,x,y);
					h++;
				}
			}
		}
	}
}

void scrollbgandobstacles(){
	// scroll bg by speed
	scroll_bkg(speed,0);

	// update the current count of how far we have scrolled the screen
	screenpixeloffset += speed;

	// get the quadrant of vram the left edge of the screen "screenpixeloffset")" is currently in
	currentscreenquadrant = getscreenquadrant(screenpixeloffset);

	if(lastscreenquadrantrendered!=currentscreenquadrant){
		// have just scrolled into new quadrant of screen so time to render previous quadrant
		// now its no longer visible on screen
		set_bkg_tiles(lastscreenquadrantrendered*8,10,8,1,&map[(nextscene * 32) + (lastscreenquadrantrendered * 8)]); // first row
		set_bkg_tiles(lastscreenquadrantrendered*8,11,8,1,&map[64 + (nextscene * 32) + (lastscreenquadrantrendered * 8)]); // second row

		if(lastscreenquadrantrendered==0||lastscreenquadrantrendered==2){
			generatenextobstacles();
		}

		// set the last rendereed quadrant
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

	// scroll obstacles
	for(k=0;k!=4;k++){
		if(obstacles[k].initialized==1){
			// TODO converto to generic character scroll method
			//scrollcharactersprites(&obstacles[k],-speed,0)
			scroll_sprite(obstacles[k].startspriteid,-speed,0);
			scroll_sprite(obstacles[k].startspriteid+1,-speed,0);
			// as x is UINT I assume it will wrap round to 256 automatically?
			// and it will get regenerated soon anyway

			// is just about to go off screen so make inactive instead and move to other end of screen
			// they are about to get regenerated anyway
			if(obstacles[k].x < speed){

				obstacles[k].x = 240;
				obstacles[k].initialized=0;
			}

			obstacles[k].x = obstacles[k].x - speed;
		}
	}
}


UINT8 getscreenquadrant(UINT8 screenoffset){
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

void drawscore(){
	UINT8 score[1] = {12};
	UINT8 digitmap[1];
	UINT16 time;
	INT8 numdigitsdrawn = 0;

	// dont want to redraw more than once per half second
	if(sys_time % 30 != 0){
		return;
	}

	time = (sys_time-laststarttime)/30; // per second scoring felt too slow

	while (time != 0) {
		digitmap[0] = time % 10 + 17;
		// draw next lowest digit
		set_win_tiles(10 - numdigitsdrawn, 0, 1, 1, digitmap);
		numdigitsdrawn++;
		time = time/10;
	}
}

void clearscore(){
	UINT8 clearmap[10] = {0,0,0,0,0,0,0,0,0,0};
	set_win_tiles(0, 0, 1, 1, clearmap);
	clearmap[0] = 17;
	set_win_tiles(10, 0, 1, 1, clearmap);
}

// =========================================================
// Initialisation / reset functions at very start of game
// =========================================================


void resetgame(){
	DISPLAY_OFF; // turn off so we dont see big redraw
	HIDE_SPRITES;
	gameover = 0;
	skipframesforspriteanim = speed * 6;
	jumpindex = -1;
	screenpixeloffset = 0;
	lastobstacleindex = -1;

	//reset and empty obstacles
	for(k=0;k!=4;k++){
		obstacles[k].x=240;
		movecharactersprites(&obstacles[k]);
		obstacles[k].initialized = 0;
	}

	// reset sprites
	setupinitialwindow();
	setupinitialbackground(); // create initial background
	setupinitialsprites(); // create initial sprites
	clearscore();
	drawdino(1);
	SHOW_SPRITES;
	DISPLAY_ON;
}

void setupinitialwindow(){
	// load window tiles
	UINT8 blank[1] = {0};
	//Load the GBDK default font (the tiles will be located on the BG VRAM between index 1-96 (0x01-0x60)
	font_init();
	//color(BLACK, LTGREY, SOLID);
	font_load(font_ibm);

	// write a clear sprite to every window block
	// write a clear sprite to every background block
	for (j=0 ; j != 32 ; j++){
		for (i=0 ; i != 32 ; i++){		
			set_win_tiles(i,j,1,1,blankmap);
		}
	}
	move_bkg(0,3);

	move_win(75,130);
	drawscore();
}

void setupinitialsprites(){
	set_sprite_data(0, 13, SpritesData);   /* defines the sprite data for all sprites */

	// create dino character
	// copy array of dinos sprite ids into dino.ids using memcpy
	memcpy(dino.spritemapids,dinospritemap, sizeof(dinospritemap)); 
	dino.x = 14;
	dino.y = 80;
	dino.width = 18; // technical sprites take up 24px but looks more like he hits at 18
	dino.height = 24;
	dino.startspriteid = 0;
	dino.initialized = 1;
	lastspriteid = 8; // dino fills 0-8
	movecharactersprites(&dino);

	setupcharactersprites(&dino); // & is saying pass a pointer to the function
}

void generatenextobstacles(){
	// will always be created in the last quadrant of vram
	// then scrolled into view
	UINT8 xoffsetfromstart; 
	INT8 currentindex;
	INT8 randomnum;
	initrand(DIV_REG);

	// get random number between 192 and 240 (256-2*8 so two sprites wide)
	xoffsetfromstart = 192 + rand() % 49;

	//lastspriteid

	// generate up to two obstacles
	for(k=0;k!=2;k++){
		// get random number between 0 and 2
		// used to decide what obstacle to generate
		initrand(DIV_REG);
		randomnum = rand() % 3;
		
		// if randomnum is 2 then skip creating an obstacle
		if(randomnum!=2){
			currentindex = lastobstacleindex + 1;
			
			// check if we start recycling sprites
			// there are 4 osbstacles spread across 256 of VRAM
			// each obstacles needs 2 sprites so last sprite id
			// is 16 (9-16)
			if(lastspriteid==16)
			{
				// dino takes 0-8
				lastspriteid=9;
			}
			else{
				lastspriteid++; // each obstacle takes 2 sprites
			}
			if(currentindex==4){
				currentindex = 0;
			}

			lastobstacleindex = currentindex;

			obstacles[currentindex].initialized = 1;
			obstacles[currentindex].startspriteid =  lastspriteid;
			
			obstacles[currentindex].x = (xoffsetfromstart + (k * 8)); // 2nd obstacle will always be 8 pixels to the right of first
			obstacles[currentindex].y = 81;
			obstacles[currentindex].width = 8;
			obstacles[currentindex].height = 16;

			if(randomnum==0){
				//set large cacti sprite map
				memcpy(obstacles[currentindex].spritemapids,largecactispritemap, sizeof(largecactispritemap));
			}
			else if (randomnum==1){
				//set small cacti sprite map
				memcpy(obstacles[currentindex].spritemapids,smallcactispritemap, sizeof(largecactispritemap));
			}

			// each obstacle loads 2 sprites so account for second
			lastspriteid++;

			// load the map images into sprites overwriting any previous ones
			setupcharactersprites(&obstacles[currentindex]);
			movecharactersprites(&obstacles[currentindex]);
		}
	}
}

void setupcharactersprites(struct PG* character){
	//loop map ids and load sprites where there is an id
	// -> are saying get a property from a pointer
	UBYTE currentspriteid = character->startspriteid;

	for(i=0;i!=sizeof(character->spritemapids);i++){
		if(character->spritemapids[i]!=255){ // check if sprite map is empty (255) or not
			set_sprite_tile(currentspriteid,character->spritemapids[i]);
			currentspriteid++;
		}
		
	}
}

void setupinitialbackground(){
	set_bkg_data(0, 11, BackgroundData); // load background data into tileset
	cls(); // clear background so that all tiles are blank to start with

	set_bkg_tiles(0,10,32,1,map); // draw first background row
	set_bkg_tiles(0,11,32,1,&map[96]); // draw second background row	

	nextscene = 1; // set next backgroundscene to draw
	screenpixeloffset = 0; // set initial screen scroll offset
	lastscreenquadrantrendered = 0; // set the last screen quadrant rendered
}

void updateSwitches() {
	
	SHOW_WIN;
	SHOW_SPRITES;
	SHOW_BKG;
	DISPLAY_ON;	
}

// =========================================================
// Animation utils
// =========================================================
UBYTE shouldrenderanimationframe(){
	return screenpixeloffset % skipframesforspriteanim == 0;
}

// =========================================================
// Event handlers
// =========================================================

void checkjumping(){
	if(shouldrenderanimationframe()){ // TODO MOVE TO SHARED FUNCTION
		
		if(jumpindex > -1){
			dino.y= dino.y + jump_array[jumpindex];
			scrollcharactersprites(&dino,0,jump_array[jumpindex]);
			hasmovedy = 1;

			if(jumpindex == sizeof(jump_array) - 1){
				// at end of jump index so end
				jumpindex = -1;
			}
			else{
				// move to next jump ammount
				jumpindex++;
			}
		}
		else{
			hasmovedy = 0;
		}
	}
}

void checkInput() {
	if((joypad() & J_A) && apressed == 0 && running) // only want to jump once per keypress
	{
		apressed = 1;
		// dont jump if already jumping
		if(jumpindex==-1){
			playjump();
			jumpindex = 0;
		}
	}
	else if ((joypad() & J_A) && apressed == 1 && running)
	{
		// do nothing user is still pressing A
	}
	else if(joypad() & J_A && !running){
		// not running and they press A so start / reset
		laststarttime = sys_time;
		if(gameover){
			resetgame();
		}
		running = 1;
		apressed = 1;
	}
	else{
		// reset A press they have let go of button
		apressed = 0;
	}

	if (hasmovedy){
		// if only moved Y (jump) we still want to wait for 60
		hasmovedy = 0;
		apressed = 1;
	}
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