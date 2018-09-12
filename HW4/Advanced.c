#include "Advanced.h"
#include "Constants.h"
#include "Image.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

/* Add noise to an image */
IMAGE *AddNoise(IMAGE *image, int n)
{
	int x, y, i;
	int WIDTH = ImageWidth(image);
	int HEIGHT = ImageHeight(image);
	int num; /* number of noise added */
	num = (n*HEIGHT*WIDTH) / 100;
	srand(time(NULL));

	for (i = 0; i < num; i++) {
		x = ((double)rand() / RAND_MAX)*(WIDTH - 1);
		y = ((double)rand() / RAND_MAX)*(HEIGHT - 1);
		SetPixelR(image, x, y, 255);
		SetPixelG(image, x, y, 255);
		SetPixelB(image, x, y, 255);
	}
}


/* sharpen the image */
IMAGE *Sharpen(IMAGE *image)
{
	int		x, y, m, n, a, b;
	int		tmpR = 0;
	int		tmpG = 0;
	int		tmpB = 0;
	int		tmp2R = 0;
	int		tmp2G = 0;
	int		tmp2B = 0;
	int WIDTH = ImageWidth(image);
	int HEIGHT = ImageHeight(image);

	IMAGE *tmpImage = CreateImage(WIDTH, HEIGHT);

	for (y = 0; y < HEIGHT; y++) {
		for (x = 0; x < WIDTH; x++) {
			SetPixelR(tmpImage, x, y, GetPixelR(image, x, y));
			SetPixelG(tmpImage, x, y, GetPixelG(image, x, y));
			SetPixelB(tmpImage, x, y, GetPixelB(image, x, y));
		}
	}

	for (y = 0; y < HEIGHT; y++) {
		for (x = 0; x < WIDTH; x++) {
			for (n = -1; n <= 1; n++) {
				for (m = -1; m <= 1; m++) {
					a = x + m;
					b = y + n;
					if (a > WIDTH - 1)
						a = WIDTH - 1;
					if (a < 0)
						a = 0;
					if (b > HEIGHT - 1)
						b = HEIGHT - 1;
					if (b < 0)
						b = 0;

					if ((n == 0) && (m == 0))
					{
						tmpR += 9 * GetPixelR(tmpImage, x, y);
						tmpG += 9 * GetPixelG(tmpImage, x, y);
						tmpB += 9 * GetPixelB(tmpImage, x, y);
					}
					else
					{
						tmpR -= GetPixelR(tmpImage, a, b);
						tmpG -= GetPixelG(tmpImage, a, b);
						tmpB -= GetPixelB(tmpImage, a, b);
					}
				}
			}
			tmpR = (tmpR>255) ? 255 : (tmpR<0) ? 0 : tmpR;
			tmpG = (tmpG>255) ? 255 : (tmpG<0) ? 0 : tmpG;
			tmpB = (tmpB>255) ? 255 : (tmpB<0) ? 0 : tmpB;
			SetPixelR(tmpImage, x, y, tmpR);
			SetPixelG(tmpImage, x, y, tmpG);
			SetPixelB(tmpImage, x, y, tmpB);
			tmpR = tmpG = tmpB = 0;
		}
	}
}

/* make the image posterized */
IMAGE *Posterize(IMAGE *image, int rbits, int gbits, int bbits)
{
	int x, y;
	int WIDTH = ImageWidth(image);
	int HEIGHT = ImageHeight(image);
	for (x = 0; x<WIDTH; x++) {
		for (y = 0; y<HEIGHT; y++) {
			unsigned char one = 1;
			int i;
			for (i = 0; i<rbits - 1; i++) {
				SetPixelR(image, x, y, (GetPixelR(image, x, y) | one));
				one <<= 1;
			}
			one = ~one;
			SetPixelR(image, x, y, (GetPixelR(image, x, y) & one));

			one = 1;
			for (i = 0; i<gbits - 1; i++) {
				SetPixelG(image, x, y, (GetPixelG(image, x, y) | one));
				one <<= 1;
			}
			one = ~one;
			SetPixelG(image, x, y, (GetPixelG(image, x, y) & one));

			one = 1;
			for (i = 0; i<bbits - 1; i++) {
				SetPixelB(image, x, y, (GetPixelB(image, x, y) | one));
				one <<= 1;
			}
			one = ~one;
			SetPixelB(image, x, y, (GetPixelB(image, x, y) & one));
		}
	}
}

/* add motion blur to the image */
IMAGE *MotionBlur(IMAGE *image, unsigned char BlurAmount) {
	int x, y, m;
	int WIDTH = ImageWidth(image);
	int HEIGHT = ImageHeight(image);
	unsigned int temp_r, temp_g, temp_b;

	for (x = 0; x < WIDTH; x++)
		for (y = 0; y < HEIGHT; y++)
		{
			temp_r = (GetPixelR(image, x, y)) / 2;
			temp_b = (GetPixelB(image, x, y)) / 2;
			temp_g = (GetPixelG(image, x, y)) / 2;

			for (m = 1; m <= BlurAmount; m++)
			{
				if ((x + m) < WIDTH)
				{
					temp_r = temp_r + GetPixelR(image, x + m, y) * 0.5 / BlurAmount;
					temp_b = temp_b + GetPixelB(image, x + m, y) * 0.5 / BlurAmount;
					temp_g = temp_g + GetPixelG(image, x + m, y) * 0.5 / BlurAmount;
				}
			}
			SetPixelR(image, x, y, temp_r);
			SetPixelG(image, x, y, temp_b);
			SetPixelB(image, x, y, temp_g);
		}
}

