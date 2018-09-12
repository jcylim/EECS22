/*********************************************************************/
/* PhotoLab.c: assignment 2 for EECS 22 in Fall 2017                 */
/*                                                                   */
/* modifications: (Saeed Karimi Bidhendi)                            */
/* 09/27/17 RD	adjusted for lecture usage                           */
/*********************************************************************/

/*** header files ***/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*** global definitions ***/

const int WIDTH  = 600;	/* image width */
const int HEIGHT = 400;	/* image height */
const int SLEN   =  80;	/* max. string length */

/*** function declarations ***/

void PrintMenu();

/* read image from a file */
int LoadImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT],
              unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* save a processed image */
int SaveImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT],
              unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* reverse image color */
void Negative(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
              unsigned char B[WIDTH][HEIGHT]);

/* color filter */
void ColorFilter(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
                 unsigned char B[WIDTH][HEIGHT], int target_r, int target_g,
                 int target_b, int threshold, int replace_r, int replace_g, int replace_b);

/* edge detection */
void Edge(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
          unsigned char B[WIDTH][HEIGHT]);


/* mirror image vertically */
void VMirror(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
             unsigned char B[WIDTH][HEIGHT]);

/* change color image to black & white */
void BlackNWhite(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
                 unsigned char B[WIDTH][HEIGHT]);


/* sharpen the image */
void Shuffle(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
             unsigned char B[WIDTH][HEIGHT]);


/* add border */
void AddBorder(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
               unsigned char B[WIDTH][HEIGHT], char color[SLEN], int border_width);

/* flip image vertically */
void VFlip(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
           unsigned char B[WIDTH][HEIGHT]);

/* Test all functions */
void AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
              unsigned char B[WIDTH][HEIGHT]);

/*** main program ***/

