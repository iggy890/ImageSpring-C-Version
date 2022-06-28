#include <stdlib.h>
#include <stdio.h>

struct Person 
{
    char f_name[256];
    char l_name[256];
    int age;
};

int main(int argc, char* argv[])
{
    FILE* data;
    FILE *fl = fopen("file.txt", "r");

    if ((data = fopen("file.bin", "rb")) == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }

    int num;
    fread(&num, sizeof(int), 1, fl);


    struct Person* people = malloc(sizeof(struct Person) * num);

    fread(people, sizeof(struct Person), 1, data);
    for (int i = 0; i < num; i++) {
        printf("Person %d's first name: %s\n", i, people[i].f_name);
        printf("Person %d's last name: %s\n", i, people[i].l_name);
        printf("Person %d's age: %d\n", i, people[i].age);
    }

    fclose(data);

    return 0;
}