#include <stdio.h>
#include <stdlib.h>

// define a simple Image struct with 3 members (Image name, age, average)
typedef struct {
   int width, height, channels;
   char *topic;
   unsigned char *pixels;
} Image;

int write_data(char *filename, Image *data, int total);
Image *read_data(char *filename, int *total);

int main()
{
    // dynamically allocate space for an array of 3 Image structs
    Image *images;
    images = malloc(sizeof(Image) * 3);
    
    // initialize the array of structs with sample data
    images[0].topic = "Dandelion";
    images[0].width = 1;

    images[0].height = 1;
    images[0].channels = 3;

    images[1].topic = "Black";
    images[1].width = 1;

    images[1].height = 1;
    images[1].channels = 3;

    images[2].topic = "White";
    images[2].width = 1;
    
    images[2].height = 1;
    images[2].channels = 3;
    
    // attempt to write the data to the file, exit with an error status if there
    // is a problem writing the data otherwise report writing data was OK
    if (write_data("images.bin", images, 3))
        printf("Write data OK.\n");
    else 
    {
        printf("Error writing to file.\n");
        return 1;
    }
    
    // free the original dynamically allocated array as we are done with it now
    free(images);
    
    // total will store the total number of structs (we could call them records 
    // of data) retrieved from the file, and file_data will be a pointer to a 
    // dynamically allocated array on the heap containing the structs
    int total = 0;
    Image *file_data;
    
    // attempt to read the data from the file
    file_data = read_data("images.bin", &total);
    
    // if the read was unsuccessful, report the error and exit with error status
    if (file_data == NULL)
    {
        printf("Error reading from file.\n");
        return 1;
    }
    
    // output the data that was read from the file for verification
    printf("\nData read OK.\n\n");
    for (int i = 0; i < total; i++) {
        printf("Image %d\n", i + 1);
        printf("Topic: %s\n", file_data[i].topic);
        printf("Width: %d\n", file_data[i].width);
        printf("Height: %d\n", file_data[i].height);
        printf("Channels: %d\n", file_data[i].channels);
        printf("\n");
    }
    
    // free the dynamically allocated array used to store the data read from 
    // the file
    free(file_data);
    return 0;
}

// Returns true if the function was successful in writing total number of 
// Image structs stored in the data array to the file named filename, and 
// returns false if there was an error.
//
// We write the *total* to the file first, followed by the array of structs, 
// so that way when the file is later read we know large of an array to 
// allocate space for to store the data, i.e. the file format will be:
//
// total
// data[0]
// data[1]
// ...
//
int write_data(char *filename, Image *data, int total) {
    // file pointer variable
    FILE *file;
    
    // attempt to open the file with name filename, in 'write to binary file mode'
    file = fopen(filename, "wb");
    
    // return false if there was an error opening the file
    if (file == NULL) return 0;
    
    // write the total number of structs in the array to the file, return false 
    // if the function fails to write the data successfully
    if (fwrite(&total, sizeof(int), 1, file) != 1)
        return 0;
    
    // write the structs in the array to the file, return false if the function 
    // fails to write the data successfully
    if (fwrite(data, sizeof(Image), total, file) != total)
        return 0;
    
    // close access to the file, return false if this fails
    if (fclose(file) == EOF) return 0; 
    
    // if everything is successful return true
    return 1;
}

// Reads the array of Image structs from the file with filename, storing 
// them in a dynamically allocated array a pointer to which is returned by 
// the function, which also returns via the total parameter and pass by 
// pointer the total number of structs read from the file.    If reading the 
// file was unsuccessful we return NULL.
Image *read_data(char *filename, int *total)
{
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