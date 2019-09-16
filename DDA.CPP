//C++ program for DDA line generation
#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<graphics.h>

//Function for finding absolute value
int abs (int n) {
	return ( (n>0) ? n : ( n * (-1)));
}

//DDA Function for line generation
void DDA(int X0, int Y0, int X1, int Y1) {
	// calculate dx & dy
	int dx = X1 - X0;
	int dy = Y1 - Y0;

	// calculate steps required for generating pixels
	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

	// calculate increment in x & y for each steps
	float Xinc = dx / (float) steps;
	float Yinc = dy / (float) steps;

	// Put pixel for each step
	float X = X0;
	float Y = Y0;
	for (int i = 0; i <= steps; i++) {
		putpixel (X,Y,RED); // put pixel at (X,Y)
		X += Xinc;		 // increment in x at each step
		Y += Yinc;		 // increment in y at each step
		delay(10);		 // for visualization of line-generation step by step
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

	// Initialize graphics function
	initgraph (&gd, &gm, "C:\\TURBOC3\\BGI");

	int x0 = transform(10), y0 = transform(12);
	int x1 = transform(20), y1 = transform(16);

	DDA(x0, y0, x1, y1);
	getch();
	return 0;
}