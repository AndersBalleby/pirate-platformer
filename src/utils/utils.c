#include "utils.h"

// Læs CSV til 2D array
int readCSVToMap(const char *filename, int rows, int cols,
                  int map[rows][cols]) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("Fejl ved åbning af fil");
    return 0;
  }

  char line[MAX_LINE_LENGTH];
  int row = 0;

  while (fgets(line, sizeof(line), file) && row < rows) {
    char *token;
    int col = 0;

    // Fjern evt. linjeskift
    line[strcspn(line, "\n")] = 0;

    token = strtok(line, ",");
    while (token && col < cols) {
      map[row][col] = atoi(token);
      token = strtok(NULL, ",");
      col++;
    }

    if (col != cols) {
      fprintf(stderr, "Fejl: forkert antal kolonner i række %d\n", row);
      fclose(file);
      return 0;
    }

    row++;
  }

  if (row != rows) {
    fprintf(stderr, "Fejl: forkert antal rækker i filen\n");
    fclose(file);
    return 0;
  }

  fclose(file);
  return 1;
}

bool validatePath(const char *path) {
  return access(path, F_OK) == 0;
}
