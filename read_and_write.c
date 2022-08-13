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

    printf("size: %zu\n", dataSize);

    // Write the data to the file
    // And check if this is successful
    size_t a = fwrite(data, sizeof(Image), dataSize, fl);

    if (dataSize != a) {
        printf("error\n");
        return 1;
    }

    fclose(fl);
    //free(data);

    return a;
}

/*
Image *readStructFromFile(char *filename) {
    // open the file with name filename in 'read a binary file mode'
    FILE *file = fopen(filename, "rb");
    
    // if fopen() failed to open the file, return NULL 
    if (file == NULL) return NULL; 
    
    // Define the size of what we are going to read
    int total;

    // read the total number of Image struct data records stored in the file 
    // into the total pointer parameter
    if (fread(&total, sizeof(int), 1, file) != 0) 
        return NULL;
    
    // allocate enough space to store the array of Image structs
    Image *data = malloc(sizeof(Image) * total);
    
    // read the data from the file into the block of memory we have allocated, 
    // return NULL if the read was unsuccessful and free the dynamically allocated
    // memory to prevent a memory leak
    size_t valuesRead = fread(data, sizeof(Image), total, file);

    if (valuesRead != total) {
        printf("ok\n");
        free(data);
        return NULL;
    }
    
    // close the file, if this is unsuccessful free the dynamically allocated 
    // memory to prevent a memory leak and return NULL 
    if (fclose(file) == EOF) {
        free(data);
        return NULL;
    }
    
    // if everything is successful, return the pointer to the dynamically 
    // allocated array of Image structs
    return data;
}
*/
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
    
    //FILE *fl = fopen("Saves/saves.bin", "wb");

    //fwrite(&a, sizeof(Image), sizeof(a), fl);

    printf("%d\n", writeStructToFile("Saves/saves.bin", &a));

    //printf("Success\n\n");
    Image b;
    //Image b = *readStructFromFile("Saves/saves.bin");
    //printf("Width: %d\n", b.width);
    //printf("%d\n", b.height);
}