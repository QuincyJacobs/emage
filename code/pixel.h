#ifndef PIXEL_H_
#define PIXEL_H_

#include <stdio.h>
#include <stdint.h>
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

Pixel getPixel(char s[8]);
void getHexPixel(Pixel *pixel);
void printPixel(Pixel *pixel);

#endif