int main(void)
{
    unsigned char R[WIDTH][HEIGHT];
    unsigned char G[WIDTH][HEIGHT];
    unsigned char B[WIDTH][HEIGHT];
    int choice;
    int r, g, b, thres, replace_r, replace_g, replace_b;
    int border_width;
    char color[SLEN];
    char imageName[SLEN];

    /*if (LoadImage("HSSOE.ppm", R, G, B) != 0)
        { return 10; }*/
    while(1) {
    	printf("--------------------------------\n");
	    printf("1: Load a PPM image\n");
	    printf("2: Save an image in PPM and JPEG format\n");
	    printf("3: Change a color image to Black & White\n");
	    printf("4: Make a negative of an image\n");
	    printf("5: Color filter an image\n");
	    printf("6: Sketch the edge of an image\n");
	    printf("7: Shuffle an image\n");
	    printf("8: Flip an iamge vertically\n");
	    printf("9: Mirror an image vertically\n");
	    printf("10: Add border to an image\n");
	    printf("11: Test all functions\n");
	    printf("12: Exit\n");
	    printf("Please make your choice (number only): ");
	    scanf("%d", &choice);

	    switch (choice) {
	    	case 1:
	    		printf("Please input the file name to load: ");
	    		scanf("%s", imageName);
	    		LoadImage(imageName, R, G, B);
	    		break;
	    	case 2:
	    		printf("Please input the file name to save: ");
	    		scanf("%s", imageName);
	    		SaveImage(imageName, R, G, B);
	    		break;
	    	case 3:
	    		if(strlen(imageName) == 0) {
	    			printf("Load the image first!!\n");
	    			break;
	    		}
	    		LoadImage(imageName, R, G, B);
				  BlackNWhite(R, G, B);
				  SaveImage("bw", R, G, B);
	    		break;
	    	case 4:
	    		if(strlen(imageName) == 0) {
	    			printf("Load the image first!!\n");
	    			break;
	    		}
	    		LoadImage(imageName, R, G, B);
				  Negative(R, G, B);
				  SaveImage("negative", R, G, B);
	    		break;
	    	case 5:
	    		if(strlen(imageName) == 0) {
	    			printf("Load the image first!!\n");
	    			break;
	    		}
	    		printf("Enter Red component for the target color: ");
	    		scanf("%d", &r);
	    		printf("Enter Green component for the target color: ");
	    		scanf("%d", &g);
	    		printf("Enter Blue component for the target color: ");
	    		scanf("%d", &b);
	    		printf("Enter threshold for the color difference: ");
	    		scanf("%d", &thres);
	    		printf("Enter value for Red component in the target color: ");
	    		scanf("%d", &replace_r);
	    		printf("Enter value for Green component in the target color: ");
	    		scanf("%d", &replace_g);
	    		printf("Enter value for Blue component in the target color: ");
	    		scanf("%d", &replace_b);
	    		LoadImage(imageName, R, G, B);
				  ColorFilter(R, G, B, r, g, b, thres, replace_r, replace_g, replace_b);
				  SaveImage("colorfilter", R, G, B);
	    		break;
	    	case 6:
	    		if(strlen(imageName) == 0) {
	    			printf("Load the image first!!\n");
	    			break;
	    		}
	    		LoadImage(imageName, R, G, B);
				  Edge(R, G, B);
				  SaveImage("edge", R, G, B);
	    		break;
	    	case 7:
	    		if(strlen(imageName) == 0) {
	    			printf("Load the image first!!\n");
	    			break;
	    		}
	    		/*LoadImage(imageName, R, G, B);
				  Shuffle(R, G, B);
				  SaveImage("vflip", R, G, B);*/
	    		break;
	    	case 8:
	    		if(strlen(imageName) == 0) {
	    			printf("Load the image first!!\n");
	    			break;
	    		}
	    		LoadImage(imageName, R, G, B);
				  VFlip(R, G, B);
				  SaveImage("vflip", R, G, B);
	    		break;
			case 9:
				if(strlen(imageName) == 0) {
	    			printf("Load the image first!!\n");
	    			break;
	    		}
	    		LoadImage(imageName, R, G, B);
				  VMirror(R, G, B);
				  SaveImage("vmirror", R, G, B);
	    		break;
	    	case 10:
	    		if(strlen(imageName) == 0) {
	    			printf("Load the image first!!\n");
	    			break;
	    		}
	    		printf("Enter border width: ");
	    		scanf("%d", &border_width);
	    		printf("Available border colors: black, white, red, green, blue, yellow, cyan, pink, orange\n");
	    		printf("Select border color from the options: ");
	    		scanf("%s", color);
	    		LoadImage(imageName, R, G, B);
				  AddBorder(R, G, B, color, border_width);
				  SaveImage("border", R, G, B);
	    		break;
	    	case 11:
	    		if(strlen(imageName) == 0) {
	    			printf("Load the image first!!\n");
	    			break;
	    		}
          AutoTest(R, G, B);
	    		break;
	    	default:
	    		break;		
	    }
	    if (choice == 12) {
	    	break;
	    }
    }
    return 0;
} /* end of main */


/*** function definitions ***/

/* read a photo from the specified file into the specified */
/* RGB data structure; returns 0 for success, >0 for error */


int LoadImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) {
        FILE           *File;
        char            Type[SLEN];
        int             Width, Height, MaxValue;
        int             x, y;
        char            ftype[] = ".ppm";
        char            fname_tmp[SLEN];      
        strcpy(fname_tmp, fname);
        strcat(fname_tmp, ftype);

        File = fopen(fname_tmp, "r");
        if (!File) {
                printf("Cannot open file \"%s\" for reading!\n", fname);
                return 1;
                    }
        fscanf(File, "%79s", Type);
        if (Type[0] != 'P' || Type[1] != '6' || Type[2] != 0) {
                printf("\nUnsupported file format!\n");
                return 2;
                                                                }
        fscanf(File, "%d", &Width);
        if (Width != WIDTH) {
                printf("\nUnsupported image width %d!\n", Width);
                return 3;
                             }
        fscanf(File, "%d", &Height);
        if (Height != HEIGHT) {
                 printf("\nUnsupported image height %d!\n", Height);
                 return 4;
                              }
        fscanf(File, "%d", &MaxValue);
        if (MaxValue != 255) {
                 printf("\nUnsupported image maximum value %d!\n", MaxValue);
                 return 5;
                            }
        if ('\n' != fgetc(File)) {
                 printf("\nCarriage return expected!\n");
                 return 6;
                                }
        for (y = 0; y < HEIGHT; y++)
             for (x = 0; x < WIDTH; x++) {
                         R[x][y] = fgetc(File);
                         G[x][y] = fgetc(File);
                         B[x][y] = fgetc(File);
                                         }
        if (ferror(File)) {
             printf("\nFile error while reading from file!\n");
             return 7;
                           }
        printf("%s was read.\n", fname_tmp);
        fclose(File);
        return 0;
}

int SaveImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) {
        FILE    *File;
        int x, y;
        char    SysCmd[SLEN * 5];
        char    ftype[] = ".ppm";
        char    fname_tmp[SLEN];  /*avoid to modify on the original pointer, 11/10/10, X.Han*/
        char    fname_tmp2[SLEN];

        strcpy(fname_tmp, fname);
        strcpy(fname_tmp2, fname);
        strcat(fname_tmp2, ftype);

        File = fopen(fname_tmp2, "w");
        if (!File) {
                printf("Cannot open file \"%s\" for writing!\n", fname);
                return 1;
                   }
        fprintf(File, "P6\n");
        fprintf(File, "%d %d\n", WIDTH, HEIGHT);
        fprintf(File, "255\n");
        for (y = 0; y < HEIGHT; y++)
                 for (x = 0; x < WIDTH; x++) {
                               fputc(R[x][y], File);
                               fputc(G[x][y], File);
                               fputc(B[x][y], File);
                                              }
         if (ferror(File)) {
                  printf("\nFile error while writing to file!\n");
                  return 2;
                            }
         fclose(File);
         printf("%s was saved. \n", fname_tmp2);
   /*
     *      * rename file to image.ppm, convert it to ~/public_html/<fname>.jpg
     *           * and make it world readable
                                   *                */
        sprintf(SysCmd, "/users/grad2/doemer/eecs22/bin/pnmtojpeg_hw2.tcsh %s", fname_tmp2);
        if (system(SysCmd) != 0) {
        printf("\nError while converting to JPG:\nCommand \"%s\" failed!\n", SysCmd);
        return 3;
                                  }
        printf("%s.jpg was stored.\n", fname_tmp);
        return 0;
}

void BlackNWhite(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) {
    for (int x = 0; x < WIDTH; x++) {
    	for (int y = 0; y < HEIGHT; y++) {
    		R[x][y] = B[x][y] = G[x][y] = (R[x][y] + B[x][y] + G[x][y])/3; 
    	}
    }
    printf("'Black & White' operation is done!\n");
}

void Negative(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) {
        for (int x = 0; x < WIDTH; x++) {
        	for (int y = 0; y < HEIGHT; y++) {
        		R[x][y] = (255 - R[x][y]);
				B[x][y] = (255 - B[x][y]);
				G[x][y] = (255 - G[x][y]); 
        	}
        }
        printf("'Negative' operation is done!\n");
}

void ColorFilter(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], int target_r, int target_g,
                 int target_b, int threshold, int replace_r, int replace_g, int replace_b) {
        bool red, green, blue = false;
        for (int x = 0; x < WIDTH; x++) {
        	for (int y = 0; y < HEIGHT; y++) {
        		red = (R[x][y] > target_r - threshold) && (R[x][y] < target_r + threshold);
        		green = (G[x][y] > target_g - threshold) && (G[x][y] < target_g + threshold);
        		blue = (B[x][y] > target_b - threshold) && (B[x][y] < target_b + threshold); 
        		if (red && green && blue) {
        			R[x][y] = replace_r;
        			G[x][y] = replace_g;
        			B[x][y] = replace_b;
        		} else {
        			break;
        		}
        	}
        }
        printf("'Color Filter' operation is done!\n");
}

