typedef unsigned short u16; // Why are you doing this?
#define REG_DISPCTL *(unsigned short *) 0x4000000
#define MODE3 3
#define BG2_ENABLE(1<<10)
#define COLOR(r,g,b) ((r)  | (g) << 5 | (b) << 10)
#define RED COLOR (31,0,0)
#define GREEN COLOR(0,31,0)
#define BLUE COLOR(0,0,31)
#define CYAN COLOR(0,31,31)
#define MAGENTA COLOR(31,0,31)
#define YELLOW COLOR(31,31,0)
#define WHITE COLOR(31,31,31)
#define BLACK 0
#define OFFSET(r,c,numcols) ((r) * (numcols) + (c))

unsigned short *videoBuffer = (unsigned short *) 0X6000000; // this is the address of the video buffer, points to the video buffer

// prototype, YOU NEED PROTOTYPE TO RUN.
void setPixel( int row, int col, u16 color);
void drawRect(int row, int col, int height, int width); // the variable names in the prototype are not needed, just declare type
void delay (int n);
void boundCheck( int *var,int boundCheck, int *delta);


int maint () {
	REG_DISPCTL = MODE3 | BG2_ENABLE;
	int row,col,rd,cd,size;
	row = 80;
	col = 120;
	rd = 1;
	cd = 1;
	size = 5;

	setPixel(40, 60,YELLOW);
	drawRect(10,20,30,40);
	//*(unsigned short*) (0X6000000 + ( 19200 +120) * 2) = WHITE // multiplied by 2 because the it;s short
	//*(videoBuffer + OFFSET(80,120,240)) = WHITE;
	// this would be the same as the line above : videoBuffer[OFFSET(80,120,240)] = WHITE;
	while(1) // called game loop
	{
		row = row + rd;
		col = col + cd;
		drawRect(row, col, size, size, RED);
		delay(5)
		drawRect(row, col, size, size, BLACK ) // this would moving so fast that we would need delay above it
		boundCheck(&row, 159, &rd, size); // pass in the address of x ( which is &row) and address of delta ( which is &rd)
		boundCheck(&row, 239, &rd, size);
		// if (row < 0) {
		// 	row = 0;
		// 	rd = -rd;
		// }
		// if (row > 159) {     bound check function will take care of this part
		// 	row = 159;
		// 	rd = -rd;
		// }
		// if (col < 0) {
		// 	col = 0;
		// 	cd = -cd
		// }
		// if (col > 239) {
		// 	col = 239;
		// 	cd = -cd;
		// }
	}
}
void setPixel( int row, int col, u16 color){
	*(videoBuffer + OFFSET(row,col,240)) = color;
}
void drawRect(int row, int col, int height, int width, u16 color) {
	int r,c;
	for (r = 0; r < height, r++) {
		for (c = 0;c < width; c++) {
			setPixel(row + r, col + c, color);
		}
	}
}

void delay (int n, ){
	volatile int n; // volatile is telling the compiler to let you do what you wanted to do
	for (int i= 0; i < n*10000, i++) {
		x = x + 1;
	}
}
void boundCheck( int *var,int boundCheck, int *delta, int size) { // if you want to change the variable, you dont pass in the variable but pas in the address
	if (*var < 0) { // int size is the size of the ball to make the ball stop as soon as it goes to size and bottom
		*var = 0;
		*delta = - *delta;
	}
	if (*var > bound - size + 1) {
		*var = bound - size + 1;
		*delta = -*delta;
	}
	//return var; you dont need this any more
}

