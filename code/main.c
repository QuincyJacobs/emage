#include <stdio.h>

#include "pixel.h"
#include "file.h"

int main(void)
{
	Pixel pixel1;

	Pixel pixelArray[4];

	pixelArray[0] = getPixel("ff0000ff");
	pixelArray[1] = getPixel("00ff00ff");
	pixelArray[2] = getPixel("0000ffff");
	pixelArray[3] = getPixel("ffffffff");

	printPixel(&pixelArray[0]);
	printPixel(&pixelArray[1]);
	printPixel(&pixelArray[2]);
	printPixel(&pixelArray[3]);

	pixel1.red = 0;
	pixel1.green = 2;
	pixel1.blue = 230;
	pixel1.alpha = 148;

	printPixel(&pixel1);

	getHexPixel(&pixel1);

	printFile("0000000000000005ff0000ff00ff00ff0000ffffffffffff");
	printFileStatistics();

	getchar();

	return 0;
}

