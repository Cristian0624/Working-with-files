#include "functions_needed.c"

int main() {
    const char *input_file = "input.txt";
    const char *output_file = "output.txt";

    create_input_file(input_file);

    char *text = read_input_file(input_file);
    if (text == NULL)
        return EXIT_FAILURE;

    int count = count_sentences(text);
    int sen_length = 0;
    char *sec_sent = get_second_sentence(text, &sen_length);

    display_results(count, sec_sent, sen_length);

    write_to_file(output_file, count, sec_sent, sen_length);

    free(text); free(sec_sent);
    return EXIT_SUCCESS;
}