#include <stdio.h>

#define uint8 uint8_t

struct Pixel
{
  // rgba in little endian will be written out as agbr
  uint8 alpha;
  uint8 green;
  uint8 blue;
  uint8 red;
};

// function declaration
void printPixel(struct Pixel *pixel);
void hexifyPixel(struct Pixel *pixel);
void uint8ToHex(uint8 Byte, char *hex, int arrayIndex);
char getSingleHexChar(uint8 bits4);
void printFile();
void readFile();

int main(void)
{
  struct Pixel pixel1;
  
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

void printPixel(struct Pixel *pixel)
{
  printf("red: %d;  green: %d;  blue: %d;  alpha: %d;\n", pixel->red, pixel->green, pixel->blue, pixel->alpha);
}

void hexifyPixel(struct Pixel *pixel)
{
  char hex[9];
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
