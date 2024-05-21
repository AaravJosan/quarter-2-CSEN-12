//count.c, Aarav Josan, 01/10/2005
//count.c is used a c program that is used to find the number of words in a given textfile.
#include <stdio.h>
#include <stdlib.h>

#define MAX_WORD_LENGTH 30

int count(char[]);

//main function
int main(int argc, char *argv[]){
    if (argc < 2){
        printf("Enter File!\n");
        return 0;
    }
    printf("Number of words in file: %d", count(argv[1]));

}

//Count number of words in text file
int count(char fileName[]){
    FILE *fptr;
    fptr = fopen(fileName, "r");

    if (fptr == NULL){
        printf("File not found\n");
        exit(0);
    }
    
    int words = 0;
    char string[MAX_WORD_LENGTH];
    while(fscanf(fptr, "%s", string) == 1)
        words++;

    return words;
}

