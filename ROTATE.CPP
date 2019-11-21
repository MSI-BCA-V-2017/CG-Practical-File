#include <iostream.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <dos.h>
#include <graphics.h>

char IncFlag;
int PolygonPoints[4][2] = {
	{10, 100},
	{110, 100},
	{110, 200},
	{10, 200}
};

void PolyLine(float angle) {
	int iCnt;
	cleardevice();
	line(0,240,640,240); // x axis
	line(320,0,320,480); // y axis
	char *buffer;
	for (iCnt=0; iCnt<4; iCnt++) {
		line(
			PolygonPoints[iCnt][0], PolygonPoints[iCnt][1], // drawing line from one vertex
			PolygonPoints[(iCnt+1)%4][0],PolygonPoints[(iCnt+1)%4][1] // to another
		);
	}
	outtextxy(320, 10, itoa(angle, buffer, 10));
}
void Rotate(float angle) {
	float Angle;
	int iCnt;
	int Tx, Ty; // 
	// cout << endl;
	Angle = angle*(22.0/7.0)/180.0;
	for (iCnt=0; iCnt<4; iCnt++) {
		Tx = PolygonPoints[iCnt][0];
		Ty = PolygonPoints[iCnt][1];
		PolygonPoints[iCnt][0] = (Tx - 320)*cos(Angle) - (Ty - 240)*sin(Angle) + 320;
		PolygonPoints[iCnt][1] = (Tx - 320)*sin(Angle) + (Ty - 240)*cos(Angle) + 240;
	}
}

void main() {
	int gDriver = DETECT, gMode;
	int iCnt;
	initgraph(&gDriver, &gMode, "C:\\TURBOC3\\BGI");
	settextstyle(0, 0, 1);
	for (iCnt=0; iCnt<4; iCnt++)
	{
		PolygonPoints[iCnt][0] += 320;
		PolygonPoints[iCnt][1] = 240 - PolygonPoints[iCnt][1];
	}
	PolyLine(0.0f);
	setcolor(WHITE);
	getch();
	float angle = 1.0f;
	for (int i = 1; i <= 30; i++, angle+=1.0f) {
		Rotate(angle);
		PolyLine(angle);
		delay(100);
		if (i % 5 == 0) 
			getch();
	}
	// Rotate(15.0f);
	// PolyLine(15.0f);
	// getch();
	// Rotate(30.0f);
	// PolyLine(30.0f);
	getch();
}