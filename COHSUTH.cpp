//C++ program to find category of line using Cohen-Sutherland
#include<iostream.h>
#include<conio.h>

const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

// Compute the bit code for a point (x, y) using the clip rectangle
// bounded diagonally by (xmin, ymin), and (xmax, ymax)

// xmax, xmin, ymax and ymin are global constants.
const int xmin = 100, ymin = 100, xmax = 300, ymax = 300;

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

	cout << "Clipping line from (" << x0 << ", " << y0 << ") to (";
	cout << x1 << ", " << y1 << ")" << endl;

	if (!(outcode0 | outcode1)) {
		// bitwise OR is 0: both points inside window; trivially accept and exit loop
		// accept = true;
		cout << "Line inside the window!" << endl;
		// break;
	} else if (outcode0 & outcode1) {
		// bitwise AND is not 0: both points share an outside zone (LEFT, RIGHT, TOP,
		// or BOTTOM), so both must be outside window; exit loop (accept is false)
		cout << "Line outside the window!"  << endl;
		// break;
	} else {
		// failed both tests, so calculate the line segment to clip
		// from an outside point to an intersection with clip edge
		cout << "Line partially inside the window! Clpping candidate!" << endl;
	}
}

int main() {
	clrscr();
	cout << "Viewport dimensions:";
	cout << " (" << xmin << ", " << ymin << ") to (";
	cout << xmax << ", " << ymax << ")" << endl;
	CohenSutherlandLineClip(110, 120, 250, 245);
	CohenSutherlandLineClip(50, 50, 200, 50);
	CohenSutherlandLineClip(80, 95, 125, 160);
	getch();
	return 0;
}
