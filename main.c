#include <gb/gb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rand.h>
#include "sprites.h"
#include "sprites.c"
#include "background.h"
#include "background.c"
#include "map.h"
#include "map.c"
#include "font.h" // tried using built in fonts but including font.h broke code on real device?
#include "font.c"
#include "splashscreen.c"
#include "splashscreenmap.c"
#include "creditscreen.c"
#include "creditscreenmap.c"

// =========================================================
// Global variables, constants etc
// =========================================================
extern INT16 sessionhighscore;

//generical character structure: id, position, graphics
struct PG {
	UBYTE spritemapids[9]; // dino needs 7, and cacti 2, but to create a generic drawing and moving function everything will assume an 3x3 grid and just not full some
	UBYTE spritemapidsanimated[9]; 
	UBYTE startspriteid; // the first sprite id in the collection
	UINT8 x;
	UINT8 y;
	UINT8 width;
	UINT8 height;
	UBYTE graphic;
	UBYTE initialized;
	UBYTE animated;
};

void resetgame(UBYTE fadeenabled);
void drawscore();
void checkInput();
void checkjumping();
void updateSwitches();
void animatedino(UBYTE);
void animateobstacles();
void drawgameover();
void playgameover();
void scrollbg();
void scrollobstacles();
void playjump();
void playstep();
void enablesound();
void setupinitialsprites(); 
void setupinitialbackground();
void setupinitialwindow();
void drawsplashscreen();
void drawcreditsscreen();
void playmusicnext();
void clearbackground();
void fadeout();
void fadein();
void drawhighscore();
void makegameharder(UINT16 time);
void setupcharactersprites(struct PG* character, UBYTE showanimated);
void movecharactersprites(struct PG* character, UINT8 width, UINT8 height, UINT8 spacing);
void generatenextobstacles();
void showsplashandintro();
UBYTE shouldrenderanimationframe();
UBYTE checkanycollisions();
UBYTE checkcollides(struct PG* one,struct PG* two, UINT8 minx);
UINT8 getvramquadrant(UINT8 screenoffset);

const unsigned char blankmap[1] =
{
	0x00
};
const UINT8 jump_array[7] = {-26,-3,-1,1,5,10, 14};
const UBYTE dinospritemap[9] = {0,1,2,3,4,255,5,6,255}; // use 255 to indicate none as there is no concept of array null values, they would eval to 0
const UBYTE smallcactispritemap[9] = {11,255,255,10,255,255,255,255,255}; // use 255 to indicate none as there is no concept of array null values, they would eval to 0
const UBYTE largecactispritemap[9] = {9,255,255,10,255,255,255,255,255}; // use 255 to indicate none as there is no concept of array null values, they would eval to 0
const UBYTE gameoverspritemap[8] = {34,28,40,32,42,49,32,45};
const UBYTE pterodactylspritemap[9] = {13,255,255,14,255,255,255,255,255}; // use 255 to indicate none as there is no concept of array null values, they would eval to 0
const UBYTE pterodactylspritemapanimated[9] = {15,255,255,16,255,255,255,255,255}; // use 255 to indicate none as there is no concept of array null values, they would eval to 0
const UBYTE clearscoremap[8] = {11,11,11,11,11,11,11,12};
const UBYTE clearhighscoresmap[8] = {11,11,11,11,11,11,11,11};
const UBYTE highscoremap[2] = {0x1D,0x1E};

UBYTE hasdinojustmovedy,apressed,running,gameover,splashscreen;
UINT8 dinomanimationframe,obstanimationframe,lastspriteid,h,i,j,k, currentBeat, skipgeneratingobstacles,speed;
UINT16 lastscreenquadrantrendered,currentscreenquadrant,nextscene,screenpixeloffset, laststarttime, timerCounter;
INT8 jumpindex,lastobstacleindex;


struct PG obstacles[4]; // 4 in vram at once
struct PG dino;
struct PG gameoversprite;