void Edge(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) {
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
        		int red = 8*R_copy[x][y]-R_copy[x-1][y-1]-R_copy[x][y-1]-R_copy[x+1][y-1]-R_copy[x-1][y]-R_copy[x+1][y]-R_copy[x-1][y+1]-R_copy[x][y+1]-R_copy[x+1][y+1];
        		int green = 8*G_copy[x][y]-G_copy[x-1][y-1]-G_copy[x][y-1]-G_copy[x+1][y-1]-G_copy[x-1][y]-G_copy[x+1][y]-G_copy[x-1][y+1]-G_copy[x][y+1]-G_copy[x+1][y+1];
        		int blue = 8*B_copy[x][y]-B_copy[x-1][y-1]-B_copy[x][y-1]-B_copy[x+1][y-1]-B_copy[x-1][y]-B_copy[x+1][y]-B_copy[x-1][y+1]-B_copy[x][y+1]-B_copy[x+1][y+1];
        		if (red < 0) {
        			red = 0;
        		} else if (red > 255) {
        			red = 255;
        		}
        		if (green < 0) {
        			green = 0;
        		} else if (red > 255) {
        			green = 255;
        		}
        		if (blue < 0) {
        			blue = 0;
        		} else if (red > 255) {
        			blue = 255;
        		}
        		R[x][y] = red;
				G[x][y] = green; 
				B[x][y] = blue;
        	}
        }
        printf("'Edge' operation is done!\n");
}

/*void Shuffle(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) {
        int blocks[R][16];

        for (int x = 0; x < WIDTH/4; x++) {
        	for (int y = 0; y < HEIGHT/4; y++) {
        		 
        	}
        }
        printf("'Shuffle' operation is done!\n");
}*/

void VFlip(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) {
        unsigned char R_copy[WIDTH][HEIGHT/2];
        unsigned char G_copy[WIDTH][HEIGHT/2];
        unsigned char B_copy[WIDTH][HEIGHT/2];
        for (int x = 0; x < WIDTH; x++) {
        	for (int y = 0; y < HEIGHT/2; y++) {
        		R_copy[x][y] = R[x][y];
    				B_copy[x][y] = B[x][y];
    				G_copy[x][y] = G[x][y];
    				R[x][y] = R[x][HEIGHT-y];
    				B[x][y] = B[x][HEIGHT-y];
    				G[x][y] = G[x][HEIGHT-y];
    				R[x][HEIGHT-y] = R_copy[x][y];
    				B[x][HEIGHT-y] = B_copy[x][y];
    				G[x][HEIGHT-y] = G_copy[x][y];  
        	}
        }
        printf("'VFlip' operation is done!\n");
}

void VMirror(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) {
        for (int x = 0; x < WIDTH; x++) {
        	for (int y = 0; y < HEIGHT; y++) {
        		R[x][HEIGHT-y] = R[x][y];
				B[x][HEIGHT-y] = B[x][y];
				G[x][HEIGHT-y] = G[x][y]; 
        	}
        }
        printf("'VMirror' operation is done!\n");
}


