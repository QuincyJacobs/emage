#include "file.h"


void printFile(char *fileName, char *image)
{
	FILE *file;
	file = fopen(fileName, "w+");
	fputs(image, file);
	fclose(file);
}

Pixel** getPixelArray(char *fileName, long *stride, long *rows)
{
	FILE *file;
	uint8 strideLength = 17;
	char strideBuff[17];

	file = fopen("test.emg", "r");
	fgets(strideBuff, strideLength, (FILE*)file);
	*stride = atol(strideBuff);
	*rows = ((getFileLength(file) - 16) / 8) / *stride;

	// allocate right amount of space for the amount of pixels being loaded
	Pixel **resultArray;
	resultArray = malloc(*rows * sizeof(Pixel));
	for (int i = 0; i < *rows; i++)
	{
		resultArray[i] = malloc(*stride * (sizeof(resultArray[0])));
	}

	// fill the resultArray with pixels from the file
	getPixels(file, resultArray, stride, rows);

	fclose(file);

	return resultArray;
}

// TODO: incompatible types - from 'FILE *' to 'char *'
void getPixels(FILE *file, Pixel **pixelArray, long *stride, long *rows)
{
	for (int i = 0; i < *rows; i++) {
		for (int j = 0; j < *stride; j++) {
			char pixelBuff[9];
			fgets(pixelBuff, 9, (FILE*)file);
			pixelArray[i][j] = getPixel(pixelBuff);
			// TODO: remove this print
			printPixel(&pixelArray[i][j]);
		}
	}
}

void printFileStatistics()
{
	FILE *file;
	char strideBuff[17];
	char pixelBuff[9];

	file = fopen("test.emg", "r");

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