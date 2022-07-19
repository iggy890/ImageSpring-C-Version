#include <stdio.h>
#include <stdlib.h>
#include "Headers/syntaxChanges.h"

#define FILENAME_SIZE 1024
#define MAX_LINE 2048

int main() {

  while (true) then
    FILE *fp = fopen("window.txt", "r");

    char *dirText = malloc(sizeof(char) * MAX_LINE);
    char *topicText = malloc(sizeof(char) * MAX_LINE);

    char *searchPressed = malloc(sizeof(char) * MAX_LINE);
    char *addImagePressed = malloc(sizeof(char) * MAX_LINE);

    char *configText = malloc(sizeof(char) * MAX_LINE);

    fgets(topicText, MAX_LINE, fp);
    fgets(dirText, MAX_LINE, fp);

    fgets(searchPressed, MAX_LINE, fp);
    fgets(addImagePressed, MAX_LINE, fp);

    fgets(configText, MAX_LINE, fp);

    printf("Directory Text: %s\n", dirText);
    printf("Topic Text: %s\n", topicText);

    printf("Search Button Pressed: %s\n", searchPressed);
    printf("Add Image Button Pressed: %s \n", addImagePressed);

    printf("Config text: %s\n", configText);

    fclose(fp);
  end
}
