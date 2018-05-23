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
    uint8 red;
    uint8 green;
    uint8 blue;
    uint8 alpha;
}Pixel;

// function declaration
Pixel getPixel(char s[8]);
uint8 hexToDec(char* chars, int size);
void getHexPixel(Pixel *pixel);
void decToHex(uint8 dec, char hex[2]);
void printPixel(Pixel *pixel);
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

void getHexPixel(Pixel *pixel)
{
	char printPixel[9] = "00000000";
	decToHex(pixel->red, &printPixel[0]);
	decToHex(pixel->green, &printPixel[2]);
	decToHex(pixel->blue, &printPixel[4]);
	decToHex(pixel->alpha, &printPixel[6]);
	printf("\n%s", printPixel);
}

void decToHex(uint8 dec, char hex[2]) 
{
	// colors are saved as 2 hexadecimal digits, so minimum of 2
	int hexDigitAmount = 2;

	// get the amount of digits the hex will be (always 2 in this code, but didn't feel like breaking a working function)
	while (dec >= pow(16, hexDigitAmount))
	{
		hexDigitAmount++;
	}

	// calculate the hex digit (from high to low)
	for (int i = 1; i <= hexDigitAmount; i++)
	{
		// value indicating the decimal value of the highest hexadecimal
		int curHexDecimalValue = pow(16, ((hexDigitAmount - i)));
		// decimal value indicating the hexadecimal value for a single position (0-15)
		int curHexDigitValue = (dec / curHexDecimalValue);
		// remove the hex value (decimal) being processed from the total (decimal)
		dec -= (curHexDecimalValue*curHexDigitValue);

		switch (curHexDigitValue) {
		case 0:
			hex[i - 1] = '0';
			break;
		case 1:
			hex[i - 1] = '1';
			break;
		case 2:
			hex[i - 1] = '2';
			break;
		case 3:
			hex[i - 1] = '3';
			break;
		case 4:
			hex[i - 1] = '4';
			break;
		case 5:
			hex[i - 1] = '5';
			break;
		case 6:
			hex[i - 1] = '6';
			break;
		case 7:
			hex[i - 1] = '7';
			break;
		case 8:
			hex[i - 1] = '8';
			break;
		case 9:
			hex[i - 1] = '9';
			break;
		case 10:
			hex[i - 1] = 'a';
			break;
		case 11:
			hex[i - 1] = 'b';
			break;
		case 12:
			hex[i - 1] = 'c';
			break;
		case 13:
			hex[i - 1] = 'd';
			break;
		case 14:
			hex[i - 1] = 'e';
			break;
		case 15:
			hex[i - 1] = 'f';
			break;
		default:
			hex[i - 1] = '0';
			break;
		}
	}
}

void printPixel(Pixel *pixel)
{
    printf("red: %d   \t;  green: %d \t;  blue: %d \t;  alpha: %d \t;\n", pixel->red, pixel->green, pixel->blue, pixel->alpha);
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
