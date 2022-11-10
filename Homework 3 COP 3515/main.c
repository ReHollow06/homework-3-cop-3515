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
void fillIntArray(int *intArray, int arraySize, int val);
void arrayOutFormatted(int *numArray, int size, const char *stringFormat);
char hammingDecoder(int hammingCode);

void fillIntArray(int *intArray, int arraySize, int val)
{
  for (int i = 0; i < arraySize; i++)
  {
    intArray[i] = val;
  }
}

void arrayOutFormatted(int *numArray, int size, const char *stringFormat)
{
  for (int i = 0; i < size; i++)
  {
    printf(stringFormat, numArray[i]);
  }
}

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


char hammingDecoder(int hammingCode)
{
    int hammingBin[11];
    decToBinArray(hammingCode, hammingBin, 11);
    int p1;
    int p2;
    int p4;
    int p8;
    int errorIndex;
    int p1Array[5] = {hammingBin[8], hammingBin[6], hammingBin[4], hammingBin[2], hammingBin[0]};
    int p2Array[5] = {hammingBin[8], hammingBin[5], hammingBin[4], hammingBin[1], hammingBin[0]};
    int p4Array[3] = {hammingBin[6], hammingBin[5], hammingBin[4]};
    int p8Array[5] = {hammingBin[2], hammingBin[1], hammingBin[0]};

    if (hasEvenParity(p1Array, 5, hammingBin[10]))
    {
        p1 = 0;
    }
    else
    {
        p1 = 1;
    }

    if (hasEvenParity(p2Array, 5, hammingBin[9]))
    {
        p2 = 0;
    }
    else
    {
        p2 = 1;
    }

    if (hasEvenParity(p4Array, 3, hammingBin[7]))
    {
        p4 = 0;
    }
    else
    {
        p4 = 1;
    }

    if (hasEvenParity(p8Array, 3, hammingBin[3]))
    {
        p8 = 0;
    }
    else
    {
        p8 = 1;
    }
    int pBitArray[4] = {p8, p4, p2, p1};
    errorIndex = binArrayToDec(pBitArray, 4);

    if (errorIndex == 0)
    {
        int asciiValBin[7] = {hammingBin[0], hammingBin[1], hammingBin[2], hammingBin[4], hammingBin[5], hammingBin[6], hammingBin[8]};
        int asciiVal = binArrayToDec(asciiValBin, 7);
        printf("Done processing %d\n", hammingCode);
        printf("No transmission errors found in %d\n", hammingCode);
        return (char)asciiVal;
    }
    else
    {
        int arrayErrorIndex = (sizeof(hammingBin) / sizeof(hammingBin[0])) - errorIndex;
        int displayHammondCode[16];
        decToBinArray(hammingCode, displayHammondCode, 16);
        printf("Done processing %d\n", hammingCode);
        printf("Error in bit position: %d\n", errorIndex);
        printf("Token: %d, ", hammingCode);
        arrayOutFormatted(displayHammondCode, 16, "%d");
        printf("\n");
        hammingBin[arrayErrorIndex] += 1;
        if (hammingBin[arrayErrorIndex] == 2)
        {
            hammingBin[arrayErrorIndex] = 0;
        }
        int correctedHammingCode = binArrayToDec(hammingBin, 11);
        decToBinArray(correctedHammingCode, displayHammondCode, 16);
        printf("Corrected Token: %d, ", correctedHammingCode);
        arrayOutFormatted(displayHammondCode, 16, "%d");
        printf("\n");
        int asciiValBin[7] = {hammingBin[0], hammingBin[1], hammingBin[2], hammingBin[4], hammingBin[5], hammingBin[6], hammingBin[8]};
        int asciiVal = binArrayToDec(asciiValBin, 7);
        return (char)asciiVal;
    }
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

  // printf("==> Starting the encoding process:\n\n\n");
  // char lineCheck[100];
  // while (!feof(fileToEncode))
  // {
  //   char line[100];
  //   if (strcmp(line, lineCheck) == 0)
  //   {
  //     continue;
  //   }
  //   strcpy(lineCheck, line);
  //   fgets(line, sizeof(line) / sizeof(line[0]), fileToEncode);
  //   int hammingCodes[sizeof(line)];
  //   int hammingCodesSize = sizeof(line);
  //   fillIntArray(hammingCodes, hammingCodesSize, -1);

  //   printf("Processing: %s\n", line);
  //   for (int i = 0; i < strlen(line); i++) // prints out character and associated hammingcode, and adds hamming code to an array
  //   {
  //     if (line[i] == '\n')
  //     {
  //       continue;
  //     }

  //     printf("Character = '%c' - %d\n", line[i], hammingEncoder((int)line[i]));
  //     hammingCodes[i] = hammingEncoder((int)line[i]);
  //   }

  //   printf("Hamming Code: \n");

  //   for (int i = 0; i < hammingCodesSize; i++) // prints out hamming codes with 3 codes per line
  //   {
  //     if (hammingCodes[i] != -1)
  //     {
  //       int hammingBin[16];
  //       decToBinArray(hammingCodes[i], hammingBin, 16);
  //       printf("%5d ", hammingCodes[i]);
  //       arrayOutFormatted(hammingBin, 16, "%d");
  //       if ((i + 1) % 3 == 0)
  //       {
  //         printf("\n");
  //       }
  //     }
  //     else
  //     {
  //       continue;
  //     }
  //   }

  //   printf("\n\n");
  // }

  printf("==> Starting the decoding process: \n\n\n");
  int lineNums[3];
  fscanf(fileToDecode, "%7d%8d%8d ", &lineNums[0], &lineNums[1], &lineNums[2]);
  arrayOutFormatted(lineNums, 3, "%d ");

  fclose(fileToEncode);
  fclose(fileToDecode);

  return 0;
} /* main */