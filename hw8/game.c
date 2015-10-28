typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned char u8;

extern unsigned short *videoBuffer;
/* Buttons */

#define BUTTON_A      (1<<0)
#define BUTTON_B      (1<<1)
#define BUTTON_SELECT (1<<2)
#define BUTTON_START  (1<<3)
#define BUTTON_RIGHT  (1<<4)
#define BUTTON_LEFT   (1<<5)
#define BUTTON_UP     (1<<6)
#define BUTTON_DOWN   (1<<7)
#define BUTTON_R      (1<<8)
#define BUTTON_L      (1<<9)



#define BUTTONS (*( volatile unsigned int *)0x04000130)
//nonzero if on
#define KEY_DOWN_NOW(key)  (~(BUTTONS) & key)

#define SCANLINECOUNTER (*(volatile unsigned short *)0x4000006)

#define REG_DISPCNT *(u16 *)0x4000000
#define MODE3 3
#define BG2_ENABLE (1<<10)

#define RGB(r,g,b) ((r) | (g) << 5 | (b) << 10)
#define RED RGB(31,0,0)
#define WHITE RGB(31,31,31)
#define GREEN RGB(0,31,0)
#define BLUE RGB(0,0,31)
#define CYAN RGB(0,31,31)
#define MAGENTA RGB(31,0,31)
#define YELLOW RGB(31,31,0)
#define BLACK RGB(0,0,0)

void firstLevel();
void setPixel(int r, int c, u16 color);
void drawRect(int r, int c, int width, int height, u16 color);
void drawHollowRect(int r, int c, int width, int height, u16 color);
void plotLine(int x0, int y0, int x1, int y1, u16 color);
void delay(int n);
void waitForVblank();
void secondLevel();

