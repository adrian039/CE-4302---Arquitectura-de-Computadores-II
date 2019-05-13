#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include "../config.h"
#define FALSE 0;
#define TRUE 1;

//Variables
int numberOfColumns, numberOfRows, numberOfBands, highVal, totalPixels, header;
unsigned char *image;

//Funciones
void readImage(char **argv, int k);

//Lee la imagen y guarda cada pixel en una matriz
void readImage(char **argv, int k)
{
    FILE *fpIn;
    char *string;
    int doneReading = FALSE;
    char c;
    fpIn = fopen(argv[k], "rb");

    if (fpIn == NULL)
    {
        perror("Such a file does not exist...");
        exit;
    }

    string = (char *)calloc(256, 3);

    while (!doneReading && (c = (char)fgetc(fpIn)) != '\0')
        switch (c)
        {
        case 'P':
            c = (char)fgetc(fpIn);
            switch (c)
            {
            case '2':
                header = 2;
                numberOfBands = 1;
                //pgm plain
                break;
            case '5':
                header = 5;
                numberOfBands = 1;
                //pgm Normal
                break;
            case '3':
                header = 3;
                numberOfBands = 3;
                //ppm plain
                break;
            case '6':
                header = 6;
                numberOfBands = 3;
                //ppm Normal
                break;
            }
            c = (char)fgetc(fpIn);
            if (c != 0x0A)
            {
                ungetc(c, fpIn);
            }
            else
            {
                ungetc(c, fpIn);
                fgets(string, 256, fpIn);
            }
            break;
        case '#':
            fgets(string, 256, fpIn);
            break;
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            ungetc(c, fpIn);
            fscanf(fpIn, "%d %d %d", &(numberOfColumns), &(numberOfRows), &(highVal));
            doneReading = TRUE;
            fgetc(fpIn);
            break;
        }
    totalPixels = numberOfRows * numberOfColumns;
    std::cout<<"Rows: "<<numberOfRows<<std::endl;
    std::cout<<"Columns: "<<numberOfColumns<<std::endl;
    std::cout<<"Total Pixels: "<<totalPixels<<std::endl;
    std::cout<<"High Value: "<<highVal<<std::endl;
    int pixels[numberOfRows][numberOfColumns];
    image = (unsigned char *)malloc(totalPixels);
    fread(image, 1, totalPixels, fpIn);
    int cont = 0;
    auto const filename = imgFile;
        std::ofstream file1(filename);
        if (file1.fail())
        {
            std::cerr << "!Error opening " << filename << std::endl;
            return;
        }
    for (int i = 0; i < totalPixels; i++)
    {

            file1 << (int)image[i] << std::endl;
    }
    free(image);
}

//Funcion principal
int main(int argc, char **argv)
{
    if (argc < 1)
    {
        return 0;
    }
    readImage(argv, 1);
    return 0;
}