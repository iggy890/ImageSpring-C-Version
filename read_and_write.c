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
    // Open the file with name filename in 'read a binary file mode'
    FILE *file = fopen(filename, "rb");
    
    // Check if the file exists
    if (file == NULL) {
        // Since we know the file doesn't exist we can:
        // Close the file:
        fclose(file);

        // And return NULL
        return NULL;
    }

    // Define the total size
    int total;

    // Read the file size into the total variable
    fread(&total, sizeof(int), 1, file);

    // Allocate the needed memory
    Image *data = malloc(sizeof(Image) * total);

    // Read the file into the allocated variable
    size_t readData = fread(data, sizeof(Image), total, file);

    // Check if the amount data read is the same as the amount of data in the file
    if (readData != total) {
        // We have identified that there is a problem
        // So now we free the allocated variable like so:
        free(data);

        // And we close the file:
        fclose(file);

        // And we then return NULL
        return NULL;
    }

    // If our code has reached here we can close the file:
    fclose(file);

    // And return the data
    return data;
}

Image *read(char *filename) {
    FILE *fl = fopen(filename, "rb");

    Image *data = malloc(sizeof(Image) * INT8_MAX);
    fread(data, sizeof(Image), INT8_MAX, fl);

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
    a.topic = "deez";

    writeStructToFile("Saves/saves.bin", &a);

    Image *data = read("Saves/saves.bin");
    
    Image current = data[0];

    printf("Width: %d\n", current.width);
    printf("Height: %d\n", current.height);

    printf("Channels: %d\n", current.channels);
    printf("Topic: %s\n", current.topic);

    free(data);
}