/*
 * COP 3515 – Fall Semester 2022
 *
 * Homework #3: Fixing The Problem
 *
 * (Your Name)
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

int hammingEncoder(int asciiVal);
void decToBinArray(int dataVal, int *binArray, int binArraySize);
int binArrayToDec(int *binArray, int binArraySize);

void decToBinArray(int dataVal, int *binArray, int binArraySize)
{
  for (int i = 0; i < binArraySize; i++)
  {
    binArray[i] = 0;
  }

  for (int i = binArraySize - 1; dataVal > 0; i--)
  {
    binArray[i] = dataVal % 2;
    dataVal /= 2;
  }
}

int binArrayToDec(int *binArray, int binArraySize)
{
  int decVal = 0;
  for (int i = 0; i < binArraySize; i++)
  {
    decVal += (int) pow(2, i) * binArray[(binArraySize-1) - i];
  }
  return decVal;
}


int hammingEncoder(int asciiVal)
{
  int hammingCode;
  int binVal[7];
  decToBinArray(asciiVal, binVal, sizeof(binVal)/sizeof(int));

  int hammingBin[11] = {binVal[0], binVal[1], binVal[2], -1, binVal[3], binVal[4], binVal[5], -1, binVal[6], -1, -1};

  int p1;
  int p2;
  int p4;
  int p8;


  return 1;
}

int main(void)
{
  int ascii = 84;
  int bin[8];
  hammingEncoder(ascii);
  

  return 0;
} /* main */