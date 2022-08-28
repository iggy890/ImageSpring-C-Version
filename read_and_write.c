#include <stdio.h>
#include "Headers/stb_image.h"

// Write a struct to file
int writeStructToFile(char *filename, Image *data) {
    // Open the file in the 'wb' (write-binary) mode
    FILE *fl = fopen(filename, "wb");

    // Check if the file doesn't exist
    if (fl == NULL) {
        return 1; // Return 1 if the file doesn't exist
    }

    // Assign the dSize variable to the size of the data
    size_t dSize = sizeof(data);

    // Check if dSize is the same size as the written data
    if (dSize != fwrite(data, sizeof(Image), dSize, fl)) {
        return 1; // Return 1 because of an unsuccessful write
    }

    // Close the file
    fclose(fl);

    //free(data);

    return 0; // Return 0 if the file was successfully written
}

// Checks if a struct of type Image is empty
int isEmpty(Image i) {
    printf("Reached isEmpty\n");
    if (i.width == 0 && i.height == 0 && i.channels == 0) {
        return 1; // Return 1 because the Image is empty
    } else {
        return 0; // Return 0 because the Image is not empty
    }
}

// Read an array of structs from a specified file
Image *readStructFromFile(char *filename) {
    // Open the specified file in rb (read-binary)
    FILE *fl = fopen(filename, "rb");

    // Allocate enough memory to read the data from the file
    Image *data;

    // Read the file's data into the data pointer
    fread(data, sizeof(Image), INT64_MAX, fl);

    // Close the file as it is now no longer needed
    fclose(fl);

    // Return the data
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
    // Create the image object
    Image a;

    // Assign the values to the image object
    a.width = 6;
    a.height = 9;
    a.channels = 4;
    a.topic = "wow";

    // Write the Image object a to the file
    writeStructToFile("Saves/saves.bin", &a);

    // Read the file into the data pointer
    Image *data = readStructFromFile("Saves/saves.bin");

    // Define the current variable
    Image current = data[0];
    
    printf("Width: %d\n", current.width);
    printf("Height: %d\n", current.height);

    printf("Channels: %d\n", current.channels);
    printf("Topic: %s\n", current.topic);

    // Free the data variable
    //free(data);
}