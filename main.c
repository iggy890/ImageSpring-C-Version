/*
ImageSpring Version 1
*/

// Macros
#define STB_IMAGE_IMPLEMENTATION // Macro for stb_image.h
#define SAVES_DIR "Saves/saves.bin" // The Directory of the saves
#define MAX_LINE 2048 // Required for readLine()

// Includes
#include <stdio.h> // Standard Studio Library
#include <pthread.h> // Threading Library

#include <string.h> // String Library
#include <unistd.h> // Needed for sleep()

#include "Headers/stb_image.h" // Main Imaging Library

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

// Update the Images variable to reflect the saves.bin version
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

// Run the window.py file
void *run(void *vargp) {
    system("python3 window.py"); // Run the file
    window_ended = 1; // Set window ended to true

    return NULL; // Return NULL
}


void *other(void *vargp) {
    while (1) {
        // Check if the window has ended and stop the thread
        if (window_ended)
            return NULL;

        // Open the file
        FILE *fp = fopen("Saves/window.txt", "r");

        // Memory allocation
        char *dirText = malloc(sizeof(char) * MAX_LINE);
        char *topic = malloc(sizeof(char) * MAX_LINE);

        char *searchPressed = malloc(1);
        char *addImagePressed = malloc(1);

        // Read the file line by line
        fgets(dirText, MAX_LINE, fp);
        fgets(topic, MAX_LINE, fp);

        // Remove the '\n' character from the end
        dirText[strcspn(dirText, "\n")] = 0;
        topic[strcspn(topic, "\n")] = 0;

        // Read the rest of the lines
        fgets(searchPressed, 3, fp);
        fgets(addImagePressed, 3, fp);

        // Check if the 'Add Image' button is pressed
        if (strcmp(addImagePressed, "1") == EXIT_SUCCESS) {
            updateImages();
            Image a = stbi_load(dirText, 3);
            printf("Channels: %d\n", a.channels);

            a.topic = topic;
            addImage(a);

            printf("Channels: %d\n", Images[0].channels);
            printf("len: %lu\n", len(Images));

            writeStructToFile(SAVES_DIR, Images);
        }
        
        fclose(fp); // Close the file

        // Check if the 'Search' button is pressed
        if (strcmp(searchPressed, "1\n") == EXIT_SUCCESS) {
            updateImages();

            Result result = search(stbi_load(dirText, 3), Images);
            for (int i; i < result.persLength; i++) {
                printf("Image: %c %f%%\n", result.topics[i], result.pers[i]);
            }
        }

        // Free the allocated variables
        free(dirText);
        free(topic);

        free(searchPressed);
        free(addImagePressed);
        
        // If the window has ended then stop the thread
        if (window_ended)
            return NULL;

        // Wait for a little
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