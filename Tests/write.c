#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
   char fName[256];
   char lName[256];
   int age;
}Person;

int main() {
   FILE *fl = fopen("file.bin", "wb");
   FILE *fl2 = fopen("file.txt", "w");

   int ims;
   printf("How many people do you want to add: ");
   scanf("%d", &ims);

   Person *people = malloc(sizeof(Person) * ims);

   for (int i = 0; i < ims; i++) {
      printf("What is Person number %d's age: ", i);
      scanf("%d", &people[i].age);

      printf("What is their first name: ");
      scanf("%s", people[i].fName);

      printf("What is their last name: ");
      scanf("%s", people[i].lName);
   }

   fwrite(people, sizeof(Person), 1,  fl);
   fwrite(&ims, sizeof(ims), 1, fl2);

   fclose(fl2);
   fclose(fl);
}