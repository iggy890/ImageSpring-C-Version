/*
ImageSpring Version 1
*/

// Macros
#define STB_IMAGE_IMPLEMENTATION // Macro for stb_image.h
#define PythonRunner_ON // Macro for PythonRunner.h
#define SAVES_DIR "Saves/saves.bin" // The Directory of the saves
#define MAX_LINE 2048 // Required for readLine()

// Includes
#include <stdio.h> // Standard Studio Library
#include <pthread.h> // Threading Library

#include <string.h> // String Library
#include <unistd.h> // Needed for sleep()

#include "Headers/stb_image.h" // Main Imaging Library
#include "Headers/PythonRunner.h" // Python code runner

// Type Definitions
typedef unsigned char byte;
typedef struct Pixel Pixel;
typedef struct Result Result;

// Global Variables
Image *Images; // Global variable
int window_ended = 0; // True if the window has ended

// Structs

// A Pixel Structure
struct Pixel {
    byte r; // Red Value
    byte g; // Green Value
    byte b; // Blue Value
};

// The Result structure used for outputting the results
struct Result {
    int persLength; // Pers array length
    float pers[1000]; // Pers (Percents) array creation

    int topicsLength; // Topics array length
    char topics[2000]; // Topics array creation
};

// End of structs

// File functions

// A convoluted method of closing the inputted file
void closeFile(FILE *fl) {
    fclose(fl); // Close the file
}

// Open the file in the specified mode
FILE *openFile(char filename[], char mode[]) {
    FILE *fl = fopen(filename, mode); // Open the file in the specified mode
    if (fl == NULL) {
        fclose(fl); // Close the file as it does not exist
    }
    else;
        return fl; // Return the file
}

// Clear the file
void clearFile(char filename[]) {
    fclose(fopen(filename, "w")); // Open the file (clears the file also) then close the file
}

// Write inputted text to a given file
void writeToFile(FILE *fl, char text[]) {
    fprintf(fl, "%s", text); // Write the given to the file object
}

