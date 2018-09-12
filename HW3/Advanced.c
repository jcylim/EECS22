#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "Advanced.h"

/* Add noise to image */
void Noise(int n, unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) {
	srand(time(NULL));
	int x, y;
	int count = n*WIDTH*HEIGHT/100;
	while(count>0) {
		x = rand() % WIDTH;
		y = rand() % HEIGHT;
		R[x][y] = B[x][y] = G[x][y] = 255; 
		count--;
	}
}

/* sharpen the image */
void Sharpen(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) {
    int R_copy[WIDTH][HEIGHT];
    int G_copy[WIDTH][HEIGHT];
    int B_copy[WIDTH][HEIGHT];
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            R_copy[x][y] = R[x][y];
            B_copy[x][y] = B[x][y];
            G_copy[x][y] = G[x][y]; 
        }
    }
    for (int x = 1; x < WIDTH-1; x++) {
        for (int y = 1; y < HEIGHT-1; y++) {
            int red = 9*R_copy[x][y]-R_copy[x-1][y-1]-R_copy[x][y-1]-R_copy[x+1][y-1]-R_copy[x-1][y]-R_copy[x+1][y]-R_copy[x-1][y+1]-R_copy[x][y+1]-R_copy[x+1][y+1];
            int green = 9*G_copy[x][y]-G_copy[x-1][y-1]-G_copy[x][y-1]-G_copy[x+1][y-1]-G_copy[x-1][y]-G_copy[x+1][y]-G_copy[x-1][y+1]-G_copy[x][y+1]-G_copy[x+1][y+1];
            int blue = 9*B_copy[x][y]-B_copy[x-1][y-1]-B_copy[x][y-1]-B_copy[x+1][y-1]-B_copy[x-1][y]-B_copy[x+1][y]-B_copy[x-1][y+1]-B_copy[x][y+1]-B_copy[x+1][y+1];
            if (red < 0) {
                red = 0;
            } else if (red > 255) {
                red = 255;
            }
            if (green < 0) {
                green = 0;
            } else if (green > 255) {
                green = 255;
            }
            if (blue < 0) {
                blue = 0;
            } else if (blue > 255) {
                blue = 255;
            }
            R[x][y] = red;
            G[x][y] = green; 
            B[x][y] = blue;
        }
    }
}

/* posterize the image */
void Posterize(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], unsigned int rbits, unsigned int gbits, unsigned int bbits) {
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            R[x][y] -= (pow(2, rbits) - 1);
            G[x][y] -= (pow(2, gbits) - 1);
            B[x][y] -= (pow(2, bbits) - 1);
        }
    }
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            R[x][y] += (pow(2, rbits-1) - 1);
            G[x][y] += (pow(2, gbits-1) - 1);
            B[x][y] += (pow(2, bbits-1) - 1);
        }
    }
}

/* motion blur */
/*void MotionBlur(int BlurAmount, unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) {

}
*/