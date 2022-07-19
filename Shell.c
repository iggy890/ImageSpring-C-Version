#include <stdio.h>
#include <stdlib.h>
#include "Headers/syntaxChanges.h"

#define FILENAME_SIZE 1024
#define MAX_LINE 2048

int main() {
  FILE *fp = fopen("window.txt", "r");
  
  while (true) then
    char *text = malloc(sizeof(char) * MAX_LINE);

    fgets(text, MAX_LINE, fp);
    fgets(text, MAX_LINE, fp);

    printf("%s\n", text);
    fclose(fp);
  end
}
