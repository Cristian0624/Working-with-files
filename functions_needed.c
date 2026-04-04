#include "file_header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void create_input_file(const char *filename) {
    char *string = NULL;
    size_t bufsize = 0;

    printf("Enter a text (sentences should end with '.' ): ");
    fflush(stdout);

    ssize_t len = getline(&string, &bufsize, stdin);
    if (len == -1) {
        fprintf(stderr, "Error reading the input !\n");
        free(string);
        return;
    }

    if (string[len - 1] == '\n') {
        string[len - 1] = '\0';
        len--;
    }

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Cannot open %s for writing.\n", filename);
        free(string);
        return;
    }
    fprintf(file, "%s", string);
    fclose(file);

    printf("String written to %s.\n\n", filename);
    free(string);
}

char* read_input_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Cannot open %s for reading.\n", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    rewind(file);

    char *message = (char*) malloc((length + 1 ) * sizeof(char));
    if (message == NULL) {
        fprintf(stderr, "Memory allocation error !\n");
        fclose(file);
        return NULL;
    }

    fread(message, sizeof(char), length, file);
    message[length] = '\0';
    fclose(file);
    return message;
}

int count_sentences(const char *text) {
    int count = 0;
    const char *p = text;
    while (*p) {
        if (*p == '.')
            count++;

        p++;
    }
    return count;
}

char* get_second_sentence(const char *text, int *sen_length) {
    int found = 0;
    const char *p = text;
    const char *start = text;

    while (*p) {
        if (*p == '.') {
            found++;
            if (found == 2) {
                *sen_length = (int)(p - start)+ 1;

                char *sentence = (char*) malloc((*sen_length + 1) * sizeof(char));
                if (sentence == NULL)
                    return NULL;

                strncpy(sentence, start, *sen_length);
                sentence[*sen_length] = '\0';
                return sentence;
            }
            start = p + 1;
            while (*start == ' ')
                start++;
        }
        p++;
    }
    return NULL;
}

void display_results(int count, const char *sec_sentence, int sen_length ) {
    printf("Total number of sentences: %d \n", count);
    if (sec_sentence) {
        printf("Second sentence: {%s}\n", sec_sentence);
        printf("The length of the second sentence: %d (characters)", sen_length);
    }else {
        printf("There is no second sentence!\n");
    }
    printf("\n");
}

void write_to_file(const char *filename, int count, const char *sec_sentence, int sen_length) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Cannot open %s for writing.\n", filename);
        return;
    }
    fprintf(file, "Number of sentences are: %d\n", count);
    if (sec_sentence) {
        fprintf(file, "Second sentence is: {%s}\n", sec_sentence);
        fprintf(file, "Length of the second sentence: %d", sen_length);
    } else {
        fprintf(file, "There is no second sentence!\n");
    }
    fclose(file);
    printf("Results written to %s.\n", filename);
}
