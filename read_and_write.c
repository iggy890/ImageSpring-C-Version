#include <stdio.h>
#include "Headers/stb_image.h"

// Write a struct to file
int writeStructToFile(char *filename, Image *data) {
    // Open the file in the 'wb' (write-binary) mode
    FILE *fl = fopen(filename, "wb");

    // Check if the file doesn't exist
    if (fl == NULL) {
        return 1;
    }

    // Get the length of the data
    size_t dataSize = sizeof(data);

    // Write the data to the file
    // And check if this is successful
    size_t writtenData = fwrite(data, sizeof(Image), dataSize, fl);

    if (dataSize != writtenData) {
        printf("error\n");
        return 1;
    }

    fclose(fl);
    //free(data);

    return 0;
}

Image *readStructFromFile(char *filename) {
    // Open the specified file in the rb (read-binary mode)
    FILE *fl = fopen(filename, "rb");

    if (fl == NULL)
        return NULL; // Return 1 if the file doesn't exist

    // Stores the size of the file
    int total;

    // Read the size of the file into the 'total' integer
    fread(&total, sizeof(int), 1, fl);

    // Allocate the Image pointer
    Image *data = malloc(sizeof(Image) * total);

    // Read the file into the pointer
    size_t readData = fread(data, sizeof(Image), total, fl);
    
    // Check if the file read the correct amount of values
    if (readData != total)
        return NULL;

    fclose(fl);

    return data;
}

void print(Image *image) {
    for (int i; i < len(image); i++) {
        Image current = image[i];

        printf("\nTopic:\t%s\n", current.topic);
        printf("Width:\t%d\n", current.width);
        printf("Height:\t%d\n", current.height);
        printf("Channels:\t%d\n", current.channels);
    }
}

int main() {
    Image a;
    a.width = 6;
    a.height = 9;
    a.channels = 4;
    a.topic = "deez nutz";
    
    FILE *fl = fopen("Saves/saves.bin", "rb");

    printf("%d\n", writeStructToFile("Saves/saves.bin", &a));

    //printf("Success\n\n");
    Image *data = malloc(sizeof(Image));
    fread(data, sizeof(Image), 1, fl);

    printf("Width: %d\n", data->width);
    printf("Height: %d\n", data->height);

    printf("Channels: %d\n", data->channels);
    printf("Topic: %s\n", data->topic);

    free(data);
}