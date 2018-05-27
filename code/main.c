#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include "pixel.h"

#pragma warning(disable:4996)

// hexadecimal
//char stride[] = "0000000000000005";
//char redPixel[] = "ff0000ff";
//char greenPixel[] = "00ff00ff";
//char bluePixel[] = "0000ffff";

// function declaration
void printFile();
void readFile();

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

	//printFile();
	//readFile();

	return 0;
}

void printFile()
{
	FILE *file;

	file = fopen("test.emg", "w+");
	fputs("This is for testing fputs.\n", file);
	fclose(file);
}

void readFile()
{
	FILE *file;
	char buff[255];

	file = fopen("test.emg", "r");
	fscanf(file, "%s", buff);
	printf("1: %s\n", buff);

	fgets(buff, 255, (FILE*)file);
	printf("2: %s\n", buff);

	fgets(buff, 255, (FILE*)file);
	printf("3: %s\n", buff);
	fclose(file);
}
