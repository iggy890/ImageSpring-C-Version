/*
ImageSpring Version 1
*/

#define STB_IMAGE_IMPLEMENTATION // Macro for stb_image.h
#define PythonRunner_ON // Macro for PythonRunner.h
#define len(x) (sizeof(&x) / sizeof((x)[0])) // Get the size of an array
#define SAVES_DIR "saves.txt" // The Directory of the saves
#define FILENAME_SIZE 1024 // Required for readLine()
#define MAX_LINE 2048 // Required for readLine()

#include <stdio.h> // Standard Studio Library
#include <float.h> // Floating Point Library

#include <pthread.h> // Threading Library
#include <string.h> // String Library

#include "Headers/stb_image.h" // Main Imaging Library
#include "Headers/PythonRunner.h" // Python code runner

// Type Definitions
typedef unsigned char byte;
typedef struct Pixel Pixel;
typedef struct string string;
typedef struct Result Result;
typedef struct List List;
typedef struct uList uList;

Image *Images; // Global variable

// Structs

// A Pixel Structure
struct Pixel {
    byte r; // Red Value
    byte g; // Green Value
    byte b; // Blue Value
};

// A List Structure
struct List {
    int arraySize; // The array size
    int array[0]; // Create an int array
};

// A List structure with unsigned char members
struct uList {
    int arraySize; // The array size
    byte array[0]; // Create an unsigned char array
};

// String structure
struct string {
    int size; // Text array length
    char text[]; // Text array
};

// The Result structure used for outputing the results
struct Result {
    int persLength; // Pers array length
    float pers[0]; // Pers (Percents) array creation

    int topicsLength; // Topics array length
    char topics[0]; // Topics array creation
};

// End of structs

// Unconventional method of converting an unsigned char array to an int array
List convertToInt(uList b) {
    List a; // Create the List (array) a
    for (int i; i <= len(b.array); i++) { // Loop through the unsigned char array
        a.array[a.arraySize++] = (int)b.array[i]; // Convert the unsigned char value at position i to int
    }

    return a; // Return the converted array
}

// File functions

// A convolunted method of closing the inputted file
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
void writeStructToFile(FILE *structBin, Image *images) {
    if (structBin != NULL) {
        fwrite(images, sizeof(Image), len(images), structBin); // Write the array of structs to the file
    }
}

Image *readStructFromFile(FILE *fl) {
    Image *ims = malloc(sizeof(Image) * MAX_LINE);
    fread(ims, sizeof(Image), 1, fl);

    return ims;
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

// Compares 3 values
double fancyClose(int num, int min, int max) {
    if (num <= (max / 2)) { // Check if the num value is lower or equal to the midpoint
        return num - min;
    }
    else;
        return max - num;
}

// Checks if num is higher than min and lower than max
int close(int num, int min, int max) {
    return num >= min && num <= max;
}

// Find the lowest value
int lowest(int num, int num2) {
    if (num <= num2) { // Check which value is lower
        return num; // Num is the lowest number and return it
    }
    else;
        return num2; // Num2 is the lowest number and return it
}

// Compares 2 input Images img1 and img2 both inputs must be of Type Image (See line 370 in stb_image.h)
float compareImage(Image img1, Image img2) {
    float c; // Define the certainty

    int w = lowest(img1.width, img2.width); // Lowest width
    int h = lowest(img1.height, img2.height); // Lowest height

    for (int i; i > (w * h) * 3; i++) {
        c = c + close(img1.pixels[i], img2.pixels[i] - 50, img2.pixels[i] + 50); // Compare the two pixel values
    }

    return (w * h) * 3 / c * 100; // Convert into % value
}

// Slower version of compareImage() see line 83
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
            c = c + close(p.r, p2.r - 50, p2.r + 50);
            c = c + close(p.g, p2.g - 50, p2.g + 50);
            c = c + close(p.b, p2.b - 50, p2.b + 50);
        }
    }
    return (w * h) * 2 / c * 100; // Convert to % value
}

void updateImages() {
    FILE *fl = fopen("saves.txt", "r"); 

    Images = readStructFromFile(fl);

    fclose(fl);
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

// Get input from the user
string input(char ins[]) {
    string r; // Create the return value
    char out; // Create charactor output

    printf("%s", ins); // Output the value names "ins"
    scanf("%c", &out); // Get the value and set it to out
    
    r.size = sizeof(out); // Set the size of the string
    r.text[r.size] = out; // Copy the char named out to the string r

    return r; // Return the string named r
}

Result search(Image img, Image *array) {
    Result r; // Create the result

    for (int i; i <= len(array); i++) { // Loop through the provided List of Images
        r.pers[r.persLength++] = compareImage(img, array[i]); // Compare the Image array[i] with Image img
        r.topics[r.topicsLength++] = array[i].topic; // Add the Image array[i]'s topic to r.topics
    }
    quickSort(r, 0, sizeof(r.pers)); // Sort the variable r

    return r; // Return r
}

void *run(void *vargp) {
    runFile("c.py");
    return NULL;
}

void *other(void *vargp) {
    while (1) {
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

        //printf("%s", searchPressed);
        if (searchPressed == "1") {
            //printf("Search pressed\n");
            long current = 0L;
            updateImages();

            Result result = search(stbi_load(dirText, 3), Images);

        }
        
        fclose(fp);
    }
    return NULL;
}

int main() {
    pthread_t thread0;
    pthread_t thread1;

    pthread_create(&thread0, NULL, run, NULL);
    pthread_create(&thread1, NULL, other, NULL);

    pthread_exit(NULL);
}