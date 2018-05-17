#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define uint8 uint8_t

// binary
// char stride[] = "0000000000000000000000000000000000000000000000000000000000000101"; // now 5
// char redPixel[] = "11111111000000000000000011111111";
// char greenPixel[] = "00000000111111110000000011111111";
// char bluePixel[] = "00000000000000001111111111111111";

// hexadecimal
char stride[] = "0000000000000005";
char redPixel[] = "ff0000ff";
char greenPixel[] = "00ff00ff";
char bluePixel[] = "0000ffff";

// conclusion: Use hexadecimal for color storage as it's more compact than binary.
// leave stride as decimal.

typedef struct Pixel
{
    uint8 alpha;
    uint8 green;
    uint8 blue;
    uint8 red;
}Pixel;

// function declaration
Pixel getPixel(char s[8]);
uint8 hexToDec(char* chars, int size);
void printPixel(Pixel *pixel);
void hexifyPixel(Pixel *pixel);
void uint8ToHex(uint8 Byte, char *hex, int arrayIndex);
char getSingleHexChar(uint8 bits4);
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
  
    //printFile();
    //readFile();

    hexifyPixel(&pixel1);
  
    return 0;
}

Pixel getPixel(char s[8])
{
    Pixel pixel = { hexToDec(s, 2), hexToDec(&s[2], 2), hexToDec(&s[4], 2), hexToDec(&s[6], 2)};
    return pixel; 
}

// hexToDec returns uint8 because we will only use it for colors, which are also uint8
uint8 hexToDec(char* chars, int size)
{
    uint8 resultingDecimal = 0;
    uint8 res = 0;
    for(int i = 0; i < size; i++)
    {
	uint8 addedValue = pow(16, (size - i - 1));
	uint8 currentValue = 0;
	switch (chars[i]) {
	case '0':
	    currentValue = 0;
	    break;
	case '1':
	    currentValue = 1;
	    break;
	case '2':
	    currentValue = 2;
	    break;
	case '3':
	    currentValue = 3;
	    break;
	case '4':
	    currentValue = 4;
	    break;
	case '5':
	    currentValue = 5;
	    break;
	case '6':
	    currentValue = 6;
	    break;
	case '7':
	    currentValue = 7;
	    break;
	case '8':
	    currentValue = 8;
	    break;
	case '9':
	    currentValue = 9;
	    break;
	case 'a':
	    currentValue = 10;
	    break;
	case 'b':
	    currentValue = 11;
	    break;
	case 'c':
	    currentValue = 12;
	    break;
	case 'd':
	    currentValue = 13;
	    break;
	case 'e':
	    currentValue = 14;
	    break;
	case 'f':
	    currentValue = 15;
	    break;
	default:
	    currentValue = 0;
	    break;
	}
	resultingDecimal += (currentValue * addedValue);
    }
    return resultingDecimal;
}

void printPixel(Pixel *pixel)
{
    printf("red: %d   \t;  green: %d \t;  blue: %d \t;  alpha: %d \t;\n", pixel->red, pixel->green, pixel->blue, pixel->alpha);
}

void hexifyPixel(Pixel *pixel)
{
    char hex[4];
    uint8ToHex(pixel->red, hex, 0);
    uint8ToHex(pixel->green, hex, 2);
    uint8ToHex(pixel->blue, hex, 4);
    uint8ToHex(pixel->alpha, hex, 6);

    //TODO: remove print
    printf("\n%s\n", hex);
}

void uint8ToHex(uint8 Byte, char *hex, int arrayIndex)
{
    uint8 higherHex = 0;
    while(Byte >= 16)
    {
	Byte -= 16;
	higherHex++;
    }
  
    hex[arrayIndex] = getSingleHexChar(higherHex);
    hex[arrayIndex+1] = getSingleHexChar(Byte);
}

char getSingleHexChar(uint8 bits4)
{
    switch(bits4){
    case 0:
	return '0';
    case 1:
	return '1';
    case 2:
	return '2';
    case 3:
	return '3';
    case 4:
	return '4';
    case 5:
	return '5';
    case 6:
	return '6';
    case 7:
	return '7';
    case 8:
	return '8';
    case 9:
	return '9';
    case 10:
	return 'a';
    case 11:
	return 'b';
    case 12:
	return 'c';
    case 13:
	return 'd';
    case 14:
	return 'e';
    case 15:
	return 'f';
    default:
	return 0;
    }
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