void main() {
	ENABLE_RAM_MBC1;
	speed = 2;
	skipgeneratingobstacles = 0;

	showsplashandintro();
	resetgame(1);

	// maing game loop
	while(1) {
		checkInput();
		updateSwitches();			// Make sure the SHOW_SPRITES and SHOW_BKG switches are on each loop
		wait_vbl_done();			// Wait until VBLANK to avoid corrupting visual memory
	
		if(running) {
			drawscore();
			checkjumping();
			animatedino(hasdinojustmovedy);
			animateobstacles();
			scrollbg();
			scrollobstacles();
			if(checkanycollisions()){
				set_sprite_tile(1,12); // draw dinos SUPRISE eye
				drawgameover();
				playgameover();
				drawhighscore(); // do here as well as in reset so you see new high score on gameover
				running = 0;
				gameover = 1;
				delay(1000); // otherwise user immediately will reset
			}
		}
	}
	DISABLE_RAM_MBC1;
}

UBYTE checkanycollisions(){
	// for each obstacle on screen check if dino collides
	
	for(k=0;k!=4;k++){
		if(obstacles[k].initialized){
			if(checkcollides(&dino,&obstacles[k],54)){
				return 1;
			}
		}
	}
	return 0;
}

UBYTE checkcollides(struct PG* dino, struct PG* obst, UINT8 minx){
	// TODO store these rather than calculating every time
	UINT8 smallerdinox = dino->x + 3;
	UINT8 smallerdinoy = dino->y + 4;
	UINT8 smallerdinowidth = dino->width - 6;
	UINT8 smallerdinoheight = dino->height - 6;
	// using width and height of each look at x position 
	// and see if two rectangles overlap range at all
	// dino is always in quadrant 0 so not point checking objects
	// that are outside it so x < minx
	if(obst->x > minx){
		return 0;
	}
	// to make collisions "look" more pixel accurate
	// make dino a little shorter and thinner

	
	return 
		((smallerdinox >= obst->x && smallerdinox <= obst->x + obst->width) ||
		(obst->x >= smallerdinox && obst->x <= smallerdinox + smallerdinowidth)) &&
		((smallerdinoy <= obst->y && smallerdinoy >= obst->y - obst->height) ||
		(obst->y <= smallerdinoy && obst->y >= smallerdinoy - smallerdinoheight));
}


// =========================================================
// Screen / character drawing functions
// =========================================================

void clearbackground(){
	// write a clear sprite to every background block
	for (j=0 ; j != 32 ; j++){
		for (i=0 ; i != 32 ; i++){		
			set_bkg_tiles(i,j,1,1,blankmap);
		}
	}
}

void animatedino(UBYTE jumping){
	// animate legs and play step sound
	// dont want to play anim every frame so skip some
	
	if(shouldrenderanimationframe()){
		if(dinomanimationframe==0 || jumping){
			// both legs down
			dinomanimationframe = 1;
			set_sprite_tile(5,5); 
			set_sprite_tile(6,6);
		}
		else if(dinomanimationframe==1){
				// right leg up
				set_sprite_tile(5,5); 
				set_sprite_tile(6,8);
				playstep();			
				dinomanimationframe=2;
		}	
		else{
				// left leg up
				set_sprite_tile(5,7); 
				set_sprite_tile(6,6);
				playstep();					
				dinomanimationframe=0;
		}
	}
}

void animateobstacles(){
	if(shouldrenderanimationframe()){
		for(k=0;k!=4;k++){
			if(obstacles[k].initialized==1&&obstacles[k].animated==1){
				setupcharactersprites(&obstacles[k],obstanimationframe);
			}
		}
		obstanimationframe=!obstanimationframe;
	}
}