void firstLevel() {
	int p = 1;
	while (p <= 1) {
		int size = 5;
		int rwin, bwin, row, col, oldRow, oldCol, brow, bcol, boldRow, boldCol, ycol, yrow;
		size++;
		rwin = 0;
		bwin = 0;
		ycol = 65;
		yrow = 65;
		
		waitForVblank();
		//draw the green background
		drawRect(0,0, 240, 160, GREEN);
		
		//draw the yellow goal state
		drawRect(yrow, ycol, 10,10, YELLOW);
		
		//draw the red and yellow players
		drawRect(100, 10, 10, 10, RED);
		drawRect(10, 20, 10, 10, BLUE);
		oldCol = 0;
		oldRow = 0;
		row = 100;
		col = 10;

		boldCol = 0;
		boldRow = 0;
		brow = 10;
		bcol = 20;
		//looping to keep moving the red and blue players to reach the yellow goal
			
			//drawRect(100, 10, 20, 50, RED);
			
			//drawRect(row, col, size, size, color);
		if(KEY_DOWN_NOW(BUTTON_RIGHT))
		{
			if (row <= 160 && col <= 240 && row >= 0 && col >= 0) {			
			drawRect(0,0, 240, 160, GREEN);
			drawRect(yrow, ycol, 10,10, YELLOW);
			drawRect(brow, bcol, 10, 10, BLUE);
			col = col + 1;
			drawRect(row, col, 10, 10, RED);
			} else {
				drawRect(0,0, 240, 160, GREEN);	
				drawRect(yrow, ycol, 10,10, YELLOW);	
				drawRect(brow, bcol, 10, 10, BLUE);
				row = 50;
				col = 50;				
				drawRect(row, col, 10, 10, RED);			
			}
			
		}
		if(KEY_DOWN_NOW(BUTTON_LEFT))
		{
			if (row <= 160 && col <= 240 && row >= 0 && col >= 0) {			
			drawRect(0,0, 240, 160, GREEN);
			drawRect(yrow, ycol, 10,10, YELLOW);
			drawRect(brow, bcol, 10, 10, BLUE);
			col = col - 1;
			drawRect(row, col-3, 10, 10, RED);
			} else {
				drawRect(0,0, 240, 160, GREEN);
				drawRect(yrow, ycol, 10,10, YELLOW);			
				drawRect(brow, bcol, 10, 10, BLUE);
				row = 50;
				col = 50;				
				drawRect(row, col, 10, 10, RED);			
			}
		}

		if(KEY_DOWN_NOW(BUTTON_UP))
		{
			if (row <= 160 && col <= 240 && row >= 0 && col >= 0) {			
			drawRect(0,0, 240, 160, GREEN);
			drawRect(yrow, ycol, 10,10, YELLOW);
			drawRect(brow, bcol, 10, 10, BLUE);	
			row = row - 1;	
			drawRect(row, col, 10, 10, RED);
			} else {
				drawRect(0,0, 240, 160, GREEN);
				drawRect(yrow, ycol, 10,10, YELLOW);
				drawRect(brow, bcol, 10, 10, BLUE);
				row = 50;
				col = 50;				
				drawRect(row, col, 10, 10, RED);			
			}
			
		}
		if(KEY_DOWN_NOW(BUTTON_DOWN))
		{
			if (row <= 160 && col <= 240 && row >= 0 && col >= 0) {			
			drawRect(0,0, 240, 160, GREEN);
			drawRect(yrow, ycol, 10,10, YELLOW);	
			drawRect(brow, bcol, 10, 10, BLUE);
			row = row + 1;
			drawRect(row, col, 10, 10, RED);
			} else {
				drawRect(0,0, 240, 160, GREEN);
				drawRect(yrow, ycol, 10,10, YELLOW);
				drawRect(brow, bcol, 10, 10, BLUE);
				row = 50;
				col = 50;				
				drawRect(row, col, 10, 10, RED);			
			}
		}
		
		if(KEY_DOWN_NOW(BUTTON_R))
		{
			if (brow <= 160 && bcol <= 240 && brow >= 0 && bcol >= 0) {			
			drawRect(0,0, 240, 160, GREEN);
			drawRect(yrow, ycol, 10,10, YELLOW);
			drawRect(row, col, 10, 10, RED);
			bcol = bcol + 1;
			drawRect(brow, bcol, 10, 10, BLUE);
			} else {
				drawRect(0,0, 240, 160, GREEN);	
				drawRect(yrow, ycol, 10,10, YELLOW);
				drawRect(row, col, 10, 10, RED);
				brow = 80;
				bcol = 190;	
				drawRect(brow, bcol, 10, 10, BLUE);			
			}
			
		}
		if(KEY_DOWN_NOW(BUTTON_L))
		{
			if (brow <= 160 && bcol <= 240 && brow >= 0 && bcol >= 0) {			
			drawRect(0,0, 240, 160, GREEN);
			drawRect(yrow, ycol, 10,10, YELLOW);
			drawRect(row, col, 10, 10, RED);
			bcol = bcol - 1;
			drawRect(brow, bcol, 10, 10, BLUE);
			} else {
				drawRect(0,0, 240, 160, GREEN);	
				drawRect(yrow, ycol, 10,10, YELLOW);
				drawRect(row, col, 10, 10, RED);
				brow = 80;
				bcol = 190;	
				drawRect(brow, bcol, 10, 10, BLUE);		
			}
		}

		if(KEY_DOWN_NOW(BUTTON_A))
		{
			if (brow <= 160 && bcol <= 240 && brow >= 0 && bcol >= 0) {			
			drawRect(0,0, 240, 160, GREEN);
			drawRect(yrow, ycol, 10,10, YELLOW);
			drawRect(row, col, 10, 10, RED);
			brow = brow - 1;
			drawRect(brow, bcol, 10, 10, BLUE);
			} else {
				drawRect(0,0, 240, 160, GREEN);	
				drawRect(yrow, ycol, 10,10, YELLOW);
				drawRect(row, col, 10, 10, RED);
				brow = 80;
				bcol = 190;	
				drawRect(brow, bcol, 10, 10, BLUE);		
			}
			
		}
		if(KEY_DOWN_NOW(BUTTON_B))
		{
			if (brow <= 160 && bcol <= 240 && brow >= 0 && bcol >= 0) {			
			drawRect(0,0, 240, 160, GREEN);
			drawRect(yrow, ycol, 10,10, YELLOW);
			drawRect(row, col, 10, 10, RED);
			brow = brow + 1;
			drawRect(brow, bcol, 10, 10, BLUE);
			} else {
				drawRect(0,0, 240, 160, GREEN);	
				drawRect(yrow, ycol, 10,10, YELLOW);
				drawRect(row, col, 10, 10, RED);
				brow = 80;
				bcol = 190;	
				drawRect(brow, bcol, 10, 10, BLUE);		
			}
		}
		if (brow == row && bcol == col && bcol != ycol  && bcol != ycol) {	
			row = 190;
			col = 100	;	
			drawRect(0,0, 240, 160, GREEN);	
			drawRect(row, col, 10, 10, RED);
			drawRect(yrow, ycol, 10,10, YELLOW);
			brow = 10; 
			bcol = 20;
			drawRect(brow, bcol, 10, 10, BLUE);		
		}
		//checking if either of the entitites reachedthe yellow goal state, increment their win pts
		//and then start the next level
		if ((brow == yrow && bcol == ycol) || (row == yrow && col == ycol) ) {	
			//bwin = (brow == yrow && bcol == ycol) ? bwin++ : bwin;
			//rwin = (brow == yrow && bcol == ycol) ? rwin : rwin++;		
			p = 2;		
		}
		//waitForVblank();
	}
}


