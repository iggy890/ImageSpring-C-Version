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

// Checks if a struct of type Image is empty
int isEmpty(Image i) {
    if (i.width == 0 && i.height == 0 && i.channels == 0) {
        return 1;
    } else {
        return 0;
    }
}

// Read an array of structs from a specified file
Image *read(char *filename) {
    // Open the specified file in rb (read-binary)
    FILE *fl = fopen(filename, "rb");

    // Allocate enough memory to read the data from the file
    Image *data = malloc(sizeof(Image) * INT16_MAX);

    // Read the file's data into the data pointer
    fread(data, sizeof(Image), INT16_MAX, fl);

    // Close the file as it is now no longer needed
    fclose(fl);

    // Define the 'i' variable
    int i = 0;

    // Allocate new memory that we will return soon
    Image *new = malloc(sizeof(Image) * INT16_MAX);
    
    
    while (!isEmpty(data[i]) /* Check if data[i] is null */) {
        // We have identified that data[i] is not null
        // Now we can append data[i] to the pointer new
        new[i] = data[i];

        // Increment i by 1
        i++;
    }

    // Free the now uneeded data
    free(data);

    // And return the pointer 'new'
    return new;
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