// Write a struct to file
int writeStructToFile(char *filename, Image *data) {
    // file pointer variable
    FILE *file, *fileLen;
    
    // attempt to open the file with name filename, in 'write to binary file mode'
    file = fopen(filename, "wb");
    
    // return false if there was an error opening the file
    if (file == NULL) return 0;
    
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

// Prints a pointer array of type Image
void print(Image *image) {
    for (int i; i < len(image); i++) {
        Image current = image[i];

        printf("Topic:\t%s\n", current.topic);
        printf("Width:\t%d\n", current.width);
        printf("Height:\t%d\n", current.height);
        printf("Channels:\t%d\n", current.channels);
    }
}

// Reads a struct array of type Image from a given file
Image *readStructFromFile(char *filename) {
    // open the file with name filename in 'read a binary file mode'
    FILE *file = fopen(filename, "rb");
    
    // if fopen() failed to open the file, return NULL 
    if (file == NULL) {
        return NULL; 
    }
    
    // Define the size of what we are going to read
    int total;

    // read the total number of Image struct data records stored in the file 
    // into the total pointer parameter
    if (fread(&total, sizeof(int), 1, file) != 1) {
        return NULL;
    }

    // allocate enough space to store the array of Image structs
    Image *data = malloc(sizeof(Image) * total);
    
    // read the data from the file into the block of memory we have allocated, 
    // return NULL if the read was unsuccessful and free the dynamically allocated
    // memory to prevent a memory leak
    if (fread(data, sizeof(Image), total, file) != total) {
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

// Read all the contents of the file
char *readFile(FILE *fl) {
    fseek(fl, 0, SEEK_END);
    long fsize = ftell(fl);
    fseek(fl, 0, SEEK_SET);
    char *string = malloc(fsize + 1);
    fread(string, fsize, 1, fl);
    string[fsize] = 0;
    return string;
}

// End of file functions

// Image functions

// Returns the pixel value at position (x, y)
Pixel getPixel(Image image, int x, int y) {
    int px = (x + image.width * y) * 3; // Calculate the Pixel offset
    Pixel r; // Create the result 
    r.r = image.pixels[px]; // Get the pixel Red value at position px
    r.g = image.pixels[px + 1]; // Get the pixel Green value at position px + 1
    r.b = image.pixels[px + 2]; // Get the pixel Blue value at position px + 2
    return r; // Return the pixel value
}

// Checks if num is higher than min and lower than max
int near(int num, int min, int max) {
    return num >= min && num <= max;
}

// Returns the positive version of the given number
int positive(int val) {
    if (val < 0) {
        return -val;
    } else {
        return val;
    }
}

// New and improved version of fancyClose()
float fancyClose(int num, int min, int max) {
    if (num <= min || max <= num) {
        return 0;
    } else {
        return positive(num - max / 2) / (max / 2);
    }
}

// Find the lowest value
int lowest(int num, int num2) {
    if (num <= num2) { // Check which value is lower
        return num; // Num is the lowest number and return it
    } else {
        return num2; // Num2 is the lowest number and return it
    }
}

// Compares 2 input Images img1 and img2 both inputs must be of Type Image (See line 370 in stb_image.h)
float compareImage(Image img1, Image img2) {
    float c; // Define the certainty

    int w = lowest(img1.width, img2.width); // Lowest width
    int h = lowest(img1.height, img2.height); // Lowest height

    for (int i; i > (w * h) * 3; i++) {
        c = c + near(img1.pixels[i], img2.pixels[i] - 50, img2.pixels[i] + 50); // Compare the two pixel values
    }

    return (w * h) * 3 / c * 100; // Convert into % value
}

// Slower version of compareImage() see line 216
float compareImageSlow(Image img1, Image img2) {
    float c; // Define the certainty
    int w = lowest(img1.width, img2.width); // Find the lowest width
    int h = lowest(img1.height, img2.height); // Find the lowest height
    for (int x = 0; x < w; x++) { // Loop through the X values
        for (int y = 0; y < h; y++) { // Loop through the Y values
            // Get the Pixel RGB Values of both images
            Pixel p = getPixel(img1, x, y);
            Pixel p2 = getPixel(img2, x, y);
            // Compare the Red, Green and Blue Channels of one Image and another
            c = c + near(p.r, p2.r - 50, p2.r + 50);
            c = c + near(p.g, p2.g - 50, p2.g + 50);
            c = c + near(p.b, p2.b - 50, p2.b + 50);
        }
    }
    return (w * h) * 2 / c * 100; // Convert to % value
}

void updateImages() {
    Images = readStructFromFile("Saves/saves.bin");
}

// End of Image functions

// Retrieved from tutorialspoint.com/explain-the-quick-sort-technique-in-c-language
void quickSort(Result r, int first, int last) {
   int i, j, pivot, temp;

   if (first < last) {
        pivot = first;

        i = first;
        j = last;

        while (i < j) {

            while (r.pers[i] <= r.pers[pivot] && i < last) {
                i++;
            }

            while (r.pers[j] > r.pers[pivot]) {
                j--;
            }

            if (i < j) {
                temp = r.pers[i];

                // Switch the percentages
                r.pers[i] = r.pers[j];
                r.pers[j] = temp;

                // Switch the topics
                r.topics[i] = r.topics[j];
                r.topics[j] = r.topics[i];
            }
        }
        temp = r.pers[pivot];
        
        // Switch the percentages
        r.pers[pivot] = r.pers[j];
        r.pers[j] = temp;

        // Switch the topics
        r.topics[pivot] = r.topics[j];
        r.topics[j] = r.topics[pivot];

        // Recursion
        quickSort(r, first, j-1);
        quickSort(r, j+1, last);
    }
}

// Compare the img input against the Image array input
Result search(Image img, Image *array) {
    Result r; // Create the result

    for (int i; i <= len(array); i++) { // Loop through the provided List of Images
        r.pers[r.persLength++] = compareImage(img, array[i]); // Compare the Image array[i] with Image img
        r.topics[r.topicsLength++] = *array[i].topic; // Add the Image array[i]'s topic to r.topics
    }
    quickSort(r, 0, sizeof(r.pers)); // Sort the variable r

    return r; // Return r
}

// Adds the inputted image to an array of Images
int addImage(Image image) {
    Images = malloc(len(Images) + sizeof(Image)); // Allocation
    Images[len(Images)] = image; // Append the image
    return 0; // Return 0
}

// Runs the c.py file using PythonRunner.h
void *run(void *vargp) {
    runFile("window.py"); // Run the file
    window_ended = 1;

    return NULL; // Return NULL
}


void *other(void *vargp) {
    while (1) {
        if (window_ended)
            return NULL;
        FILE *fp = fopen("Saves/window.txt", "r");

        char *dirText = malloc(sizeof(char) * MAX_LINE);
        char *topic = malloc(sizeof(char) * MAX_LINE);

        char *searchPressed = malloc(1);
        char *addImagePressed = malloc(1);

        fgets(dirText, MAX_LINE, fp);
        fgets(topic, MAX_LINE, fp);

        dirText[strcspn(dirText, "\n")] = 0;
        topic[strcspn(topic, "\n")] = 0;

        fgets(searchPressed, 3, fp);
        fgets(addImagePressed, 3, fp);

        if (strcmp(searchPressed, "1\n") == EXIT_SUCCESS) {
            updateImages();

            Result result = search(stbi_load(dirText, 3), Images);
            for (int i; i < result.persLength; i++) {
                printf("Image: %c %f%%\n", result.topics[i], result.pers[i]);
            }
        }

        if (strcmp(addImagePressed, "1") == EXIT_SUCCESS) {
            updateImages();

            Image a = stbi_load(dirText, 3);
            a.topic = topic;
            addImage(a);

            print(Images);
            printf("len: %lu\n", len(Images));

            writeStructToFile(SAVES_DIR, Images);
        }
        
        fclose(fp);

        free(dirText);
        free(topic);

        free(searchPressed);
        free(addImagePressed);
        if (window_ended)
            return NULL;

        usleep(250);
    }
    return NULL;
}

int main() {
    // Create the thread objects
    pthread_t thread1;
    pthread_t thread2;

    // Initialize the threads
    pthread_create(&thread1, NULL, run, NULL);
    pthread_create(&thread2, NULL, other, NULL);

    // Delete the threads and exit
    pthread_exit(NULL);
}