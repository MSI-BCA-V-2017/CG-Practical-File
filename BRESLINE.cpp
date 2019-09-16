//C++ program for Bresenham's line drawing algorithm
#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<graphics.h>

//Bresenham function for line drawing
void Bresenham(int x0, int y0, int x1, int y1) {
	//calculate dx and dy
	int dx = x1 - x0;
	int dy = y1 - y0;

	//initialise x and y
	int x = x0, y = y0;

	//calculate decision parameter
	int D = 2 * dy - dx;

	//putpixel for each step
	while (x < x1) {
		//for positive D
		if (D >= 0) {
			putpixel(x, y, RED);
			y += 1;
			D += 2 * (dy - dx);
		}
		//for negative D 
		else {
			putpixel(x, y, RED);
			D += 2 * dy;
			x += 1;
		}
		delay(10); //for visualisation
	}
}

// transforming point
int transform(int p) {
    int translate = 10;
    int scale = 10;
    return scale * (p + translate);
}

int main() {
	int gd = DETECT, gm;
	initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

	int x0 = transform(10), y0 = transform(12);
	int x1 = transform(20), y1 = transform(16);

	Bresenham(x0, y0, x1, y1);
	getch();
	return 0;
}