/* add crop to the image */
IMAGE *Crop(IMAGE *image, int x, int y, int W, int H) {
	int x, y, m;
	int WIDTH = ImageWidth(image);
	int HEIGHT = ImageHeight(image);
	unsigned int temp_r, temp_g, temp_b;

	for (x = 0; x < WIDTH; x++)
		for (y = 0; y < HEIGHT; y++)
		{
			temp_r = (GetPixelR(image, x, y)) / 2;
			temp_b = (GetPixelB(image, x, y)) / 2;
			temp_g = (GetPixelG(image, x, y)) / 2;

			for (m = 1; m <= BlurAmount; m++)
			{
				if ((x + m) < WIDTH)
				{
					temp_r = temp_r + GetPixelR(image, x + m, y) * 0.5 / BlurAmount;
					temp_b = temp_b + GetPixelB(image, x + m, y) * 0.5 / BlurAmount;
					temp_g = temp_g + GetPixelG(image, x + m, y) * 0.5 / BlurAmount;
				}
			}
			SetPixelR(image, x, y, temp_r);
			SetPixelG(image, x, y, temp_b);
			SetPixelB(image, x, y, temp_g);
		}
}

/* add resize to the image */
IMAGE *Resize(IMAGE *image, int percentage) {
	int x, y, m;
	int WIDTH = ImageWidth(image);
	int HEIGHT = ImageHeight(image);
	unsigned int temp_r, temp_g, temp_b;

	for (x = 0; x < WIDTH; x++)
		for (y = 0; y < HEIGHT; y++)
		{
			temp_r = (GetPixelR(image, x, y)) / 2;
			temp_b = (GetPixelB(image, x, y)) / 2;
			temp_g = (GetPixelG(image, x, y)) / 2;

			for (m = 1; m <= BlurAmount; m++)
			{
				if ((x + m) < WIDTH)
				{
					temp_r = temp_r + GetPixelR(image, x + m, y) * 0.5 / BlurAmount;
					temp_b = temp_b + GetPixelB(image, x + m, y) * 0.5 / BlurAmount;
					temp_g = temp_g + GetPixelG(image, x + m, y) * 0.5 / BlurAmount;
				}
			}
			SetPixelR(image, x, y, temp_r);
			SetPixelG(image, x, y, temp_b);
			SetPixelB(image, x, y, temp_g);
		}
}

/* add brightness and contrast to the image */
IMAGE *BrightnessAndContrast(IMAGE *image, int brightness, int contrast) {
	int x, y, m;
	int WIDTH = ImageWidth(image);
	int HEIGHT = ImageHeight(image);
	unsigned int temp_r, temp_g, temp_b;

	for (x = 0; x < WIDTH; x++)
		for (y = 0; y < HEIGHT; y++)
		{
			temp_r = (GetPixelR(image, x, y)) / 2;
			temp_b = (GetPixelB(image, x, y)) / 2;
			temp_g = (GetPixelG(image, x, y)) / 2;

			for (m = 1; m <= BlurAmount; m++)
			{
				if ((x + m) < WIDTH)
				{
					temp_r = temp_r + GetPixelR(image, x + m, y) * 0.5 / BlurAmount;
					temp_b = temp_b + GetPixelB(image, x + m, y) * 0.5 / BlurAmount;
					temp_g = temp_g + GetPixelG(image, x + m, y) * 0.5 / BlurAmount;
				}
			}
			SetPixelR(image, x, y, temp_r);
			SetPixelG(image, x, y, temp_b);
			SetPixelB(image, x, y, temp_g);
		}
}

/* add watermark to the image */
/*IMAGE *Watermark(IMAGE *image) {
int x, y, m;
int WIDTH = ImageWidth(image);
int HEIGHT = ImageHeight(image);
unsigned int temp_r, temp_g, temp_b;

for (x = 0; x < WIDTH; x++)
for (y = 0; y < HEIGHT; y++)
{
temp_r = (GetPixelR(image, x, y)) / 2;
temp_b = (GetPixelB(image, x, y)) / 2;
temp_g = (GetPixelG(image, x, y)) / 2;

for (m = 1; m <= BlurAmount; m++)
{
if ((x + m) < WIDTH)
{
temp_r = temp_r + GetPixelR(image, x + m, y) * 0.5 / BlurAmount;
temp_b = temp_b + GetPixelB(image, x + m, y) * 0.5 / BlurAmount;
temp_g = temp_g + GetPixelG(image, x + m, y) * 0.5 / BlurAmount;
}
}
SetPixelR(image, x, y, temp_r);
SetPixelG(image, x, y, temp_b);
SetPixelB(image, x, y, temp_g);
}
}*/


/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
