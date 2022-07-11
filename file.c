#include <stdio.h>
#include <stdlib.h>

void runSimpleString(char *code) {
    FILE *temp = fopen("temp.py", "w");

    fprintf(temp, "%s", code);
    fclose(temp);

    system("python3 temp.py");
    remove("temp.py");
}

int main() {
    runSimpleString("from tkinter import *\nwindow=Tk()\nwindow.geometry('400x400')\nwindow.title('test')\nwindow.mainloop()");
}