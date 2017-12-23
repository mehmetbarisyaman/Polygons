#include <stdio.h>
#include <stdlib.h>
#include <math.h>


float max(float a, float b) {
	if (a > b)
		return a;
	return b;
}
float min(float a, float b) {
	if (a < b)
		return a;
	return b;
}

int segment(float x1, float x2, float x3, float y1, float y2, float y3) {
	if ((x2 <= max(x1, x3)) && (x2 >= min(x1, x3)) && (y2 <= max(x1, x3)) && (y2 >= min(x1, x3)))
		return 1;
	return 0;
}


int orient(float x1, float x2, float x3, float y1, float y2, float y3) {
	float val = (y2 - y1) * (x3 - x2) - (x2 - x1) * (y3 - y2);
	if (val == 0)
		return 0;
	else if (val > 0)
		return 1;
	else
		return 2;
}


int intersect(float x1, float x2, float x3, float x4, float y1, float y2, float y3, float y4) {
	int o1 = orient(x1, x2, x3, y1, y2, y3);
	int o2 = orient(x1, x2, x4, y1, y2, y4);
	int o3 = orient(x3, x4, x1, y3, y4, y1);
	int o4 = orient(x3, x4, x2, y3, y4, y2);
	if ((o1 != o2) && (o3 != o4)) {
		return 1;
	}
	if ((o1 == 0) && (segment(x1, x3, x2, y1, y3, y2)==1))
		return 1;
	if ((o2 == 0) && (segment(x1, x4, x2, y1, y4, y2)==1))
		return 1;
	if ((o3 == 0) && (segment(x3, x1, x4, y3, y1, y4)==1))
		return 1;
	if ((o4 == 0) && (segment(x3, x2, x4, y3, y2, y4)==1))
		return 1;
	return 0;
}

int isOn(float x1, float x2, float xc, float y1, float y2, float yc) {
	float a1, a2, a3, a4, b1, b2;
	a1 = x1 - xc;
	a2 = x2 - xc;
	a3 = y1 - yc;
	a4 = y2 - yc;
	b1 = y1 - y2;
	b2 = x1 - x2;
	float sx1 = fabs(a1);
	float sx2 = fabs(a2);
	float sy1 = fabs(a3);
	float sy2 = fabs(a4);
	if ((sy1 + sy2 == fabs(b1)) && (sx1 + sx2 == fabs(b2))) {
		return 1;
	}
	else {
		return 0;
	}
}

int main() {
	float pointX = 0;
	float pointY = 0;
	int corners = 0;
	printf("Enter x and y coordinates of the point whose position is investigated: ");
	scanf("%f", &pointX);
	scanf("%f", &pointY);
	printf("\nEnter the number of corners for the polygon: ");
	scanf("%d", &corners);
	if (corners < 3) {
		printf("Not enough corners to form a polygon. \n");
		int exit;
		scanf("%d", &exit);
		return -1;
	}
	int i = 0;
	float x[50];
	float y[50];
	float a;
	float b;
	int j = 0;
	for (i = 0; i<corners; i++) {
		printf("\nEnter x and y coordinates of the %d.corner: ", i);
		scanf("%f", &a);
		scanf("%f", &b);
		for (j = 0; j < i; j++) {
			if ((x[j] == a) && (y[j] == b)) {
				printf("The terminal points of the line are same.These inputs do not form a line for the polygon!\n");
				int exit;
				scanf("%d", &exit);
				return -1;
			}
		}
		x[i] = a;
		y[i] = b;
	}
	int z = 0;
	for (i = 0; i < corners; i++) {
		z = i + 3;
		if (z == corners)
			break;
		if (intersect(x[i], x[i + 1], x[i + 2], x[z], y[i], y[i + 1], y[i + 2], y[z]) == 1) {
			printf("===== These lines do not form a simple connected polygon =====\n");
			int exit;
			scanf("%d", &exit);
			return -1;
		}	
	}
	for (i = 0; i<corners-1; i++) {
		if (isOn(x[i], x[i + 1], pointX, y[i], y[i + 1], pointY) == 1) {
			printf("===== The point is on the polygon ===== \n");
			int exit;
			scanf("%d", &exit);
			return 0;
		}
	}
	printf("The investigated point is not on the polygon.\n");
	int exit;
	scanf("%d", &exit);
	return 0;
}
