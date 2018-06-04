#ifndef FILE_H_
#define FILE_H_

#include <stdio.h>
#include <stdlib.h>

#include "pixel.h"

#pragma warning(disable:4996) // _CRT_SECURE_NO_WARNINGS (triggered by using fopen instead of fopen_s)

#define hexRegEx "^[a-fA-F0-9]+$"

// function declaration
void printFile(char *fileName, char *image);
Pixel** getPixelArray(char *fileName, long *stride, long *rows);
void getPixels(FILE *fileName, Pixel **pixelArray, long *stride, long *rows);
void printFileStatistics();
long getFileLength(FILE *file);

#endif

