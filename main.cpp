#include "Onegin.h"

int main (int argc, const char *argv[]) {

    const char *input_file  = "../data/hamlet_input.txt";
    const char *output_file = "../data/hamlet_output.txt";

    if (argc >= 3) {
        input_file =  argv[1];
        output_file = argv[2];
    } else {
        printf ("Not enough arguments fo command line. "
                "Default names are used for input file: %s, output file: %s\n",
                input_file, output_file);
    }

    const char *separator_left_to_right = "-------------------------------------Text sorted from left to right-------------------------------------\n\n";
    const char *separator_right_to_left = "\n\n-------------------------------------Text sorted from right to left-------------------------------------\n\n";
    const char *separator_original_text = "\n\n-------------------------------------Original text------------------------------------------------------\n\n";

    Text text = ctor (input_file);

    FILE *writefile  = fopen (output_file, "w");
    assert (writefile != nullptr);

    sort_left_to_right (text.strings, text.num_lines);
    print_to_file (text.strings, text.num_lines, writefile, separator_left_to_right);

    sort_right_to_left (text.strings, text.num_lines);
    print_to_file (text.strings, text.num_lines, writefile, separator_right_to_left);

    print_initial_text (text.buffer, writefile, separator_original_text);

    fclose (writefile);
    dtor (text);

    return 0;
}

