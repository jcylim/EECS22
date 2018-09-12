#include "DIPs.h"
#include "Constants.h"
#include "Image.h"

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

/* Example of DIP */
/* make the picture color black & white */
IMAGE *BlackNWhite(IMAGE *image) {
    int tmp;
    int WIDTH = ImageWidth(image);
    int HEIGHT = ImageHeight(image);
    for (int y = 0; y < HEIGHT; y++)
    {   
        for (int x = 0; x < WIDTH; x++) 
        {
            tmp = (GetPixelR(image,x,y) + GetPixelB(image,x,y) + GetPixelG(image,x,y)) / 3;
            SetPixelR(image,x,y,tmp);
            SetPixelB(image,x,y,tmp);
            SetPixelG(image,x,y,tmp);
        }
    }
}

/* reverse image color */
IMAGE *Negative(IMAGE *image) {
    int x, y;
    int WIDTH = ImageWidth(image);
    int HEIGHT = ImageHeight(image);
    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            SetPixelR(image, x, y, MAX_PIXEL - GetPixelR(image, x, y));
            SetPixelG(image, x, y, MAX_PIXEL - GetPixelG(image, x, y));
            SetPixelB(image, x, y, MAX_PIXEL - GetPixelB(image, x, y));
        }
    }
}

/*colorfiler */
IMAGE *ColorFilter (IMAGE *image, int target_g, int target_b, int threshold, int replace_r, int replace_g, int replace_b) {
    replace_r = (replace_r > MAX_PIXEL)? MAX_PIXEL : (replace_r < 0) ? 0 : replace_r;
    replace_r = (replace_r > MAX_PIXEL)? MAX_PIXEL : (replace_r < 0) ? 0 : replace_r;
    replace_r = (replace_r > MAX_PIXEL)? MAX_PIXEL : (replace_r < 0) ? 0 : replace_r;
    int WIDTH = ImageWidth(image);
    int HEIGHT = ImageHeight(image);
    int x, y;
    for (y = 0; y < HEIGHT; y++){
        for (x = 0; x < WIDTH; x++){
            if (abs(GetPixelR(image, x, y) - target_r) <= threshold
                    && abs(GetPixelG(image, x, y) - target_g) <= threshold
                    && abs(GetPixelB(image, x, y) - target_b) <= threshold) {
                SetPixelR(image, x, y, replace_r);
                SetPixelG(image, x, y, replace_g);
                SetPixelB(image, x, y, replace_b);
            }
        }
    }
}