void secondLevel() {

	//draw the cyan background
	drawRect(0,0, 240, 160, CYAN);
	//drawing the goal state
	drawRect(54, 189, 10, 10, YELLOW);
	//draw the boxes for the "puzzle blocking thingies"
	drawRect(10,110, 30, 10, BLUE);
	drawRect(100,10, 30, 20, BLUE);
	drawRect(20,50, 10, 20, BLUE);
	drawRect(160,40, 30, 20, BLUE);
	drawRect(20,100, 10, 20, BLUE);
	drawRect(30,60, 40, 20, BLUE);
	waitForVblank();

	int p = 1;
	while (p <= 1) {
	int size = 5;
	int row, col, ycol, yrow, rwin, bwin;
	row = 100;
	col = 10;
	//int rwin, bwin, row, col, oldRow, oldCol, brow, bcol, boldRow, boldCol, ycol, yrow;
	size++;
	rwin = 0;
	bwin = 0;
	ycol = 65;
	yrow = 65;
	
	
		if(KEY_DOWN_NOW(BUTTON_RIGHT))
		{
			if (row <= 160 && col <= 240 && row >= 0 && col >= 0) {			
				drawRect(0,0, 240, 160, CYAN);
				//drawing the goal state
				drawRect(54, 189, 10, 10, YELLOW);
				//draw the boxes for the "puzzle blocking thingies"
				drawRect(10,110, 30, 10, BLUE);
				drawRect(100,10, 30, 20, BLUE);
				drawRect(20,50, 10, 20, BLUE);
				drawRect(160,40, 30, 20, BLUE);
				drawRect(20,100, 10, 20, BLUE);
				drawRect(30,60, 40, 20, BLUE);
			} else {
				p++;
				p--;			
			}
			
		}
		if(KEY_DOWN_NOW(BUTTON_LEFT))
		{
			if (row <= 160 && col <= 240 && row >= 0 && col >= 0) {			
				drawRect(0,0, 240, 160, CYAN);
				//drawing the goal state
				drawRect(54, 189, 10, 10, YELLOW);
				//draw the boxes for the "puzzle blocking thingies"
				drawRect(10,110, 30, 10, BLUE);
				drawRect(100,10, 30, 20, BLUE);
				drawRect(20,50, 10, 20, BLUE);
				drawRect(160,40, 30, 20, BLUE);
				drawRect(20,100, 10, 20, BLUE);
				drawRect(30,60, 40, 20, BLUE);
			} else {
				p++;
				p--;
				
			}
		}

		if(KEY_DOWN_NOW(BUTTON_UP))
		{
			if (row <= 160 && col <= 240 && row >= 0 && col >= 0) {			
				drawRect(0,0, 240, 160, CYAN);
				//drawing the goal state
				drawRect(54, 189, 10, 10, YELLOW);
				//draw the boxes for the "puzzle blocking thingies"
				drawRect(10,110, 30, 10, BLUE);
				drawRect(100,10, 30, 20, BLUE);
				drawRect(20,50, 10, 20, BLUE);
				drawRect(160,40, 30, 20, BLUE);
				drawRect(20,100, 10, 20, BLUE);
				drawRect(30,60, 40, 20, BLUE);
			} else {
				p++;
				p--;			
			}
			
		}
		if(KEY_DOWN_NOW(BUTTON_DOWN))
		{
			if (row <= 160 && col <= 240 && row >= 0 && col >= 0) {			
				drawRect(0,0, 240, 160, CYAN);
				//drawing the goal state
				drawRect(54, 189, 10, 10, YELLOW);
				//draw the boxes for the "puzzle blocking thingies"
				drawRect(10,110, 30, 10, BLUE);
				drawRect(100,10, 30, 20, BLUE);
				drawRect(20,50, 10, 20, BLUE);
				drawRect(160,40, 30, 20, BLUE);
				drawRect(20,100, 10, 20, BLUE);
				drawRect(30,60, 40, 20, BLUE);
			} else {
				p++;
				p--;			
			}
		}
		

	}
	
}

