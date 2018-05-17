#include <stdio.h>
#include <stdint.h>

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

typedef struct Pixel
{
    uint8 alpha;
    uint8 green;
    uint8 blue;
    uint8 red;
}Pixel;

// function declaration
Pixel getPixel(char s[8]);
uint8 hex2Dec(char right, char left);
uint8 calcDec(char singleHexChar);
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

    pixelArray[0] = getPixel((char*)"ff0000ff");
    pixelArray[1] = getPixel((char*)"00ff00ff");
    pixelArray[2] = getPixel((char*)"0000ffff");
    pixelArray[3] = getPixel((char*)"ffffffff");

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
    Pixel pixel = { hex2Dec(s[1], s[0]), hex2Dec(s[3], s[2]), hex2Dec(s[5], s[4]), hex2Dec(s[7], s[6]) };
    return pixel; 
}

// TODO: This function
uint8 hexToDec(char* chars, int size)
{
    for(int i = 0; i < size; i++)
    {
	
    }
    return 0;
}

uint8 hex2Dec(char right, char left)
{
    uint8 highBits = calcDec(right) * 16;
    uint8 lowBits = calcDec(left);
    return highBits + lowBits;
}

uint8 calcDec(char singleHexChar)
{
    uint8 dec;
    switch (singleHexChar) {
    case '1':
	dec = 1;
	break;
    case '2':
	dec = 2;
	break;
    case '3':
	dec = 3;
	break;
    case '4':
	dec = 4;
	break;
    case '5':
	dec = 5;
	break;
    case '6':
	dec = 6;
	break;
    case '7':
	dec = 7;
	break;
    case '8':
	dec = 8;
	break;
    case '9':
	dec = 9;
	break;
    case 'a':
	dec = 10;
	break;
    case 'b':
	dec = 11;
	break;
    case 'c':
	dec = 12;
	break;
    case 'd':
	dec = 13;
	break;
    case 'e':
	dec = 14;
	break;
    case 'f':
	dec = 15;
	break;
    default:
	dec = 0;
	break;
    }
    return dec;
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