void movecharactersprites(struct PG* character, UINT8 width, UINT8 height, UINT8 spacing){
	UINT8 spacingaccumulatorx = 0;
	UINT8 spacingaccumulatory = 0;	
	h = 0; // h needed to keep track of sprite maps that are not empty
	// dont bother moving a character if its not initialized, probably empty obstacle
	if(character->initialized==1){
		for(i=0;i!=height;i++){
			spacingaccumulatory += spacing;
			
			for(j=0;j!=width;j++){
				spacingaccumulatorx += spacing;
				// increment characters sprite map through all 3x3 grid of sprite maps, checking if any should be ignored
				if(character->spritemapids[(i * 3 + j)] != 255){
					move_sprite(character->startspriteid + h,character->x + (j*8) + spacingaccumulatorx,character->y + (i*8) + spacingaccumulatory);
					h++;
				}
			}
			spacingaccumulatorx = 0; // reset for each line
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

void scrollbg(){
	// scroll bg by speed
	scroll_bkg(speed,0);

	// update the current count of how far we have scrolled the screen
	screenpixeloffset += speed;

	// get the quadrant of vram the left edge of the screen "screenpixeloffset")" is currently in
	currentscreenquadrant = getvramquadrant(screenpixeloffset);

	if(lastscreenquadrantrendered!=currentscreenquadrant){
		// have just scrolled into new quadrant of screen so time to render previous quadrant
		// now its no longer visible on screen
		set_bkg_tiles(lastscreenquadrantrendered*8,10,8,1,&map[(nextscene * 32) + (lastscreenquadrantrendered * 8)]); // first row
		set_bkg_tiles(lastscreenquadrantrendered*8,11,8,1,&map[64 + (nextscene * 32) + (lastscreenquadrantrendered * 8)]); // second row

		if(lastscreenquadrantrendered==0||lastscreenquadrantrendered==2){
			// skip used when we increase speed so that no obstacles 
			// are shown for a bit
			if(skipgeneratingobstacles>0){
				skipgeneratingobstacles--;
			}
			else{
				generatenextobstacles();
			}
		}

		// set the last rendereed quadrant
		lastscreenquadrantrendered = currentscreenquadrant;
	}

	if(screenpixeloffset>=256){
		// we have reached end of vram width so reset
		screenpixeloffset = 0;
		if(nextscene==1){
			nextscene = 0;
		}
		else{
			nextscene = 1;
		}
	}
}

void scrollobstacles(){
	// scroll obstacles
	for(k=0;k!=4;k++){
		if(obstacles[k].initialized==1){
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

UINT8 getvramquadrant(UINT8 screenoffset){
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
	INT16 time;
	INT8 numdigitsdrawn = 0;
	// dont want to redraw more than once per half second
	if(sys_time % 30 != 0){
		return;
	}

	time = (sys_time-laststarttime)/30; // per second scoring felt too slow
	makegameharder(time);

	if(time > sessionhighscore){
		sessionhighscore = time;
	}

	while (time != 0) {
		digitmap[0] = time % 10 + 12;
		// draw next lowest digit
		set_win_tiles(19- numdigitsdrawn, 0, 1, 1, digitmap);
		numdigitsdrawn++;
		time = time/10;
	}
}

void drawhighscore(){
	UINT8 digitmap[1];
	INT16 time;
	INT8 numdigitsdrawn = 0;


	//printf("%u",sessionhighscore);

	if(sessionhighscore > 10000){
		
		sessionhighscore = 0;
		//printf("%u",sessionhighscore);
		
	}

	time = sessionhighscore;

	// clear any previous scores
	set_win_tiles(12, 2, 8, 1, clearhighscoresmap);

	while (time != 0) {
		digitmap[0] = time % 10 + 12;
		// draw next lowest digit
		set_win_tiles(19 - numdigitsdrawn, 2, 1, 1, digitmap);
		numdigitsdrawn++;
		time = time/10;
	}

	if(sessionhighscore != 0){
		set_win_tiles(17 - numdigitsdrawn, 2, 2, 1, highscoremap);
	}	
}

void clearscore(){
	set_win_tiles(12, 0, 8, 1, clearscoremap);
}

void drawgameover(){
	set_sprite_data(17, 35, Font); // load font data
	// copy array of dinos sprite ids into dino.ids using memcpy
	memcpy(gameoversprite.spritemapids,gameoverspritemap, sizeof(gameoverspritemap)); 
	gameoversprite.x = 68;
	gameoversprite.y = 40;
	gameoversprite.width = 24; 
	gameoversprite.height = 16;
	gameoversprite.startspriteid = 18;
	gameoversprite.initialized = 1;
	lastspriteid = 8; // dino fills 0-8
	setupcharactersprites(&gameoversprite,0); // & is saying pass a pointer to the function
	movecharactersprites(&gameoversprite,4,2,2);
}

void drawsplashscreen(){
	DISPLAY_OFF;	
	// Load up the tile data	
     set_bkg_data(0,255,splashscreendata);

    //  // Switch to VRAM
    //  VBK_REG = 1;

    //  // Switch out of VRAM
    //  VBK_REG = 0;

     // Set screen x,y pos to 0,0 and draw the map 20,18(size of the screen)
     set_bkg_tiles(0,0,20,18,splashscreenmap);

     // Show the background
     SHOW_BKG;

     // Turn the display on
     DISPLAY_ON; 
}

void drawcreditsscreen(){
	DISPLAY_OFF;	
	// Load up the tile data	
     set_bkg_data(0,255,creditscreendata);

    //  // Switch to VRAM
    //  VBK_REG = 1;

    //  // Switch out of VRAM
    //  VBK_REG = 0;

     // Set screen x,y pos to 0,0 and draw the map 20,18(size of the screen)
     set_bkg_tiles(0,0,20,18,creditscreenmap);

     // Show the background
     SHOW_BKG;

     // Turn the display on
     DISPLAY_ON; 
}

void fadeout(){
	wait_vbl_done();
	// looks like magic actually its changing the palette for the background
	// switching each colour in the palette to black step by step	
	for(i=0;i!=4;i++){
		switch(i){
			case 0:
				BGP_REG = 0xE4;
				break;
			case 1:
				BGP_REG = 0xF9;
				break;
			case 2:
				BGP_REG = 0xFE;
				break;
			case 3:
				BGP_REG = 0xFF;
				break;												
		}
		delay(100);
	}	
}

void fadein(){
	wait_vbl_done();
	// looks like magic actually its changing the palette for the background
	// switching each colour in the palette to white step by step
	// dont need to start at all back as will have been set that by 
	// fadeout
	for(i=1;i!=4;i++){
		switch(i){
			case 1:
				BGP_REG = 0xFE;
				break;
			case 2:
				BGP_REG = 0xF9;
				break;
			case 3:
				BGP_REG = 0xE4;
				break;											
		}
		delay(100);
	}	
}

// =========================================================
// Initialisation / reset functions at very start of game
// =========================================================
void showsplashandintro(){
	wait_vbl_done();
	enablesound();
	drawcreditsscreen();
	delay(2500);
	fadeout();
	drawsplashscreen();
	fadein();

	// set music playing in bg
 	disable_interrupts();
    add_TIM(playmusicnext);
    enable_interrupts();
    TAC_REG = 0x06; // Not sure what this actually does but it overrides a default for the timer I think
    set_interrupts(TIM_IFLAG|VBL_IFLAG);

	// wait for any of these buttons to be pressed
	waitpad(J_A|J_B|J_SELECT|J_START);
	
	
	// remove music time interupt handler
	disable_interrupts();
	remove_TIM(playmusicnext);		
}

void resetgame(UBYTE fadeenabled){
	if(fadeenabled) {
		fadeout();
	}
	else{
		DISPLAY_OFF;
	}
	
	gameover = 0;
	speed = 2;
	jumpindex = -1;
	screenpixeloffset = 0;
	lastobstacleindex = -1;

	//reset and empty obstacles
	for(k=0;k!=4;k++){
		obstacles[k].x=240;
		movecharactersprites(&obstacles[k],3,3,0);
		obstacles[k].initialized = 0;
	}

	// clear gameover off screen
	gameoversprite.x = 180;
	movecharactersprites(&gameoversprite,4,2,2);

	// reset sprites
	setupinitialwindow();
	setupinitialbackground(); // create initial background
	setupinitialsprites(); // create initial sprites
	clearscore();
	animatedino(1);
	drawhighscore();
	if(fadeenabled){
		fadein();
	}
	else{
		DISPLAY_ON;
	}
}

void setupinitialwindow(){
	// load window tiles
	set_win_data(11,36,Font);

	// write a clear sprite to every window block
	// write a clear sprite to every background block
	for (j=0 ; j != 32 ; j++){
		for (i=0 ; i != 32 ; i++){		
			set_win_tiles(i,j,1,1,blankmap);
		}
	}
	move_bkg(0,3);

	move_win(1,112);
	drawscore();
}

void setupinitialsprites(){
	set_sprite_data(0, 17, SpritesData);   /* defines the sprite data for all sprites */

	// create dino character
	// copy array of dinos sprite ids into dino.ids using memcpy
	memcpy(dino.spritemapids,dinospritemap, sizeof(dinospritemap)); 
	dino.x = 14;
	dino.y = 80;
	dino.width = 18; // technical sprites take up 24px but looks more like he hits at 18
	dino.height = 18; // technically 24 but again looks more like he hits at 18
	dino.startspriteid = 0;
	dino.initialized = 1;
	lastspriteid = 8; // dino fills 0-8
	setupcharactersprites(&dino,0); // & is saying pass a pointer to the function
	movecharactersprites(&dino,3,3,0);
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

	// generate up to two obstacles
	for(k=0;k!=2;k++){
		// get random number between 0 and 2
		// used to decide what obstacle to generate
		initrand(DIV_REG);
		randomnum = rand() % 3;
		
		// if randomnum is 2 then skip creating an obstacle, until we get to time > 30
		// and then do pterodactyl but only if first ostacle in pair
		if(randomnum!=2 || ((sys_time-laststarttime)/30 > 30 && k==0)){
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
			obstacles[currentindex].width = 6; // technically 8 but looks clearer and fairer it collisions calculated at 7
			obstacles[currentindex].height = 16;
			obstacles[currentindex].animated = 0;
			memcpy(obstacles[currentindex].spritemapidsanimated, 0, 9); // clear

			if(randomnum==0){
				//set large cacti sprite map
				memcpy(obstacles[currentindex].spritemapids,largecactispritemap, sizeof(largecactispritemap));
			}
			else if (randomnum==1){
				//set small cacti sprite map
				memcpy(obstacles[currentindex].spritemapids,smallcactispritemap, sizeof(smallcactispritemap));
			}
			//  generate pterodactyl
			else if(randomnum==2){
				obstacles[currentindex].animated = 1;
				obstacles[currentindex].y = 58;
				memcpy(obstacles[currentindex].spritemapids,pterodactylspritemap, sizeof(pterodactylspritemap));
				memcpy(obstacles[currentindex].spritemapidsanimated,pterodactylspritemapanimated, sizeof(pterodactylspritemapanimated)); 
			}

			// each obstacle loads 2 sprites so account for second
			lastspriteid++;

			// load the map images into sprites overwriting any previous ones
			setupcharactersprites(&obstacles[currentindex],0);
			movecharactersprites(&obstacles[currentindex],3,3,0);

			//skip 2nd obstacle (and set it to not be initialised) as we dont want a cati and pterodactyl together
			if(randomnum==2){
				break;
			}
		}
	}
}

void setupcharactersprites(struct PG* character, UBYTE showanimated){
	//loop map ids and load sprites where there is an id
	// -> are saying get a property from a pointer
	UBYTE currentspriteid = character->startspriteid;

	for(i=0;i!=sizeof(character->spritemapids);i++){
		if(character->spritemapids[i]!=255){ // check if sprite map is empty (255) or not
			if(showanimated){
				set_sprite_tile(currentspriteid,character->spritemapidsanimated[i]);
			}
			else{
				set_sprite_tile(currentspriteid,character->spritemapids[i]);
			}
			currentspriteid++;
		}
	}
}

void setupinitialbackground(){
	set_bkg_data(0, 11, BackgroundData); // load background data into tileset
	clearbackground(); // clear background so that all tiles are blank to start with

	set_bkg_tiles(0,10,32,1,map); // draw first background row
	set_bkg_tiles(0,11,32,1,&map[96]); // draw second background row	

	nextscene = 1; // set next backgroundscene to draw
	screenpixeloffset = 0; // set initial screen scroll offset
	lastscreenquadrantrendered = 0; // set the last screen quadrant rendered
}

// these are the bits that turn on and off features of the gameboy, sprites, backgrounds...
void updateSwitches() {
	SHOW_WIN;
	SHOW_SPRITES;
	SHOW_BKG;
	DISPLAY_ON;	
}

void makegameharder(UINT16 time){
	// at multiples of 100 score, pause generating obstacles
	// so that player has a change to adapt to new speed
	// only do it twice 3 times is impossible
	if(speed != 4){
		if(time != 0 && time % 100 == 0){
			skipgeneratingobstacles = 2;
		}
		// 3 times later increase the speed
		if((time - 3) != 0 && (time - 3) % 100 == 0){
			speed++;
		}	
	}
}

// =========================================================
// Animation utils
// =========================================================
UBYTE shouldrenderanimationframe(){
	return sys_time % 4 == 0;
}

// =========================================================
// Event handlers
// =========================================================

void checkjumping(){
	if(shouldrenderanimationframe()){ // TODO MOVE TO SHARED FUNCTION
		
		if(jumpindex > -1){
			dino.y= dino.y + jump_array[jumpindex];
			scrollcharactersprites(&dino,0,jump_array[jumpindex]);
			hasdinojustmovedy = 1;

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
			hasdinojustmovedy = 0;
		}
	}
}

void checkInput() {
	if(joypad() && apressed == 0 && running) // only want to jump once per keypress
	{
		apressed = 1;
		// dont jump if already jumping
		if(jumpindex==-1){
			playjump();
			jumpindex = 0;
		}
	}
	else if (joypad() && apressed == 1 && running)
	{
		// do nothing user is still pressing A
	}
	else if(joypad() && !running){
		// not running and they press A so start / reset
		if(gameover){
			resetgame(0);
		}
		laststarttime = sys_time;
		running = 1;
		apressed = 1;
	}
	else{
		// reset A press they have let go of button
		apressed = 0;
	}

	if (hasdinojustmovedy){
		// if only moved Y (jump) we still want to wait for 60
		hasdinojustmovedy = 0;
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

void playgameover(){
	//Sound : Game Over sound
	NR10_REG = 0x7D; //or 1E or 1D for louder sound / 2E / 3E / 4E... for more "vibe"
	NR11_REG = 0xBF;
	NR12_REG = 0xF6; //B7, C7, D7...F7 for longer sound
	NR13_REG = 0x7C;
	NR14_REG = 0x86;
}

//Define note names
typedef enum {
  C3, Cd3, D3, Dd3, E3, F3, Fd3, G3, Gd3, A3, Ad3, B3,
  C4, Cd4, D4, Dd4, E4, F4, Fd4, G4, Gd4, A4, Ad4, B4,
  C5, Cd5, D5, Dd5, E5, F5, Fd5, G5, Gd5, A5, Ad5, B5,
  C6, Cd6, D6, Dd6, E6, F6, Fd6, G6, Gd6, A6, Ad6, B6,
  C7, Cd7, D7, Dd7, E7, F7, Fd7, G7, Gd7, A7, Ad7, B7,
  C8, Cd8, D8, Dd8, E8, F8, Fd8, G8, Gd8, A8, Ad8, B8,
  SILENCE
} pitch;

const UWORD frequencies[] = { //values based on a formula used by the GB processor
  44, 156, 262, 363, 457, 547, 631, 710, 786, 854, 923, 986,
  1046, 1102, 1155, 1205, 1253, 1297, 1339, 1379, 1417, 1452, 1486, 1517,
  1546, 1575, 1602, 1627, 1650, 1673, 1694, 1714, 1732, 1750, 1767, 1783,
  1798, 1812, 1825, 1837, 1849, 1860, 1871, 1881, 1890, 1899, 1907, 1915,
  1923, 1930, 1936, 1943, 1949, 1954, 1959, 1964, 1969, 1974, 1978, 1982,
  1985, 1988, 1992, 1995, 1998, 2001, 2004, 2006, 2009, 2011, 2013, 2015,
  0
};

//Define Instrument names
//Instruments should be confined to one channel
//due to different registers used between ch1, 2, 3, 4
typedef enum {
	NONE,
	MELODY,  //channel 1
	HARMONY, //channel 1
	SNARE,   //channel 4
	CYMBAL   //channel 4
} instrument;

//Define a note as having a pitch, instrument, and volume envelope
typedef struct {
	instrument i;
	pitch p;
	UBYTE env;
} note;

//define a song as a series of note structs
//This song is a 16 note loop on channel 1
//each channel should have its own array, so
//that multiple notes can be played simultaneously
note song_ch1[40] = { //notes to be played on channel 1
	{NONE, SILENCE, 0x00U},
	{MELODY, D5, 0x83U},
	{MELODY, E5, 0x83U},
	{MELODY, G5, 0x83U},
	{MELODY, D5, 0x83U},
	{MELODY, E5, 0x83U},
	{MELODY, G5, 0x83U},	
	{NONE, SILENCE, 0x00U},
	{MELODY, B6, 0x83U},
	{MELODY, B6, 0x83U},
	{MELODY, A6, 0x83U},
	{MELODY, G6, 0x83U},	
	{NONE, SILENCE, 0x00U},
	{MELODY, D6, 0x83U},	
	{MELODY, Dd6, 0x83U},
	{MELODY, E6, 0x83U},

	{MELODY, D5, 0x83U},
	{NONE, SILENCE, 0x00U},	
	{MELODY, D5, 0x83U},
	{MELODY, E5, 0x83U},	
	{MELODY, G5, 0x83U},
	{MELODY, E5, 0x83U},	
	{NONE, SILENCE, 0x00U},	
	{MELODY, B4, 0x86U},
	{NONE, SILENCE, 0x00U},

	{MELODY, E5, 0x83U},	
	{MELODY, G5, 0x83U},		
	{MELODY, E5, 0x83U},	
	{MELODY, G5, 0x83U},
	{MELODY, E5, 0x83U},	
	{NONE, SILENCE, 0x00U},

	{MELODY, B4, 0x83U},
	{NONE, SILENCE, 0x00U},
	{MELODY, D5, 0x83U},	
	{MELODY, Dd5, 0x83U},
	{MELODY, E5, 0x83U},
	{NONE, SILENCE, 0x00U},
	{MELODY, E4, 0x77U},
	{NONE, SILENCE, 0x00U},
	{NONE, SILENCE, 0x00U},	
};

//function to set sound registers based on notes chosen
void setNote(note *n){
	switch((*n).i){
		case MELODY:
			NR10_REG = 0x00U; //pitch sweep
			NR11_REG = 0x84U; //wave duty
			NR12_REG = (*n).env; //envelope
			NR13_REG = (UBYTE)frequencies[(*n).p]; //low bits of frequency
			NR14_REG = 0x80U | ((UWORD)frequencies[(*n).p]>>8); //high bits of frequency (and sound reset)
		break;
	}
}

//This function plays whatever note is on
//the current beat in Channel 1
void playChannel1(){
	setNote(&song_ch1[currentBeat]);
	NR51_REG |= 0x11U; //enable sound on channel 1
}

//Timer function gets called 16 times a second
void playmusicnext(){
	if (timerCounter == 52){ // as on splashscreen and CPU looping fast only play every 350 cycles
		timerCounter=0;
		currentBeat = currentBeat == 40 ? 0 : currentBeat+1;
		playChannel1(); //every beat, play the sound for that beat
	}
	timerCounter++;
}