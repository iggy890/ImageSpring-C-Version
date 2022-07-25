#pragma once
#ifdef PythonRunner_ON

#include <stdio.h>
#include <stdlib.h>

void runSimpleString(char *code) {
    FILE *temp = fopen("temp.py", "w");

    fprintf(temp, "%s", code);
    fclose(temp);

    system("python3 temp.py && rm temp.py");
}

void runFile(char *filename) {
    char *command = malloc(sizeof(filename) + 7);
    sprintf(command, "%s %s", "python3", filename);
    system(command);
    free(command);
}

#endif