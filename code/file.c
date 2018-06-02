#include "file.h"

void printFile(char* image)
{
	FILE *file;

	file = fopen("test.emg", "w+");
	fputs(image, file);
	fclose(file);
}

void printFileStatistics()
{
	FILE *file;
	char strideBuff[17];
	char pixelBuff[9];

	file = fopen("test.emg", "r");

	long amountOfPixels = (getFileLength(file) - 16) / 8;

	printf("\n######################################\n");
	printf("# FILE STATS\n######################################\n#\n");

	printf("# Amount of Pixels in file: %d\n", amountOfPixels);

	fgets(strideBuff, 17, (FILE*)file);
	printf("# Stride: \n#\t%s\n", strideBuff);
	printf("# Pixels: \n");
	for (int i = 0; i < amountOfPixels; i++) {
		fgets(pixelBuff, 9, (FILE*)file);
		printf("#\t%d: %s\n", i + 1, pixelBuff);
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