/* Add edge to the image*/
IMAGE *Edge(IMAGE *image) {
    int             x, y, m, n, a, b;
    unsigned char   tmpR[WIDTH][HEIGHT];
    unsigned char   tmpG[WIDTH][HEIGHT];
    unsigned char   tmpB[WIDTH][HEIGHT];
    int WIDTH = ImageWidth(image);
    int HEIGHT = ImageHeight(image);
    IMAGE *tmpImage = CreateImage(image);
    for (y = 0; y < HEIGHT; y++){
        for (x = 0; x < WIDTH; x++) {
            tmpR[x][y] = GetPixelR(tmpImage, x, y);
            tmpG[x][y] = GetPixelG(tmpImage, x, y);
            tmpB[x][y] = GetPixelB(tmpImage, x, y);
        }
    }
    int sumR = 0;   /* sum of the intensity differences with neighbors */
    int sumG = 0;
    int sumB = 0;
    int sum2R = 0;  
    int sum2G = 0;
    int sum2B = 0;
    for (y = 1; y < HEIGHT - 1; y++){
        for (x = 1; x < WIDTH - 1; x++){
            for (n = -1; n <= 1; n++){
                for (m = -1; m <= 1; m++) {
                    a = (x + m >= WIDTH) ? WIDTH - 1 : (x + m < 0) ? 0 : x + m;
                    b = (y + n >= HEIGHT) ? HEIGHT - 1 : (y + n < 0) ? 0 : y + n;
                    sumR += (tmpR[x][y] - tmpR[a][b]);
                    sumG += (tmpG[x][y] - tmpG[a][b]);
                    sumB += (tmpB[x][y] - tmpB[a][b]);
                }
            }
            sum2R = (sumR > MAX_PIXEL) ? MAX_PIXEL: (sumR < 0) ? 0: sumR;;  
            sum2G = (sumG > MAX_PIXEL) ? MAX_PIXEL: (sumG < 0) ? 0: sumG;
            sum2B = (sumB > MAX_PIXEL) ? MAX_PIXEL: (sumB < 0) ? 0: sumB;
            SetPixelR(tmpImage, x, y, sum2R);
            SetPixelG(tmpImage, x, y, sum2G);
            SetPixelB(tmpImage, x, y, sum2B);
            sumR = sumG = sumB = 0;
        }
    }
    /* set all four borders to 0 */
    for (y = 0; y < HEIGHT; y++) {
        SetPixelR(image, 0, y, 0);
        SetPixelG(image, 0, y, 0);
        SetPixelB(image, 0, y, 0);
        SetPixelR(image, WIDTH-1, y, 0);
        SetPixelG(image, WIDTH-1, y, 0);
        SetPixelB(image, WIDTH-1, y, 0);
    }
    for (x = 0; x < WIDTH; x++) {
        SetPixelR(image, x, 0, 0);
        SetPixelG(image, x, 0, 0);
        SetPixelB(image, x, 0, 0);
        SetPixelR(image, x, HEIGHT - 1, 0);
        SetPixelG(image, x, HEIGHT - 1, 0);
        SetPixelB(image, x, HEIGHT - 1, 0);
    }
}

/* flip image vertically */
IMAGE *VFlip(IMAGE *image)
{
    int             x, y;
    unsigned char   r, g, b;
    int WIDTH = ImageWidth(image);
    int HEIGHT = ImageHeight(image);
    
    for (y = 0; y < HEIGHT/2; y ++) 
    {
        for (x = 0; x < WIDTH; x ++) 
        {
            r = GetPixelR(image, x, HEIGHT - 1 - y);
            g = GetPixelG(image, x, HEIGHT - 1 - y);
            b = GetPixelR(image, x, HEIGHT - 1 - y);
            
            SetPixelR(image, x, HEIGHT - 1 - y, GetPixelR(image, x, y));
            SetPixelG(image, x, HEIGHT - 1 - y, GetPixelG(image, x, y));
            SetPixelB(image, x, HEIGHT - 1 - y, GetPixelB(image, x, y));
            
            SetPixelR(image, x, y, r);
            SetPixelG(image, x, y, g);
            SetPixelB(image, x, y, b);
        }
    }
}

/* mirror image vertically */
IMAGE *VMirror(IMAGE *image) {
    int x, y;
    int WIDTH = ImageWidth(image);
    int HEIGHT = ImageHeight(image);
    for (y = 0; y < HEIGHT / 2; y ++) {
        for (x = 0; x < WIDTH; x ++) {
            SetPixelR(image, x, HEIGHT - 1 - y, GetPixelR(image, x, y));
            SetPixelG(image, x, HEIGHT - 1 - y, GetPixelG(image, x, y));
            SetPixelB(image, x, HEIGHT - 1 - y, GetPixelB(image, x, y));
        }
    }
}


