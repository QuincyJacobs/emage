#include <stdio.h>

#include "pixel.h"
#include "file.h"

int main(void)
{

	char *fileName = "test.emg";
	Pixel pixel1;

	Pixel pixelArrayy[4];

	pixelArrayy[0] = getPixel("ff0000ff");
	pixelArrayy[1] = getPixel("00ff00ff");
	pixelArrayy[2] = getPixel("0000ffff");
	pixelArrayy[3] = getPixel("ffffffff");

	printPixel(&pixelArrayy[0]);
	printPixel(&pixelArrayy[1]);
	printPixel(&pixelArrayy[2]);
	printPixel(&pixelArrayy[3]);

	pixel1.red = 0;
	pixel1.green = 2;
	pixel1.blue = 230;
	pixel1.alpha = 148;

	printPixel(&pixel1);

	getHexPixel(&pixel1);

	printFile(fileName, "0000000000000005ff0000ff00ff00ff0000ffffffffffffffffffffff0000ff00ff00ff0000ffffffffffffffffffffff0000ff00ff00ff0000ffffffffffffffffffffff0000ff00ff00ff0000ffffffffffffffffffff");
	printFileStatistics();
	
	long stride = 0;
	long rows = 0;
	Pixel** pixelArray = getPixelArray(fileName, &stride, &rows);

	getchar();

	return 0;
}

