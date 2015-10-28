#include <stdlib.h>
#include "mylib.h"

u16* videoBuffer = (u16*) 0x6000000;

void setPixel(int r, int c, u16 color) {
	videoBuffer[OFFSET(r, c, 240)] = color;
}

//A function to draw a FILLED rectangle starting at (r,c)
void drawRect(int r, int c, int width, int height, u16 color) {
	int i, j;
	for(i = 0; i < height; i++)
	{
		for(j = 0; j < width; j++)
		{
			setPixel(i + r, j + c, color);
		}
	}

}
//A function to draw a HOLLOW rectangle starting at (r,c), O(w+h)
void drawHollowRect(int r, int c, int width, int height, u16 color) {

	int i, j;
	for(i = 0; i <= height; i++)
	{
		setPixel(i + r, c, color);
		setPixel(i + r, c + width, color);
	}

	for(j = 0; j <= width; j++)
	{
		setPixel(r, j + c, color);
		setPixel(r + height, j + c, color);
	}
}
/*Implementation of Bresenham's Line Algorithm that only
* uses addition, subtraction, and bit shifting operations; 
* Multiplication and division are not allowed. 
*/
void plotLine(int x0, int y0, int x1, int y1, u16 color) {
	
	// delta of exact value and rounded value of the dependant variable
        int d = 0;
 
  	int dy = 0;
	if (y1 > y0) {
		dy = y1 - y0;
	} else {
		dy = y0 - y1;	
	}
        
	int dx = 0
;
	if (x1 > x0) {
		dx = x1 - x0;
	} else {
		dy = x0 - x1;	
	}
 
        int dy1 = (dy << 1); // slope scaling factors to avoid floating
        int dx1 = (dx << 1); // point
 
        int ix = x0 < x1 ? 1 : -1; // increment direction
        int iy = y0 < y1 ? 1 : -1;
 
        if (dy <= dx) {
            for (;;) {
                setPixel(x0, y0, color);
                if (x0 == x1)
                    break;
                x0 += ix;
                d += dy1;
                if (d > dx) {
                    y0 += iy;
                    d -= dx1;
                }
            }
        } else {
            for (;;) {
                setPixel(x0, y0, color);
                if (y0 == y1)
                    break;
                y0 += iy;
                d += dx1;
                if (d > dy) {
                    x0 += ix;
                    d -= dy1;
                }
            }
        }
}

// 
void delay(int n)
{
	volatile int i;
	for(i=0; i<n*10000; i++)
	{
	
	}
}

void drawImage3(int row, int col, int width, int height, const volatile u16* image) {
	//int r;
	for(int r =0; r<height; r++) {
		DMA[3].src = image + r* width; //color?
		DMA[3].dst = &videoBuffer[OFFSET(row+r, col, 240)];
		DMA[3].cnt = width | DMA_ON;
	}
}


void waitForVblank()
{
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 160);
}