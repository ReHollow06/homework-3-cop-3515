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
bool hasEvenParity(int *binArray, int binArraySize, int parityBit);

bool hasEvenParity(int *binArray, int binArraySize, int parityBit)
{
  int numOnes = parityBit;
  for (int i = 0; i < binArraySize; i++)
  {
    if (binArray[i] == 1)
    {
      numOnes++;
    }
  }

  if (numOnes % 2 == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

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
    decVal += (int)pow(2, i) * binArray[(binArraySize - 1) - i];
  }
  return decVal;
}

int hammingEncoder(int asciiVal)
{
  int hammingCode;
  int binVal[7];
  decToBinArray(asciiVal, binVal, sizeof(binVal) / sizeof(int));

  int hammingBin[11] = {binVal[0], binVal[1], binVal[2], -1, binVal[3], binVal[4], binVal[5], -1, binVal[6], -1, -1};

  int p1Array[5] = {hammingBin[8], hammingBin[6], hammingBin[4], hammingBin[2], hammingBin[0]};
  int p2Array[5] = {hammingBin[8], hammingBin[5], hammingBin[4], hammingBin[1], hammingBin[0]};
  int p4Array[3] = {hammingBin[6], hammingBin[5], hammingBin[4]};
  int p8Array[5] = {hammingBin[2], hammingBin[1], hammingBin[0]};

  if (hasEvenParity(p1Array, 5, 0))
  {
    hammingBin[10] = 0;
  }
  else
  {
    hammingBin[10] = 1;
  }

  if (hasEvenParity(p2Array, 5, 0))
  {
    hammingBin[9] = 0;
  }
  else
  {
    hammingBin[9] = 1;
  }

  if (hasEvenParity(p4Array, 3, 0))
  {
    hammingBin[7] = 0;
  }
  else
  {
    hammingBin[7] = 1;
  }

  if (hasEvenParity(p8Array, 3, 0))
  {
    hammingBin[3] = 0;
  }
  else
  {
    hammingBin[3] = 1;
  }

  hammingCode = binArrayToDec(hammingBin, sizeof(hammingBin) / sizeof(int));

  return hammingCode;
}

int main(void)
{

  FILE *fileToEncode = fopen("Homework #3 - Encoding.txt", "r");
  FILE *fileToDecode = fopen("Homework #3 - Decoding.txt", "r");

  if (fileToEncode == NULL)
  {
    printf("Couldn't open Homework #3 - Encoding.txt");
    return 1;
  }
  if (fileToDecode == NULL)
  {
    printf("Couldn't open Homework #3 - Encoding.txt");
    return 2;
  }
  
  


  printf("==> Starting the encoding process:\n\n\n");


  fclose(fileToEncode);
  fclose(fileToEncode);

  return 0;
} /* main */