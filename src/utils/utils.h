#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define MAX_LINE_LENGTH 1024

bool validatePath(const char *path);
int readCSVToMap(const char *filename, int rows, int cols, int map[rows][cols]);
