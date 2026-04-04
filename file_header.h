#ifndef UNTITLED_FILE_HEADER_H
#define UNTITLED_FILE_HEADER_H

void create_input_file(const char *filename);
char* read_input_file(const char *filename);
int count_sentences(const char *text);
char* get_second_sentence(const char *text, int *sen_length);
void display_results(int count, const char *sec_sentence, int sen_length );
void write_to_file(const char *filename, int count, const char *sec_sentence, int sen_length);

#endif //UNTITLED_FILE_HEADER_H