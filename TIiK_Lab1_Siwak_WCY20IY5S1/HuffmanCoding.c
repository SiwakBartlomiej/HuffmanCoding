#include <stdio.h>
#include <stdlib.h>
#include "structdef.h"
#pragma warning(disable:4996)
#pragma warning(disable:6387)

const char filePath[] = "C:\\Users\\dravi\\source\\repos\\TIiK_Lab1_Siwak_WCY20IY5S1\\TIiK_Lab1_Siwak_WCY20IY5S1\\XD.txt";

void WriteModelToFile(HuffmanNode output[], int length) {
    FILE* outputFilePointer = fopen("HuffmanModel.txt", "w");
    if (outputFilePointer == NULL)
        exit(1);

    fprintf(outputFilePointer, "%i\n", length);
    for (int i = 0; i < OUTPUT_ARRAY_LENGTH; i++)
    {
        if (output[i].Frequency > 0 && output[i].Ascii != '\0') {
            fprintf(outputFilePointer, "%i (%c) | %i\n",
                output[i].Ascii, output[i].Ascii, output[i].Frequency);
        }
    }
    fclose(outputFilePointer);
}

int CompareHuffmanNodes(const void* element1, const void* element2) {
    HuffmanNode* node1 = (HuffmanNode*)element1;
    HuffmanNode* node2 = (HuffmanNode*)element2;
    int comparisonResult = (node1->Frequency - node2->Frequency);

    if (comparisonResult == 0)
        comparisonResult = (node1->Ascii - node2->Ascii);

    return -comparisonResult;
}


int main()
{
    HuffmanNode output[512] = { {0} };
    unsigned char* buffer;
    FILE* filePointer = fopen(filePath, "rb");

    if (filePointer == NULL) {
        perror("Nie udalo sie otworzyc pliku.");
        exit(1);
    }

    fseek(filePointer, 0, SEEK_END);
    long length = ftell(filePointer);
    rewind(filePointer);
    buffer = (unsigned char*)calloc(1, length + 1);
    fread(buffer, sizeof(char), length, filePointer);
    fclose(filePointer);

    int i = 0;
    unsigned char symbol = *(buffer + i);

    while (symbol != '\0') {
        symbol = *(buffer + i);
        output[*(buffer + i)].Frequency++;
        output[*(buffer + i)].Ascii = symbol;
        i++;
    }

    qsort(output, OUTPUT_ARRAY_LENGTH,
        sizeof(HuffmanNode), CompareHuffmanNodes);
    WriteModelToFile(output, length);
    CreateTree(output);
    SaveTreeToFile();
    //CreateCodeTable();
}