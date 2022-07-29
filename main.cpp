/*
ImageSpring Version 1
*/

#define STB_IMAGE_IMPLEMENTATION // Macro for stb_image.h
#define PythonRunner_ON // Macro for PythonRunner.h
#define len(x) (sizeof(&x) / sizeof((x)[0])) // Get the size of an array
#define SAVES_DIR "Saves/saves.bin" // The Directory of the saves
#define FILENAME_SIZE 1024 // Required for readLine()
#define MAX_LINE 2048 // Required for readLine()

#include <stdio.h> // Standard Studio Library
#include <float.h> // Floating Point Library

#include <pthread.h> // Threading Library
#include <string.h> // String Library

#include <unistd.h> // Needed for sleep()
#include <malloc/_malloc.h> // Needed for malloc()

#include "Headers/stb_image.h" // Main Imaging Library
#include "Headers/PythonRunner.hpp" // Python code runner

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
int writeStructToFile(char *filename, Image *data, int total) {
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
    Image *data = new Image[*total];
    
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

// Read all the contents of the file
char *readFile(FILE *fl) {
    fseek(fl, 0, SEEK_END);
    long fsize = ftell(fl);
    fseek(fl, 0, SEEK_SET);
    char *string = new char[fsize + 1];
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
        c = c + near(img1.pixels[i], img2.pixels[i] - 50, img2.pixels[i] + 50); // Compare the two pixel values
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
            c = c + near(p.r, p2.r - 50, p2.r + 50);
            c = c + near(p.g, p2.g - 50, p2.g + 50);
            c = c + near(p.b, p2.b - 50, p2.b + 50);
        }
    }
    return (w * h) * 2 / c * 100; // Convert to % value
}

void updateImages() {
    FILE *flLen = fopen("Saves/savesLen.txt", "r");

    int total;
    fread(&total, 1, 1, flLen);
    fclose(flLen);

    Images = readStructFromFile("Saves/saves.bin", &total);
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

int addImage(Image image) {
    Images = new Image[len(Images) + sizeof(Image)];
    Images[len(Images) + 1] = image;
    return 0;
}

void *run(void *vargp) {
    runFile((char*)"c.py");
    return NULL;
}


void *other(void *vargp) {
    int val = 0;
    while (1) {
        FILE *fp = fopen("Saves/window.txt", "r");

        char *dirText = new char[sizeof(char) * MAX_LINE];
        char *topicText = new char[sizeof(char) * MAX_LINE];

        char *searchPressed = new char[1];
        char *addImagePressed = new char[1];

        fgets(topicText, MAX_LINE, fp);
        fgets(dirText, MAX_LINE, fp);

        fgets(searchPressed, MAX_LINE, fp);
        fgets(addImagePressed, MAX_LINE, fp);

        if (strcmp(searchPressed, "1\n") == EXIT_SUCCESS) {
            val++;
            printf("Search pressed: %i\n", val);
            updateImages();

            Result result = search(stbi_load(dirText, 3), Images);
        }

        if (strcmp(addImagePressed, "1\n") == EXIT_SUCCESS) {
            printf("AddImage pressed\n");
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