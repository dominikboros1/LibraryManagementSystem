#pragma once

#include <stdio.h>
#include <string.h>

void readFromCSV(const char* filePath);
void readFromFile(const char* filePath, int* output);

void writeToFile(const char* filePath, const char* message);

FILE* openFile(const char* filePath, const char* mode);

void menu() {
    printf("\n\n\n");
    printf("**************************************************************************************\n");
    printf("*                                       MENIU                                        *\n");
    printf("**************************************************************************************\n");
    printf("*                                                                                    *\n");
    printf("*                                 1.Borrow Books                                     *\n");
    printf("*                                                                                    *\n");
    printf("*                                 2.Return Books                                     *\n");
    printf("*                                                                                    *\n");
    printf("*                                 3.Donate Books                                     *\n");
    printf("*                                                                                    *\n");
    printf("*                                 4.View Loans                                       *\n");
    printf("*                                                                                    *\n");
    printf("*                                 5.Search Books                                     *\n");
    printf("*                                                                                    *\n");
    printf("*                                 0.Exit                                             *\n");
    printf("*                                                                                    *\n");
    printf("**************************************************************************************\n");
}
