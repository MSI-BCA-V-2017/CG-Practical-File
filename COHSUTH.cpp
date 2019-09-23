//C++ program to find category of line using Cohen-Sutherland
#include<iostream.h>
#include<conio.h>
#include<graphics.h>

const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

// Compute the bit code for a point (x, y) using the clip rectangle
// bounded diagonally by (xmin, ymin), and (xmax, ymax)

// xmax, xmin, ymax and ymin are global constants.
const int xmin = 200, ymin = 150, xmax = 400, ymax = 300;

int ComputeOutCode(double x, double y) {
	int code;

	code = INSIDE;          // initialised as being inside of [[clip window]]

	if (x < xmin)           // to the left of clip window
		code |= LEFT;
	else if (x > xmax)      // to the right of clip window
		code |= RIGHT;
	if (y < ymin)           // below the clip window
		code |= BOTTOM;
	else if (y > ymax)      // above the clip window
		code |= TOP;

	return code;
}

// Cohen–Sutherland clipping algorithm clips a line from
// P0 = (x0, y0) to P1 = (x1, y1) against a rectangle with 
// diagonal from (xmin, ymin) to (xmax, ymax).
void CohenSutherlandLineClip(double x0, double y0, double x1, double y1) {
	// compute outcodes for P0, P1, and whatever point lies outside the clip rectangle
	int outcode0 = ComputeOutCode(x0, y0);
	int outcode1 = ComputeOutCode(x1, y1);
	int accept = 0;

	while (1) {
		if (!(outcode0 | outcode1)) {
			// bitwise OR is 0: both points inside window; trivially accept and exit loop
			accept = 1;
			break;
		} else if (outcode0 & outcode1) {
			// bitwise AND is not 0: both points share an outside zone (LEFT, RIGHT, TOP,
			// or BOTTOM), so both must be outside window; exit loop (accept is false)
			break;
		} else {
			// failed both tests, so calculate the line segment to clip
			// from an outside point to an intersection with clip edge
			double x, y;

			// At least one endpoint is outside the clip rectangle; pick it.
			int outcodeOut = outcode0 ? outcode0 : outcode1;

			// Now find the intersection point;
			// use formulas:
			//   slope = (y1 - y0) / (x1 - x0)
			//   x = x0 + (1 / slope) * (ym - y0), where ym is ymin or ymax
			//   y = y0 + slope * (xm - x0), where xm is xmin or xmax
			// No need to worry about divide-by-zero because, in each case, the
			// outcode bit being tested guarantees the denominator is non-zero
			if (outcodeOut & TOP) {           // point is above the clip window
				x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
				y = ymax;
			} else if (outcodeOut & BOTTOM) { // point is below the clip window
				x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
				y = ymin;
			} else if (outcodeOut & RIGHT) {  // point is to the right of clip window
				y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
				x = xmax;
			} else if (outcodeOut & LEFT) {   // point is to the left of clip window
				y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0);
				x = xmin;
			}

			// Now we move outside point to intersection point to clip
			// and get ready for next pass.
			if (outcodeOut == outcode0) {
				x0 = x;
				y0 = y;
				outcode0 = ComputeOutCode(x0, y0);
			} else {
				x1 = x;
				y1 = y;
				outcode1 = ComputeOutCode(x1, y1);
			}
		}
	}
	if (accept) {
		// Following functions are left for implementation by user based on
		// their platform (OpenGL/graphics.h etc.)
		// DrawRectangle(xmin, ymin, xmax, ymax);
		// LineSegment(x0, y0, x1, y1);
		line(xmin, 0, xmin, getmaxy());
		line(xmax, 0, xmax, getmaxy());
		line(0, ymin, getmaxx(), ymin);
		line(0, ymax, getmaxx(), ymax);
		settextstyle(0, HORIZ_DIR, 0);
		outtextxy(xmin / 2, ymin / 2, "1001");
		outtextxy(3 * xmin / 2, ymin / 2,"1000");
		outtextxy(5 * xmin / 2, ymin / 2, "1010");
		outtextxy(xmin / 2, 3 * ymin / 2, "0001");
		outtextxy(3 * xmin / 2, 3 * ymin / 2, "0000");
		outtextxy(5 * xmin / 2, 3 * ymin / 2, "0010");
		outtextxy(xmin / 2, 5 * ymin / 2, "0101");
		outtextxy(3 * xmin / 2, 5 * ymin / 2, "0100");
		outtextxy(5 * xmin / 2, 5 * ymin / 2, "0110");
		outtextxy(x0, y0, " <- First point.");
		outtextxy(x1, y1, " <- Second point.");
		line(x0, y0, x1, y1);
	}
}

int main() {
	int gd = DETECT, gm;

	int x0, y0, x1, y1;

	cout << "xmin = " << xmin << " xmax = " << xmax << endl;
	cout << "ymin = " << ymin << " ymax = " << ymax << endl;

	cout << "Enter coordinates of P0: ";
	cin >> x0 >> y0;
	cout << "Enter coordinates of P1: ";
	cin >> x1 >> y1;

	initgraph (&gd, &gm, "C:\\TURBOC3\\BGI");

	CohenSutherlandLineClip(50, 80, 250, 250);

	getch();
	return 0;
}
