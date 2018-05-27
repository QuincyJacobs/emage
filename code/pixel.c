#include "pixel.h"

// private function declarations:
uint8 hexToDec(char* chars, int size);
void decToHex(uint8 dec, char hex[2]);

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
