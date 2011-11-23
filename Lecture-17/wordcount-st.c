#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NUM_OF_NOVELS 6

void count_in_a_novel(char* filename, int* count_he, int* count_she)
{
    char line[1000];
    const char delimiters[] = " .,;:!-?\n";
    int c_he = 0, c_she = 0;
    FILE *fp = fopen(filename, "r");
    if(fp == NULL) {
        perror("Error opening file");
        exit(2);
    }

    char *token, *cp;

    while(!feof(fp)) {
        fgets(line, 1000, fp);
        token = strtok(line, delimiters);
        while(token != NULL) {
            if(strcmp(token, "he") == 0 || strcmp(token, "He") == 0)
                c_he++;
            else if (strcmp(token, "she") == 0 || strcmp(token, "She") == 0)
                c_she++;
            token = strtok(NULL, delimiters);
        }
    }


    printf("Count of \"he\" in %s: %d\n", filename, c_he);
    printf("Count of \"she\" in %s: %d\n", filename, c_she);

    *count_he += c_he;
    *count_she += c_she;

    fclose(fp);

}

int main()
{
    char *filenames[] = {"emma.txt", "mansfield-park.txt",
        "northanger-abbey.txt", "persuasion.txt", "pride-and-prejudice.txt",
        "sense-and-sensibility.txt" };
    int i, rc, sum_he = 0, sum_she = 0;

    for(i = 0; i < NUM_OF_NOVELS; i++) {
        count_in_a_novel(filenames[i], &sum_he, &sum_she);
    }

    printf("Total number of \"he\": %d\n", sum_he);
    printf("Total number of \"she\": %d\n", sum_she);

    return 0;
}