void AddBorder(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], char color[SLEN], int border_width) {
    if (strcmp(color, "black") == 0) {    
    	for (int x = 0; x < (9*border_width)/16; x++) {
      	for (int y = 0; y < HEIGHT; y++) {
      		R[x][y] = 0;
      		G[x][y] = 0; 
      		B[x][y] = 0;
      	}
    	}
    	for (int x = 0; x < WIDTH; x++) {
      	for (int y = 0; y < border_width; y++) {
      		R[x][y] = 0;
      		G[x][y] = 0; 
      		B[x][y] = 0;
      	}
    	}
    	for (int x = 0; x < WIDTH; x++) {
      	for (int y = 0; y < border_width; y++) {
      		R[x][HEIGHT-y] = 0;
      		G[x][HEIGHT-y] = 0;
      		B[x][HEIGHT-y] = 0;
      	}
    	}
    	for (int x = 0; x < (9*border_width)/16; x++) {
      	for (int y = 0; y < HEIGHT; y++) {
      		R[WIDTH-x][y] = 0;
      		G[WIDTH-x][y] = 0;
      		B[WIDTH-x][y] = 0;
      	}
    	}
    	printf("'Border' operation is done!\n");
		} else if (strcmp(color, "white") == 0) {
  			for (int x = 0; x < (9*border_width)/16; x++) {
        	for (int y = 0; y < HEIGHT; y++) {
        		R[x][y] = 255;
        		G[x][y] = 255; 
        		B[x][y] = 255;
        	}
      	}
      	for (int x = 0; x < WIDTH; x++) {
        	for (int y = 0; y < border_width; y++) {
        		R[x][y] = 255;
        		G[x][y] = 255; 
        		B[x][y] = 255;
        	}
      	}
      	for (int x = 0; x < WIDTH; x++) {
        	for (int y = 0; y < border_width; y++) {
        		R[x][HEIGHT-y] = 255;
        		G[x][HEIGHT-y] = 255;
        		B[x][HEIGHT-y] = 255;
        	}
      	}
      	for (int x = 0; x < 9*(border_width)/16; x++) {
        	for (int y = 0; y < HEIGHT; y++) {
        		R[WIDTH-x][y] = 255;
        		G[WIDTH-x][y] = 255;
        		B[WIDTH-x][y] = 255;
        	}
      	}
      	printf("'Border' operation is done!\n");
		} else if (strcmp(color, "red") == 0) {
			  for (int x = 0; x < 9*(border_width)/16; x++) {
        	for (int y = 0; y < HEIGHT; y++) {
        		R[x][y] = 255;
        		G[x][y] = 0; 
        		B[x][y] = 0;
        	}
      	}
      	for (int x = 0; x < WIDTH; x++) {
        	for (int y = 0; y < border_width; y++) {
        		R[x][y] = 255;
        		G[x][y] = 0; 
        		B[x][y] = 0;
        	}
      	}
      	for (int x = 0; x < WIDTH; x++) {
        	for (int y = 0; y < border_width; y++) {
        		R[x][HEIGHT-y] = 255;
        		G[x][HEIGHT-y] = 0;
        		B[x][HEIGHT-y] = 0;
        	}
      	}
      	for (int x = 0; x < 9*(border_width)/16; x++) {
        	for (int y = 0; y < HEIGHT; y++) {
        		R[WIDTH-x][y] = 255;
        		G[WIDTH-x][y] = 0;
        		B[WIDTH-x][y] = 0;
        	}
      	}
      	printf("'Border' operation is done!\n");
		} else if (strcmp(color, "green") == 0) {
			  for (int x = 0; x < 9*(border_width)/16; x++) {
	        for (int y = 0; y < HEIGHT; y++) {
	        	R[x][y] = 0;
	        	G[x][y] = 255; 
	        	B[x][y] = 0;
	        }
        }
      	for (int x = 0; x < WIDTH; x++) {
        	for (int y = 0; y < border_width; y++) {
        		R[x][y] = 0;
        		G[x][y] = 255; 
        		B[x][y] = 0;
        	}
      	}
      	for (int x = 0; x < WIDTH; x++) {
        	for (int y = 0; y < border_width; y++) {
        		R[x][HEIGHT-y] = 0;
        		G[x][HEIGHT-y] = 255;
        		B[x][HEIGHT-y] = 0;
        	}
      	}
      	for (int x = 0; x < 9*(border_width)/16; x++) {
        	for (int y = 0; y < HEIGHT; y++) {
        		R[WIDTH-x][y] = 0;
        		G[WIDTH-x][y] = 255;
        		B[WIDTH-x][y] = 0;
        	}
      	}
      	printf("'Border' operation is done!\n");
		} else if (strcmp(color, "blue") == 0) {
  			for (int x = 0; x < 9*(border_width)/16; x++) {
        	for (int y = 0; y < HEIGHT; y++) {
        		R[x][y] = 0;
        		G[x][y] = 0; 
        		B[x][y] = 255;
        	}
      	}
      	for (int x = 0; x < WIDTH; x++) {
        	for (int y = 0; y < border_width; y++) {
        		R[x][y] = 0;
        		G[x][y] = 0; 
        		B[x][y] = 255;
        	}
      	}
      	for (int x = 0; x < WIDTH; x++) {
        	for (int y = 0; y < border_width; y++) {
        		R[x][HEIGHT-y] = 0;
        		G[x][HEIGHT-y] = 0;
        		B[x][HEIGHT-y] = 255;
        	}
      	}
      	for (int x = 0; x < 9*(border_width)/16; x++) {
        	for (int y = 0; y < HEIGHT; y++) {
        		R[WIDTH-x][y] = 0;
        		G[WIDTH-x][y] = 0;
        		B[WIDTH-x][y] = 255;
        	}
      	}
      	printf("'Border' operation is done!\n");
		} else if (strcmp(color, "yellow") == 0) {
			  for (int x = 0; x < 9*(border_width)/16; x++) {
        	for (int y = 0; y < HEIGHT; y++) {
        		R[x][y] = 255;
        		G[x][y] = 255; 
        		B[x][y] = 0;
        	}
      	}
      	for (int x = 0; x < WIDTH; x++) {
        	for (int y = 0; y < border_width; y++) {
        		R[x][y] = 255;
        		G[x][y] = 255; 
        		B[x][y] = 0;
        	}
      	}
      	for (int x = 0; x < WIDTH; x++) {
        	for (int y = 0; y < border_width; y++) {
        		R[x][HEIGHT-y] = 255;
        		G[x][HEIGHT-y] = 255;
        		B[x][HEIGHT-y] = 0;
        	}
      	}
      	for (int x = 0; x < 9*(border_width)/16; x++) {
        	for (int y = 0; y < HEIGHT; y++) {
        		R[WIDTH-x][y] = 255;
        		G[WIDTH-x][y] = 255;
        		B[WIDTH-x][y] = 0;
        	}
      	}
      	printf("'Border' operation is done!\n");
		} else if (strcmp(color, "cyan") == 0) {
			  for (int x = 0; x < 9*(border_width)/16; x++) {
        	for (int y = 0; y < HEIGHT; y++) {
        		R[x][y] = 0;
        		G[x][y] = 255; 
        		B[x][y] = 255;
        	}
      	}
      	for (int x = 0; x < WIDTH; x++) {
        	for (int y = 0; y < border_width; y++) {
        		R[x][y] = 0;
        		G[x][y] = 255; 
        		B[x][y] = 255;
        	}
      	}
      	for (int x = 0; x < WIDTH; x++) {
        	for (int y = 0; y < border_width; y++) {
        		R[x][HEIGHT-y] = 0;
        		G[x][HEIGHT-y] = 255;
        		B[x][HEIGHT-y] = 255;
        	}
      	}
      	for (int x = 0; x < 9*(border_width)/16; x++) {
        	for (int y = 0; y < HEIGHT; y++) {
        		R[WIDTH-x][y] = 0;
        		G[WIDTH-x][y] = 255;
        		B[WIDTH-x][y] = 255;
        	}
      	}
      	printf("'Border' operation is done!\n");
		} else if (strcmp(color, "pink") == 0) {
			  for (int x = 0; x < 9*(border_width)/16; x++) {
        	for (int y = 0; y < HEIGHT; y++) {
        		R[x][y] = 255;
        		G[x][y] = 192; 
        		B[x][y] = 203;
        	}
      	}
      	for (int x = 0; x < WIDTH; x++) {
        	for (int y = 0; y < border_width; y++) {
        		R[x][y] = 255;
        		G[x][y] = 192; 
        		B[x][y] = 203;
        	}
      	}
      	for (int x = 0; x < WIDTH; x++) {
        	for (int y = 0; y < border_width; y++) {
        		R[x][HEIGHT-y] = 255;
        		G[x][HEIGHT-y] = 192;
        		B[x][HEIGHT-y] = 203;
        	}
      	}
      	for (int x = 0; x < 9*(border_width)/16; x++) {
        	for (int y = 0; y < HEIGHT; y++) {
        		R[WIDTH-x][y] = 255;
        		G[WIDTH-x][y] = 192;
        		B[WIDTH-x][y] = 203;
        	}
      	}
      	printf("'Border' operation is done!\n");
		} else if (strcmp(color, "orange") == 0) {
			  for (int x = 0; x < 9*(border_width)/16; x++) {
        	for (int y = 0; y < HEIGHT; y++) {
        		R[x][y] = 255;
        		G[x][y] = 165; 
        		B[x][y] = 0;
        	}
        }
      	for (int x = 0; x < WIDTH; x++) {
        	for (int y = 0; y < border_width; y++) {
        		R[x][y] = 255;
        		G[x][y] = 165; 
        		B[x][y] = 0;
        	}
      	}
      	for (int x = 0; x < WIDTH; x++) {
        	for (int y = 0; y < border_width; y++) {
        		R[x][HEIGHT-y] = 255;
        		G[x][HEIGHT-y] = 165;
        		B[x][HEIGHT-y] = 0;
        	}
      	}
      	for (int x = 0; x < 9*(border_width)/16; x++) {
        	for (int y = 0; y < HEIGHT; y++) {
        		R[WIDTH-x][y] = 255;
        		G[WIDTH-x][y] = 165;
        		B[WIDTH-x][y] = 0;
        	}
        }
        printf("'Border' operation is done!\n");
    } else {
  		printf("Invalid entry: Please try again.\n");
    }
}

void AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) {
  //char fname[SLEN] = "HSSOE";
  char sname[SLEN];
  //Black N White 
  LoadImage("HSSOE", R, G, B);
	BlackNWhite(R, G, B);
	strcpy(sname, "bw");/*string copy function to prepare the file name to be saved*/
	SaveImage(sname, R, G, B);
	printf("Black and White tested!\n\n");
  //Negative
	LoadImage("HSSOE", R, G, B);
	Negative(R, G, B);
	strcpy(sname, "negative");/*string copy function to prepare the file name to be saved*/
	SaveImage(sname, R, G, B);
	printf("Negative tested!\n\n");
  //Color Filter
	LoadImage("HSSOE", R, G, B);
	ColorFilter(R, G, B, 190, 100, 150, 60, 0, 0, 255);
	strcpy(sname, "colorfilter");
	SaveImage(sname, R, G, B);
	printf("Color Filter tested!\n\n");
  //Edge
  LoadImage("HSSOE", R, G, B);
  Edge(R, G, B);
  strcpy(sname, "edge");
  SaveImage(sname, R, G, B);
  printf("Edge tested!\n\n");
  //VFlip
  LoadImage("HSSOE", R, G, B);
  VFlip(R, G, B);
  strcpy(sname, "vflip");
  SaveImage(sname, R, G, B);
  printf("VFlip tested!\n\n");
  //VMirror
  LoadImage("HSSOE", R, G, B);
  VMirror(R, G, B);
  strcpy(sname, "vmirror");
  SaveImage(sname, R, G, B);
  printf("VMirror tested!\n\n");
  //Add Border
  LoadImage("HSSOE", R, G, B);
  AddBorder(R, G, B, "yellow", 64);
  strcpy(sname, "border");
  SaveImage(sname, R, G, B);
  printf("Add Border tested!\n\n");
}


/*

 
        .
        .
        .
        .
        .
 
 
 
*/




/* EOF */
