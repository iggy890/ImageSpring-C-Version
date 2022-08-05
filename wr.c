
#include <stdio.h>
#include "Headers/stb_image.h"

// Write a struct to file
int writeStructToFile(char *filename, Image *data) {
    // file pointer variable
    FILE *file, *fileLen;
    
    // attempt to open the file with name filename, in 'write to binary file mode'
    file = fopen(filename, "wb");
    fileLen = fopen("Saves/saves.txt", "w");
    
    // return false if there was an error opening the file
    if (file == NULL) return 0;
    if (fileLen == NULL) return 0;
    
    int total = len(data);

    // write the total number of structs in the array to the file, return false 
    // if the function fails to write the data successfully
    if (fwrite(&total, sizeof(int), 1, fileLen) != 1)
        return 0;
    
    // write the structs in the array to the file, return false if the function 
    // fails to write the data successfully
    if (fwrite(data, sizeof(Image), total, file) != total)
        return 0;
    
    // close access to the file, return false if this fails
    if (fclose(file) == EOF) return 1; 
    if (fclose(file) == EOF) return 1;

    // if everything is successful return true
    return 0;
}

Image *readStructFromFile(char *filename, int *total) {
    FILE *file;
    
    // open the file with name filename in 'read a binary file mode'
    file = fopen(filename, "rb");
    
    // if fopen() failed to open the file, return NULL 
    if (file == NULL) return NULL;
    
    // read the total number of Image struct data records stored in the file 
    // into the total pointer parameter
    if (fread(total, sizeof(int), 1, file) != 1) 
        return NULL;
    
    // allocate enough space to store the array of Image structs
    Image *data = malloc(sizeof(Image) * *total);
    
    // read the data from the file into the block of memory we have allocated, 
    // return NULL if the read was unsuccessful and free the dynamically allocated
    // memory to prevent a memory leak
    if (fread(data, sizeof(Image), *total, file) != *total)
    {
        free(data);
        return NULL;
    }
    
    // close the file, if this is unsuccessful free the dynamically allocated 
    // memory to prevent a memory leak and return NULL 
    if (fclose(file) == EOF) 
    {
        free(data);
        return NULL;
    }
    
    // if everything is successful, return the pointer to the dynamically 
    // allocated array of Image structs
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
    if (writeStructToFile("Saves/saves.bin", &a)) {
        printf("Success\n\n");
        int s = sizeof(Image);
        Image a = *readStructFromFile("Saves/saves.bin", &s);
        printf("Width: %d\n", a.width);
        printf("%d\n", a.height);

    }
}