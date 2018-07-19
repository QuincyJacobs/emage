#ifndef PIXEL_H_
#define PIXEL_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#ifndef uint8
	#define uint8 uint8_t
#endif

typedef struct Pixel
{
	uint8 red;
	uint8 green;
	uint8 blue;
	uint8 alpha;
}Pixel;

Pixel** getPixelArray(long *stride, long *rows);
Pixel getPixel(char s[8]);
void getHexPixel(char stringPixel[9], Pixel *pixel);
void printPixel(Pixel *pixel);

#endif