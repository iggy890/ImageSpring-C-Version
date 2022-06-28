/*
ImageSpring Version 1
*/

#define STB_IMAGE_IMPLEMENTATION // Needed for stb_image.h
#define len(x) (sizeof(&x) / sizeof((x)[0])) // Get the size of an array
#define SAVES_DIR "saves.txt" // The Directory of the saves

#include <stdio.h> // Standard Studio Library
#include <float.h> // Floating Point Library

#include <string.h> // String Library
#include "stb_image.h" // Main Imaging Library

// Type Definitions
typedef unsigned char byte;
typedef struct Pixel Pixel;
typedef struct string string;
typedef struct Result Result;
typedef struct List List;
typedef struct uList uList;

// A Pixel Structure
struct Pixel {
    byte r; // Red Value
    byte g; // Green Value
    byte b; // Blue Value
};

struct List {
    int arraySize;
    int array[0];
};

struct uList {
    int arraySize;
    byte array[0];
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

List convertToInt(uList b) {
    List a;
    for (int i; i <= len(b.array); i++) {
        a.array[a.arraySize++] = (int)b.array[i];
    }

    return a;
}

// Close the inputted file
void closeFile(FILE *fl) {
    fclose(fl);
}

// Open the file in the specified mode
FILE *openFile(const char filename[], const char mode[]) {
    FILE *fl = fopen(filename, mode);
    if (fl == NULL) {
        fclose(fl);
    }
    else;
        return fl;
}

// Clear the file
void clearFile(const char filename[]) {
    fclose(fopen(filename, "w"));
}

// Write inputted text to a given file
void writeToFile(FILE *fl, char text[]) {
    fprintf(fl, "%s", text);
}

// Write a struct to file
void writeStructToFile(FILE *structBin, FILE *len, Image *Images) {
    int a = len(Images);

    if (structBin != NULL && len != NULL) {
        fwrite(&Images, sizeof(Image), 1, structBin);
        fwrite(&a, sizeof(int), 1, len);
    }
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

// Returns the pixel value at position (x, y)
Pixel getPixel(Image image, int x, int y) {
    int px = (x + image.width * y) * 3;
    Pixel result;
    result.r = image.pixels[px];
    result.g = image.pixels[px + 1];
    result.b = image.pixels[px + 2];
    return result;
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
    if (num <= num2) {
        return num;
    }
    else {
        return num2;
    }
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
    for (int x = 0; x < w; x++) {
        for (int y = 0; y < h; y++) {
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
    string r;
    char out;

    printf("%s", ins);
    scanf("%c", &out);
    
    r.size = sizeof(out);
    r.text[r.size] = out;

    return r;
}

Result search(Image img, Image *array) {
    Result r;

    for (int i; i <= len(array); i++) {
        r.pers[r.persLength++] = compareImage(img, array[i]);
        r.topics[r.topicsLength++] = array[i].topic;
    }
    quickSort(r, 0, sizeof(r.pers));

    return r;
}

int main() {
    Image r = stbi_load("ok.jpg", 0);

    printf("Width: %d\n", r.width);
    printf("Height: %d\n", r.height);
    printf("Channels: %d\n", r.channels);
}