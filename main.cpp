#include "Onegin.h"

int main () {
    const char *input_file =  "../data/hamlet_input.txt";
    const char *output_file = "../data/hamlet_output.txt";

    String file_buffer = open_read_close_file (input_file);
    assert (is_valid_string(file_buffer));

    String* strings_array = sort_strings (file_buffer);

    long num_lines = strings_array->length;

    open_write_close_file(output_file, strings_array, num_lines);

    free_memory (file_buffer, strings_array);

    return 0;
}

