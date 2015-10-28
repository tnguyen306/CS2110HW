#include<stdio.h>
#include<stdlib.h>
#include "text.h"
#include <stdlib.h>
#include "mylib.h"
#include "buzz.h"
#include "GT.h"
#include "THWG.h"
#include "logic.h"

extern u16 *videoBuffer;


void setPixel(int r, int c, u16 color);
void drawRect(int r, int c, int width, int height, u16 color);
void drawHollowRect(int r, int c, int width, int height, u16 color);
void plotLine(int x0, int y0, int x1, int y1, u16 color);
void delay(int n);
void waitForVblank();
void drawString(int row, int col, char *str, unsigned short color);
void drawImage3(int r, int c, int width, int height, const volatile u16* image);
int height, width, row, col, gcol, grow;
int main(void) {
			
	REG_DISPCNT = MODE3 | BG2_ENABLE;
	
	
	drawImage3(0, 0, 240, 160, GT);
	drawString(55, 130, "PuzzleTime", BLACK);
	drawString(120, 0, "Press start to continue", BLACK);
	volatile int i = 0;
	//busy loop until the user presses the start button
	while(!KEY_DOWN_NOW(BUTTON_START)){
		i++;
	}
	drawRect(0,0, 240, 160, WHITE);
	drawString(20, 10, "Read the  Direction", BLACK);
	drawString(40, 10, "Up, Down, Left, Right", BLACK);
	drawString(60, 10, "Objective: cross to end of path", BLACK);
	drawString(80, 10, "Can't move outside the bounds of path", BLACK);
	drawString(105, 10, "Good luck!", BLACK);
	drawString(130, 10, "Press start to begin!!", CYAN);


	// for 10 seconds

	/*int g = 0;
	while(g < 10) {
		g++;
	}
	while(!KEY_DOWN_NOW(BUTTON_START)){
		i++;
	}
	*/
	
	// This will draw multiple images of smaller buzz picture

	while(!KEY_DOWN_NOW(BUTTON_START)){
		i++;
	}
	drawRect(0,0, 240, 160, WHITE);
	drawImage3(40,20, BUZZ_WIDTH, BUZZ_HEIGHT, buzz);
	drawImage3(60,50, BUZZ_WIDTH, BUZZ_HEIGHT, buzz);
	drawImage3(80,80, BUZZ_WIDTH, BUZZ_HEIGHT, buzz);
	drawImage3(100,110, BUZZ_WIDTH, BUZZ_HEIGHT, buzz);

	drawString(10, 10, "Level 1:", BLACK);
	drawString(20, 10, "Is Where You Die! ", BLACK);	
	drawString(30, 130, "Press Start", BLACK);
	drawString(45, 130, "To Begin", BLACK);

	//busy loop until the user presses the start button

	while(!KEY_DOWN_NOW(BUTTON_START)){
		i++;
	}
	restart:
	//draw the cyan background
	drawRect(0,0, 240, 160, CYAN);
	row = 30;
	col = 20;
	height = 15;
	width = 15;
	//draw the red game piece
	drawRect(row, col, width, height, RED);
    

	// this parts draw the maze
	drawRect(2, 20, 40,20, GREEN);
	drawRect(70, 80, 40,20, GREEN);
	drawRect(50, 90, 40, 20, GREEN);
	drawRect(60, 30, 40,20, GREEN);
	drawRect(0, 0, 40,20, GREEN);
	drawRect(70, 80, 40,20, GREEN);
	drawRect(10, 60, 40,20, GREEN);
	drawRect(0, 80, 40,20, GREEN);
	drawRect(100, 60, 40,20, GREEN);
	drawRect(70, 80, 40,20, GREEN);
	drawRect(50, 60, 40,20, GREEN);
	drawRect(60, 40, 40,20, GREEN);
	drawRect(160, 30, 40,20, GREEN);
	drawRect(160, 159, 40,20, GREEN);
	drawRect(70, 10, 40,20, GREEN);
	drawRect(10, 200, 40,20, GREEN);
	drawRect(0, 30, 40,20, GREEN);
	drawRect(150, 220, 40,20, GREEN);
	drawRect(140, 140, 40,30, GREEN);
	drawRect(130, 230, 40,20, GREEN);
	drawRect(160, 209, 40,60, GREEN);
	drawRect(160, 50, 80,20, GREEN);
	drawRect(10, 200, 40,20, GREEN);
	drawRect(80, 200, 40,20, GREEN);
	drawRect(150, 220, 40,20, GREEN);
	drawRect(40, 200, 40,80, GREEN);
	drawRect(50, 230, 40,20, GREEN);
	drawRect(50, 209, 40,50, GREEN);
	drawRect(750, 50, 40,50, GREEN);
	drawRect(90, 200, 40,20, GREEN);
	drawRect(100, 200, 40,20, GREEN);
	drawRect(50, 170, 40,20, GREEN);
	drawRect(50, 159, 40,50, GREEN);
	drawRect(750, 150, 40,50, GREEN);
	drawRect(90, 160, 40,20, GREEN);
	drawRect(100, 140, 40,20, GREEN);
	drawRect(150, 170, 40,50, GREEN);
	drawRect(75, 190, 40,50, GREEN);
	drawRect(70, 200, 40,20, GREEN);
	drawRect(10, 190, 40,20, GREEN);
	drawRect(160, 190, 40,50, GREEN);
	drawRect(160, 200, 40,20, GREEN);
	drawRect(150, 190, 40,20, GREEN);


	//coloumns and rows corresponding to green box
	//int grow, gcol;
	grow = 130;
	gcol = 200;
	drawRect(grow, gcol, 40,20, RED);
	// restart:
	int p = 1;
	while (p >= 1) {

	
		waitForVblank();

		//detecting collission with the goalpost, for going to next round
		//we will break out of the outer while loop
		if (col >= 200  && row >=  130) {
			p = 0;
			break;
		}
		if(KEY_DOWN_NOW(BUTTON_RIGHT))
		{
			int found = 0;
			for (int i = row; i < row + height; i++) {
				//detecting a collission with puzzle pieces, found keeps track of colllision found
				if (videoBuffer[OFFSET(i, col + width, 240)] == GREEN) {			
					found++;
					break;
				}
			}
			//if collission not found, can move to that spot, otherwise stay put
			if (found == 0) {			
					drawRect(row, col, height, width, CYAN);
					col = col + 1;
					drawRect(row, col, height, width, RED);
				} 
			
		}
		if(KEY_DOWN_NOW(BUTTON_LEFT))
		{
			int found = 0;
			for (int i = row; i < row + height; i++) {
				//detecting a collission, found keeps track of colllision found
				if (videoBuffer[OFFSET(i, col - 1, 240)] == GREEN) {			
					found++;
					break;
				}
			}
			//if collission not found, can move to that spot, otherwise stay put
			if (found == 0) {			
					drawRect(row, col, height, width, CYAN);
					col = col - 1;
					drawRect(row, col, height, width, RED);
				}
		}
		
		if(KEY_DOWN_NOW(BUTTON_UP))
		{
			int found = 0;
			for (int i = col; i < col + width; i++) {
				//detecting a collission, found keeps track of colllision found
				if (videoBuffer[OFFSET(row - 1, i, 240)] == GREEN) {			
					found++;
					break;
				}
			}
			//if collission not found, can move to that spot, otherwise stay put
			if (found == 0) {			
					drawRect(row, col, height, width, CYAN);
					row = row - 1;
					drawRect(row, col, height, width, RED);
				}
			
		}
		if(KEY_DOWN_NOW(BUTTON_DOWN))
		{	int found = 0;
			for (int i = col; i < col + width; i++) {
				//detecting a collission, found keeps track of colllision found
				if (videoBuffer[OFFSET(row + height, i, 240)] == GREEN) {		
					found++;
					break;
				}
			}
			//if collission not found, can move to that spot, otherwise stay put
			if (found == 0) {			
					drawRect(row, col, height, width, CYAN);
					row = row + 1;
					drawRect(row, col, height, width, RED);
				}
		}
		if (KEY_DOWN_NOW(BUTTON_A)) {
			goto restart;			
		}
		
		waitForVblank();

	}

	drawRect(0,0,240,160, BLACK);
	drawImage3(0,0, THWG_WIDTH, THWG_HEIGHT, THWG);

	drawString(10, 30, "Press start to continue to level 2 !!", WHITE);
	row = 30;
	col = 20;
	height = 15;
	width = 15;
	
	//busy loop until the user presses the start button
	while(!KEY_DOWN_NOW(BUTTON_START)){
		i++;
	}	
	backtoBeginning:
	drawRect(0,0,240,160, CYAN);
	//this is the location of the green ending zone
	int grow, gcol;
	grow = 130;
	gcol = 200;
	row = 30;
	col = 20;
	height = 10;
	width = 10;
	//draw the red game piece
	drawRect(row, col, width, height, RED);
	drawRect(grow, gcol, 50,20, RED);

	//draw the red game piece
	drawRect(row, col, width, height, RED);
    	// this draw the maze
	drawRect(2, 20, 40,20, GREEN);
	drawRect(70, 80, 40,20, GREEN);
	drawRect(50, 90, 40, 20, GREEN);
	drawRect(60, 30, 40,20, GREEN);
	drawRect(0, 0, 40,20, GREEN);
	drawRect(70, 80, 40,20, GREEN);
	drawRect(10, 60, 40,20, GREEN);
	drawRect(0, 80, 40,20, GREEN);
	drawRect(100, 60, 40,20, GREEN);
	drawRect(70, 80, 40,20, GREEN);
	drawRect(50, 60, 40,20, GREEN);
	drawRect(60, 40, 40,20, GREEN);
	drawRect(160, 30, 40,20, GREEN);
	drawRect(160, 159, 40,20, GREEN);
	drawRect(70, 10, 40,20, GREEN);
	drawRect(10, 200, 40,20, GREEN);
	drawRect(0, 30, 40,20, GREEN);
	drawRect(150, 220, 40,20, GREEN);
	drawRect(140, 140, 40,30, GREEN);
	drawRect(130, 230, 40,20, GREEN);
	drawRect(160, 209, 40,60, GREEN);
	drawRect(160, 50, 80,20, GREEN);
	drawRect(10, 200, 40,20, GREEN);
	drawRect(80, 200, 40,20, GREEN);
	drawRect(150, 220, 40,20, GREEN);
	drawRect(40, 200, 40,80, GREEN);
	drawRect(50, 230, 40,20, GREEN);
	drawRect(50, 209, 40,50, GREEN);
	drawRect(750, 50, 40,50, GREEN);
	drawRect(90, 200, 40,20, GREEN);
	drawRect(100, 200, 40,20, GREEN);
	drawRect(50, 170, 40,20, GREEN);
	drawRect(50, 159, 40,50, GREEN);
	drawRect(750, 150, 40,50, GREEN);
	drawRect(90, 160, 40,20, GREEN);
	drawRect(100, 140, 40,20, GREEN);
	drawRect(150, 170, 40,50, GREEN);
	drawRect(75, 190, 40,50, GREEN);
	drawRect(70, 200, 40,20, GREEN);
	drawRect(10, 190, 40,20, GREEN);
	drawRect(160, 190, 40,50, GREEN);
	drawRect(160, 200, 40,20, GREEN);
	drawRect(150, 190, 40,20, GREEN);
	drawRect(70, 200, 40,20, GREEN);
	drawRect(100, 24, 40,20, GREEN);
	drawRect(160, 140, 40,50, GREEN);
	drawRect(160, 200, 40,20, GREEN);
	drawRect(140, 190, 40,20, GREEN);
	p =1;
	while (p >= 1) {

	
		waitForVblank();
		
		//detecting collission with the goalpost, for going to next round
		//we will break out of the outer while loop
		if (col == 200 && row ==  128) {
			p = 0;
			break;
		}
		//makes it bigger
		/*
			if(KEY_DOWN_NOW(BUTTON_A))
		{	
			int found = 0;
			for (int i = row; i < row + height; i++) {
				//detecting a collission with puzzle pieces, found keeps track of colllision found
				if (videoBuffer[OFFSET(i, col + width, 240)] == GREEN) {			
					found++;
					break;
				}
			}
			//if collission not found, can move to that spot, otherwise stay put
			if (found == 0) {			
					
				drawRect(row, col, height, width, CYAN);
				
				if (height >= 1 && height < 240) {
					height++;
				}
			
				drawRect(row, col, height, width, RED);
				
		}
		}
		makes it smaller
			if(KEY_DOWN_NOW(BUTTON_B))
		{

			drawRect(row, col, height, width, CYAN);
			if (height >= 1 && height < 240) {
				height--;
			}
			drawRect(row, col, height, width, RED);
			
		}
		*/
		if(KEY_DOWN_NOW(BUTTON_RIGHT))
		{
			int found = 0;
			for (int i = row; i < row + height; i++) {
			// find collision and mark it
				if (videoBuffer[OFFSET(i, col + width, 240)] == GREEN) {			
					found++;
					break;
				}
			}
			//if collission not found, can move to that spot, otherwise stay put
			if (found == 0) {			
					drawRect(row, col, height, width, CYAN);
					col = col + 1;
					drawRect(row, col, height, width, RED);
				} 
			
		}
		if(KEY_DOWN_NOW(BUTTON_LEFT))
		{
			int found = 0;
			for (int i = row; i < row + height; i++) {
			//find collision and mark it
				if (videoBuffer[OFFSET(i, col - 1, 240)] == GREEN) {			
					found++;
					break;
				}
			}
			//if collission not found, can move to that spot, otherwise stay put
			if (found == 0) {			
					drawRect(row, col, height, width, CYAN);
					col = col - 1;
					drawRect(row, col, height, width, RED);
				}
		}
		
		if(KEY_DOWN_NOW(BUTTON_UP))
		{
			int found = 0;
			for (int i = col; i < col + width; i++) {
				//find collision and mark it
				if (videoBuffer[OFFSET(row - 1, i, 240)] == GREEN) {			
					found++;
					break;
				}
			}
			//if collission not found, can move to that spot, otherwise stay put
			if (found == 0) {			
					drawRect(row, col, height, width, CYAN);
					row = row - 1;
					drawRect(row, col, height, width, RED);
				}
			
		}
		if(KEY_DOWN_NOW(BUTTON_DOWN))
		{	int found = 0;
			for (int i = col; i < col + width; i++) {
				//find collision and mark it
				if (videoBuffer[OFFSET(row + height, i, 240)] == GREEN) {			
					found++;
					break;
				}
			}
			//if collission not found, can move to that spot, otherwise stay put
			if (found == 0) {			
					drawRect(row, col, height, width, CYAN);
					row = row + 1;
					drawRect(row, col, height, width, RED);
				}
		}
		if (KEY_DOWN_NOW(BUTTON_A)) {
			goto backtoBeginning;
		}
		waitForVblank();

	}
	drawRect(0,0,240,160, BLACK);
	drawImage3(0,0, THWG_WIDTH, THWG_HEIGHT, THWG);
	drawString(10, 30, "DAM, GGGGGGGGGGGGGGGGGGGGGGGG!!", WHITE);

}


			
