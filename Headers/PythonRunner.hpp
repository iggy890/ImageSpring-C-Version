#ifdef PythonRunner_ON

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

void runSimpleString(char *code) {
    FILE *temp = fopen("temp.py", "w");

    fprintf(temp, "%s", code);
    fclose(temp);

    system("python3 temp.py && rm temp.py");
}

void runFile(std::string filename) {
    std::string command = "python3 " + filename;
    system(command.c_str());
}

#endif