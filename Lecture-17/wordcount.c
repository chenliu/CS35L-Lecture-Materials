#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define NUM_OF_NOVELS 6

typedef struct thread_data {
    int count_he;
    int count_she;
    char* filename;
} thread_data_t;

void* count_in_a_novel(void* args);


int main()
{
    pthread_t threads[NUM_OF_NOVELS];
    pthread_attr_t attr;
    long status;
    char *filenames[] = {"emma.txt", "mansfield-park.txt",
        "northanger-abbey.txt", "persuasion.txt", "pride-and-prejudice.txt",
        "sense-and-sensibility.txt" };
    int i, rc, sum_he = 0, sum_she = 0;

    thread_data_t thread_data_arr[NUM_OF_NOVELS];

    /**
     * Set up arguments passed to thread
     * Create a thread for each novel to count words
     */
    for(i = 0; i < NUM_OF_NOVELS; i++) {
        thread_data_arr[i].count_he = 0;
        thread_data_arr[i].count_she = 0;
        thread_data_arr[i].filename = filenames[i];
    }

    for(i = 0; i < NUM_OF_NOVELS;i++) {
        rc = pthread_create(&threads[i], NULL, count_in_a_novel, (void*) &thread_data_arr[i] );
        if(rc != 0) {
            perror("Failed to create a thread!");
            exit(1);
        }
    }

    /**
     * Wait for all threads to complete their tasks
     */
    for(i = 0; i < NUM_OF_NOVELS; i++) {
        rc = pthread_join(threads[i], (void*) &status);
        if(rc != 0) {
            perror("Failed to join a thread!");
            exit(1);
        }
    }

    for(i = 0; i < NUM_OF_NOVELS; i++) {
        sum_he += thread_data_arr[i].count_he;
        sum_she += thread_data_arr[i].count_she;
    }

    printf("Total number of \"he\": %d\n", sum_he);
    printf("Total number of \"she\": %d\n", sum_she);

    return 0;
}

void* count_in_a_novel(void* args)
{
    thread_data_t *thread_data = (thread_data_t*) args;
    const char delimiters[] = " .,;:!-?\n";
    char *token, *cp, *saveptr;
    char buffer[1000];
    FILE *fp = fopen(thread_data->filename, "r");
    if(fp == NULL) {
        perror("Error opening file");
        exit(2);
    }


    while(fgets(buffer, 1000, fp) != NULL) {
        token = strtok(buffer, delimiters);
        //token = strtok_r(buffer, delimiters, &saveptr);
        while(token != NULL) {
            if(strcmp(token, "he") == 0 || strcmp(token, "He") == 0)
                thread_data->count_he++;
            else if (strcmp(token, "she") == 0 || strcmp(token, "She") == 0)
                thread_data->count_she++;
            token = strtok(NULL, delimiters);
            //token = strtok_r(NULL, delimiters, &saveptr);
        }
    }
    if(ferror(fp)) {
        perror("I/O error!");
        exit(3);
    }

    printf("Count of \"he\" in %s: %d\n", thread_data->filename, thread_data->count_he);
    printf("Count of \"she\" in %s: %d\n", thread_data->filename, thread_data->count_she);

    fclose(fp);

    pthread_exit(NULL);
}
