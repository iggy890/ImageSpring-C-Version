#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>

using namespace std;

class File {
    string name;
    FILE *read;
    FILE *write;

    ifstream streamRead;
    ifstream streamWrite;
    public:
        File(string fileName) {
            name = fileName;
            openFile();
        }

        ~File() {
            fclose(read);
            fclose(write);
        }

        void openFile() {
            read = fopen(name.c_str(), "r");
            string old = readFile();
            write = fopen(name.c_str(), "w");
            writeFile(old);
        }

        string readFile() {
            ifstream t(name);
            return string((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());
        }

        void writeFile(string text) {
            fprintf(write, "%s", text.c_str());
        }

        void clearFile() {
            fclose(fopen(name.c_str(), "w"));
        }
};

int main() {
    File a("test.txt");
    string b = a.readFile();
    cout << b << endl;
}