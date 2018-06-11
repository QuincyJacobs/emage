#include <stdio.h>

#include "pixel.h"
#include "file.h"

int main(void)
{
	char *readTestFileName = "test.emg";
	char *writeTestFileName = "writeTest.emg";
	printFile(readTestFileName, "0000000000000005ff0000ff00ff00ff0000ffffffffffffffffffffff0000ff00ff00ff0000ffffffffffffffffffffff0000ff00ff00ff0000ffffffffffffffffffffff0000ff00ff00ff0000ffffffffffffffffffff");
	
	long stride = 0;
	long rows = 0;

	Pixel** pixelArray = getPixelArrayFromFile(readTestFileName, &stride, &rows);
	writePixelsToFile(writeTestFileName, pixelArray, &stride, &rows);
	printEmgFileStatistics(writeTestFileName);

	// stop program from exiting
	getchar();

	return 0;
}

