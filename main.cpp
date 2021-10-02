#include "Onegin.h"
#include <inttypes.h>
#include <stdint.h>

int main () {
    const char *input_file =  "../data/hamlet_input.txt";
    const char *output_file = "../data/hamlet_output.txt";

    const char *separator_left_to_right = "-------------------------------------Text sorted from left to right-------------------------------------\n\n";
    const char *separator_right_to_left = "\n\n-------------------------------------Text sorted from right to left-------------------------------------\n\n";

    String file_buffer = open_read_close_file (input_file);
    assert (is_valid_string (file_buffer));

    StringBuff strings_array = create_strings_array (file_buffer);
    assert (is_valid_buff (strings_array));

    FILE *writefile  = fopen (output_file, "w");
    assert (writefile != nullptr);

    sort_left_to_right (strings_array);
    print_to_file (strings_array, writefile, separator_left_to_right);

    sort_right_to_left (strings_array);
    print_to_file (strings_array, writefile, separator_right_to_left);

    dump_buf_strings (strings_array);

    /* for (int i = 0; i < file_buffer.length; i++) {
        printf ("%c", file_buffer.str[i]);
    } */

    fclose (writefile);
    free_memory (file_buffer, strings_array);

    return 0;
}