/* Shuffle the image */
IMAGE *Shuffle(IMAGE *image) {
    int block_cnt = SHUFF_HEIGHT_DIV * SHUFF_WIDTH_DIV;
    int block_width = WIDTH/SHUFF_WIDTH_DIV;
    int block_height = HEIGHT/SHUFF_HEIGHT_DIV;
    int block[SHUFF_WIDTH_DIV][SHUFF_HEIGHT_DIV];
    int i, j;
    int WIDTH = ImageWidth(image);
    int HEIGHT = ImageHeight(image);

    srand(time(NULL));
    /* Initialize block markers to not done (-1) */
    for (i = 0; i < SHUFF_WIDTH_DIV; i++) {
        for (j = 0; j< SHUFF_HEIGHT_DIV; j++) {
            block[i][j] = -1;
        }
    }

    while (block_cnt > 0) {
        /* Generate a random pair of blocks */
        int dest_height = rand() % SHUFF_HEIGHT_DIV;
        int dest_width = rand() % SHUFF_WIDTH_DIV;
        int src_height = rand() % SHUFF_HEIGHT_DIV;
        int src_width = rand() % SHUFF_WIDTH_DIV;

        /* Check if these blocks are already swaped, if not swap blocks */
        if ((block[dest_width][dest_height] == -1) && (block[src_width][src_height] == -1)) {
            /* Swap blocks */
            for (i = 0; i < block_height; i++) {
                /* Init src and dest height offset */
                int h_dest = ((dest_height * block_height) + i) % HEIGHT;
                int h_src  = ((src_height * block_height) + i) % HEIGHT; 
                for (j = 0; j < block_width; j++) {
                    int temp;
                    /* Init src and dest width offset */
                    int w_src  = ((src_width * block_width) + j) % WIDTH; 
                    int w_dest = ((dest_width * block_width) + j) % WIDTH;

                    temp = R[w_dest][h_dest];
                    R[w_dest][h_dest] = R[w_src][h_src];
                    R[w_src][h_src] = temp;

                    temp = G[w_dest][h_dest];
                    G[w_dest][h_dest] = G[w_src][h_src];
                    G[w_src][h_src] = temp;

                    temp = B[w_dest][h_dest];
                    B[w_dest][h_dest] = B[w_src][h_src];
                    B[w_src][h_src] = temp;
                }
            }
            /* Set marker as done */
            block[dest_width][dest_height] = 1;
            block[src_width][src_height] = 1;
            /* Decrease block count */
            block_cnt -= 2; /* Two blocks are swapped */
        }
        
    }
}

/* add border to the image */
IMAGE *AddBorder(IMAGE *image, char color[SLEN], int border_width) {
    int x, y;
    int WIDTH = ImageWidth(image);
    int HEIGHT = ImageHeight(image);
    int border_r = 255;
    int border_g = 255;
    int border_b = 255;
    if (!strcmp(color, "black")) {
        border_r = 0;
        border_g = 0;
        border_b = 0;
    } else if (!strcmp(color, "white")) {
        border_r = 255;
        border_g = 255;
        border_b = 255;
    } else if (!strcmp(color, "red")) {
        border_r = 255;
        border_g = 0;
        border_b = 0;
    } else if (!strcmp(color, "green")) {
        border_r = 0;
        border_g = 255;
        border_b = 0;
    } else if (!strcmp(color, "blue")) {
        border_r = 0;
        border_g = 0;
        border_b = 255;
    } else if (!strcmp(color, "yellow")) {
        border_r = 255;
        border_g = 255;
        border_b = 0;
    } else if (!strcmp(color, "cyan")) {
        border_r = 0;
        border_g = 255;
        border_b = 255;
    } else if (!strcmp(color, "pink")) {
        border_r = 255;
        border_g = 192;
        border_b = 203;
    } else if (!strcmp(color, "orange")) {
        border_r = 255;
        border_g = 165;
        border_b = 0;
    } else {
        printf("Unsurported color.\n");
        return;
    }
    const int X_BORDER_WIDTH = border_width * 9 / 16;
    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            if ((y < border_width) || (y > HEIGHT - 1 - border_width) ||
                    (x < X_BORDER_WIDTH) || (x > WIDTH - 1 - X_BORDER_WIDTH)) {
                R[x][y] = border_r;
                G[x][y] = border_g;
                B[x][y] = border_b;
            }
        }
    }
}


/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
