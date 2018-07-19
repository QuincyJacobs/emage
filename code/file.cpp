#include "file.h"

// private function calls
void getPixelsFromFile(FILE *file, Pixel **pixelArray, long *stride, long *rows);
void getStrideFromLong(char *stringStride, long *longStride);
long getFileLength(FILE *file);

void printFile(char *fileName, char *text)
{
	FILE *file;
	file = fopen(fileName, "w+");
	fputs(text, file);
	fclose(file);
}

Pixel** getPixelArrayFromFile(char *fileName, long *stride, long *rows)
{
	uint8 strideLength = 17;
	char strideBuff[17];

	FILE *file;
	file = fopen("test.emg", "r");
	fgets(strideBuff, strideLength, (FILE*)file);

	*stride = atol(strideBuff);
	*rows = ((getFileLength(file) - 16) / 8) / *stride;

	// allocate right amount of space for the amount of pixels being loaded
	Pixel **pixelArray = getPixelArray(stride, rows);

	// fill the resultArray with pixels from the file
	getPixelsFromFile(file, pixelArray, stride, rows);

	fclose(file);

	return pixelArray;
}

// TODO: incompatible types - from 'FILE *' to 'char *'
// TODO: use HexRegEx to control input file
void getPixelsFromFile(FILE *file, Pixel **pixelArray, long *stride, long *rows)
{
	for (int i = 0; i < *rows; i++) {
		for (int j = 0; j < *stride; j++) {
			char pixelBuff[9];
			fgets(pixelBuff, 9, (FILE*)file);
			pixelArray[i][j] = getPixel(pixelBuff);
		}
	}
}

void writePixelsToFile(char *fileName, Pixel **pixelArray, long *stride, long *rows)
{
	char fileStride[17];
	char filePixel[9];

	FILE *file;
	file = fopen(fileName, "w+");

	//stride
	getStrideFromLong(fileStride, stride);
	fputs(fileStride, file);

	//pixels
	for (int i = 0; i < (*rows); i++)
	{
		for (int j = 0; j < (*stride); j++)
		{
			getHexPixel(filePixel, &pixelArray[i][j]);
			fputs(filePixel, file);
		}
	}

	fclose(file);
}

void printEmgFileStatistics(char *fileName)
{
	char strideBuff[17];
	char pixelBuff[9];

	FILE *file;
	file = fopen(fileName, "r");

	long amountOfPixels = (getFileLength(file) - 16) / 8;

	printf("\n######################################\n# FILE STATS\n######################################\n#\n");
	printf("# Amount of Pixels in file: %d\n", amountOfPixels);

	fgets(strideBuff, 17, (FILE*)file);
	printf("# Stride: \n#\t%s\n", strideBuff);
	printf("# Pixels: \n");
	for (int i = 0; i < amountOfPixels; i++) {
		fgets(pixelBuff, 9, (FILE*)file);
		printf("#\t%d: \t%s\n", i + 1, pixelBuff);
	}

	printf("#\n######################################\n\n");
	fclose(file);
}

void getStrideFromLong(char *stringStride, long *longStride)
{
	char buffer[17];
	uint8 strideLength = 15;
	ltoa(*longStride, buffer, 10);
	for (int i = 0; i <= strideLength; i++)
	{
		if (buffer[i] > 0)
		{
			stringStride[strideLength - i] = buffer[i];
		}
		else
		{
			stringStride[strideLength - i] = '0';
		}
	}
	stringStride[16] = '\0';
}

// https://stackoverflow.com/questions/2645598/counting-unknown-numbers-of-chars-from-a-file-in-c
long getFileLength(FILE *file) {
	fpos_t position; // fpos_t may be a struct and store multibyte info
	long length; // break support for large files on 32-bit systems

	fgetpos(file, &position); // save previous position in file

	if (fseek(file, 0, SEEK_END) // seek to end
		|| (length = ftell(file)) == -1) { // determine offset of end
		perror("Finding file length"); // handle overflow
	}

	fsetpos(file, &position); // restore position

	return length;
}