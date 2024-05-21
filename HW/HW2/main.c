#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#define MAX_VALUE 1000000
#define N 700
#define M 500

FILE *getFile(char[]);
char **getWords(FILE *wordsptr);
int search(char **words, char *elt, int direction);
void findWords(char puzzle[N][M], char **words);

static unsigned strhash(char *s){
    unsigned hash = 0;
    while(*s != '\0')
        hash = 31 * hash + *s++;

    return hash;
}

int main(int argc, char *argv[]){
    if(argc != 3){
        printf("One of the arguments is not given\n");
        return 0;
    }

    FILE *wordsPtr = getFile(argv[1]);
    FILE *puzzlePtr = getFile(argv[2]);

    if(wordsPtr == NULL || puzzlePtr == NULL) {
        printf("File not found!\n");
        return 0;
    }

    char **words = getWords(wordsPtr);

    char puzzle[N][M];

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++)
            fscanf(puzzlePtr, " %c", &puzzle[i][j]);
    }

    findWords(puzzle, words);

    free(words);
    fclose(wordsPtr);
    fclose(puzzlePtr);

    return 0;
}

FILE *getFile(char fileName[]){
    FILE *fptr;
    fptr = fopen(fileName, "r");
    return fptr;
}

char **getWords(FILE *fptr){
    char **words = (char**)malloc(sizeof(char*) * MAX_VALUE);
    assert(words);

    char *temp = (char*)malloc(sizeof(char) * MAX_VALUE);
    assert(temp);

    while(fscanf(fptr, "%s", temp) == 1) {
        if(strlen(temp) > 5) {
            int hash = strhash(temp) % MAX_VALUE;
            while(words[hash] != NULL)
                hash = (hash + 1) % MAX_VALUE;
            words[hash] = strdup(temp);
        }
    }

    free(temp);
    return words;
}

int search(char **words, char *elt, int direction){
    int hash = strhash(elt) % MAX_VALUE;

    while(words[hash] != NULL && (strcmp(words[hash], elt) != 0 || direction == -1)){
        hash = (hash + direction) % MAX_VALUE;
    }

    return hash;
}

void findWords(char puzzle[N][M], char **words){
    // Outer loop: iterate over each cell in the puzzle
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            // Directional loops for horizontal, vertical, and diagonal directions
            for(int dirX = -1; dirX <= 1; dirX++){
                for(int dirY = -1; dirY <= 1; dirY++){
                    if(dirX == 0 && dirY == 0) continue;  
                    // Forward and backward directions
                    for(int direction = -1; direction <= 1; direction += 2){
                        int currentX = i;
                        int currentY = j;
                        int wordLength = 0;

                        char currentWord[MAX_VALUE];
                         // Traverse in the specified direction
                        while(currentX >= 0 && currentX < N && currentY >= 0 && currentY < M){
                             // Build the current word
                            currentWord[wordLength++] = puzzle[currentX][currentY];
                            currentWord[wordLength] = '\0';
                            // Search for the current word in the hash table
                            int hash = search(words, currentWord, direction);
                            if(words[hash] != NULL && strcmp(words[hash], currentWord) == 0){
                                 // If a matching word is found, print it
                                printf("Found word: %s\n", currentWord);
                            }

                            // Move to the next cell in the specified direction
                            currentX += direction * dirX;
                            currentY += direction * dirY;
                        }
                    }
                }
            }
        }
    }
}

