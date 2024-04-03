#pragma once

#include <stdio.h>
#include <string.h>

void readFromCSV(const char* filePath);
void readFromFile(const char* filePath, int* output);

void writeToFile(const char* filePath, const char* message);

FILE* openFile(const char* filePath, const char* mode);
