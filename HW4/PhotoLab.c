/*********************************************************************/
/* PhotoLab.c: homework assignment #3, for EECS 22,  Fall 2017       */
/*                                                                   */
/* Author: Mina Moghadam                                                */
/* Date:   11/8/2017                                                */
/*                                                                   */
/* Comments: */
/*                                                                   */
/* Please use this template to submit your hw3.                      */
/*********************************************************************/

#include <stdio.h>
#include <string.h>

#include "DIPs.h"
#include "Advanced.h"
#include "FileIO.h"
#include "Constants.h"
#include "Test.h"

/*** function declarations ***/

/* print a menu */
void PrintMenu();

int main() {
	int rc;


#ifdef DEBUG
	AutoTest();
	rc = 0;

#else
	IMAGE *image = NULL;
	const char watermarkImage[SLEN] = "watermark_template";

	int option;         /* user input option */
	char fname[SLEN];       /* input file name */
	char colorOption[SLEN];

	rc = 1;
	PrintMenu();
	printf("Please make your choice: ");
	scanf("%d", &option);


	/* ColorFilter() parameters */
	int target_r, target_g, target_b, threshold;
	double factor_r, factor_g, factor_b;

	/* AddBorder() parameter */
	int border_width;
	unsigned char rbits, gbits, bbits;

	/* Noise() parameter */
	int n;

	/* MotionBlur() parameter */
	unsigned char blur_amount;

	/* Crop() parameter */
	int x, y, W, H;

	/*Resize() parameter */
	int percentage;

	/*BrightnessAndContrast() parameter */
	int brightness, contrast;

	while (option != EXIT) {
		if (option == 1) {
			printf("Please input the file name to load: ");
			scanf("%s", fname);
			image = LoadImage(fname);
		}

		/* menu item 2 - 14 requires image is loaded first */
		else if (option >= 2 && option <= 18) {
			if (rc != SUCCESS) {
				printf("No image is read.\n");
			}
			/* now image is loaded */
			else {
				switch (option) {
				case 2:
					printf("Please input the file name to save: ");
					scanf("%s", fname);
					SaveImage(fname, image);
					break;
				case 3:
					if (!image) {
						printf("No image is read.\n");
					}
					else {
						image = BlackNWhite(image);
						printf("\"Black & White\" operation is done!\n");
					}
					break;
				case 4:
					if (!image) {
						printf("No image is read.\n");
					}
					else {
						image = Negative(image);
						printf("\"Negative\" operation is done!\n");
					}
					break;
				case 5:
					if (!image) {
						printf("No image is read.\n");
					}
					else {
						printf("Enter Red component for the target color: ");
						scanf("%d", &target_r);
						printf("Enter Green component for the target color: ");
						scanf("%d", &target_g);
						printf("Enter Blue  component for the target color: ");
						scanf("%d", &target_b);
						printf("Enter threshold for the color difference: ");
						scanf("%d", &threshold);
						printf("Enter value for Red component in the target color: ");
						scanf("%lf", &factor_r);
						printf("Enter value for Green component in the target color: ");
						scanf("%lf", &factor_g);
						printf("Enter value for Blue  component in the target color: ");
						scanf("%lf", &factor_b);
						image = ColorFilter(image, target_r, target_g, target_b, threshold, factor_r, factor_g, factor_b);
						printf("\"Color Filter\" operation is done!\n");
					}
					break;
				case 6:
					if (!image) {
						printf("No image is read.\n");
					}
					else {
						image = Edge(image);
						printf("\"Edge\" operation is done!\n");
					}
					break;
				case 7:
					if (!image) {
						printf("No image is read.\n");
					}
					else {
						image = Shuffle(image);
						printf("\"Shuffle\" operation is done!\n");
					}
					break;
				case 8:
					if (!image) {
						printf("No image is read.\n");
					}
					else {
						image = VFlip(image);
						printf("\"VFlip\" operation is done!\n");
					}
					break;
				case 9:
					if (!image) {
						printf("No image is read.\n");
					}
					else {
						VMirror(image);
						printf("\"Vertically Mirror\" operation is done!\n");
					}
					break;
				case 10:
					if (!image) {
						printf("No image is read.\n");
					}
					else {
						printf("Enter border width:");
						scanf("%d", &border_width);
						printf("Available border colors : black, white, red, green, blue, yellow, cyan, pink, orange\n");
						printf("Select border color from the options: ");
						scanf("%s", colorOption);
						image = AddBorder(image, colorOption, border_width);
						printf("\"Border\" operation is done!\n");
					}
					break;
				case 11:
					if (!image) {
						printf("No image is read.\n");
					}
					else {
						printf("Please input noise percentage: ");
						scanf("%d", &n);
						image = AddNoise(image, n);
						printf("\"AddNoise\" operation is done!\n");
					}
					break;
				case 12:
					if (!image) {
						printf("No image is read.\n");
					}
					else {
						image = Sharpen(image);
						printf("\"Sharpen\" operation is done!\n");
					}
					break;
				case 13:
					if (!image) {
						printf("No image is read.\n");
					}
					else {
						printf("Enter the number of posterization bits for R chennel (1 to 8):");
						scanf("%hhu", &rbits);
						printf("Enter the number of posterization bits for G chennel (1 to 8):");
						scanf("%hhu", &gbits);
						printf("Enter the number of posterization bits for B chennel (1 to 8):");
						scanf("%hhu", &bbits);
						image = Posterize(image, rbits, gbits, bbits);
						printf("\"Posterize\" operation is done!\n");
					}
					break;
				case 14:
					if (!image) {
						printf("No image is read.\n");
					}
					else {
						printf("Please input motion blur amount: ");
						scanf("%hhu", &blur_amount);
						image = MotionBlur(image, blur_amount);
						printf("\"Motion Blur\" operation is done!\n");
					}
					break;
				case 15:
					if (!image) {
						printf("No image is read.\n");
					}
					else {
						printf("Please enter the X offset value: ");
						scanf("%d", &x);
						printf("Please enter the Y offset value: ");
						scanf("%d", &y);
						printf("Please input the crop width: ");
						scanf("%d", &W);
						printf("Please input the crop height: ");
						scanf("%d", &H);
						image = Crop(image, x, y, W, H);
						printf("\"Crop\" operation is done!\n");
					}

					break;
				case 16:
					if (!image) {
						printf("No image is read.\n");
					}
					else {
						printf("Please input the resizing percentage (integer between 1 - 500): ");
						scanf("%d", &percentage);
						image = Resize(image, percentage);
						printf("\"Resize\" operation is done!\n");
					}
					break;
				case 17:
					if (!image) {
						printf("No image is read.\n");
					}
					else {
						printf("Please input the brightness level (integer between -255 - 255): ");
						scanf("%d", &brightness);
						printf("Please input the contrast level (integer between -255 - 255): ");
						scanf("%d", &contrast);
						image = BrightnessAndContrast(image, brightness, contrast);
						printf("\"Brightness And Contrast Adjustment\" operation is done!\n");
					}
					break;
				case 18:
					if (!image) {
						printf("No image is read.\n");
					}
					/*IMAGE *watermark_image = LoadImage(watermarkImage);
					image = Watermark(image, watermark_image);
					printf("\"Watermark\" operation is done!\n");*/
					break;
				case 19:
					AutoTest();
					rc = SUCCESS;   /* set returned code SUCCESS, since image is loaded */
					break;
				default:
					break;

				}
			}
		}

		else if (option == 19) {
			AutoTest();
			rc = SUCCESS;   /* set returned code SUCCESS, since image is loaded */
		}
		else {
			printf("Invalid selection!\n");
		}

		/* Process finished, waiting for another input */
		PrintMenu();
		printf("Please make your choice: ");
		scanf("%d", &option);
	}
	printf("You exit the program.\n");
#endif

	return 0;
}


/*******************************************/
/* Function implementations should go here */
/*******************************************/

/* Menu */
void PrintMenu() {
	printf("\n----------------------------\n");
	printf(" 1: Load a PPM image\n");
	printf(" 2: Save an image in PPM and JPEG format\n");
	printf(" 3: Change a color image to Black & White\n");
	printf(" 4: Make a negative of an image\n");
	printf(" 5: Color filter an image\n");
	printf(" 6: Sketch the edge of an image\n");
	printf(" 7: Shuffle an image\n");
	printf(" 8: Flip an image vertically\n");
	printf(" 9: Mirror an image vertically\n");
	printf("10: Add border to an image\n");
	printf("11: Add Noise to an image\n");
	printf("12: Sharpen an image\n");
	printf("13: Posterize an image\n");
	printf("14: Blur an image\n");
	printf("15: Crop an image\n");
	printf("16: Resize an image\n");
	printf("17: Adjust the Brightness and Contrast of an image\n");
	printf("18: Add Watermark to an image\n");
	printf("19: Test all functions\n");
	printf("16: Exit\n");
}

/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
