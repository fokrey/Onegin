#include "Onegin.h"

void ctor (const char *filename, Text *text) {
    FILE *readfile = fopen(filename, "r");
    assert (readfile != nullptr);

    text->size   = get_file_size (readfile);
    if (text->size < 0)
        perror ("Error! Size of text is < 0\n");

    text->buffer = read_from_file (readfile, text->size);
    if (text->buffer == nullptr)
        perror ("Error! text.buffer is nullptr\n");

    fclose(readfile);

    text->num_lines = count_lines (text->buffer);
    if (text->num_lines < 0)
        perror ("Error! Number of lines is < 0\n");

    text->strings = create_strings_array (text->buffer, text->num_lines, text->size);
    if (text->strings == nullptr)
        perror ("Error! text.strings is nullptr\n");
}

char *read_from_file (FILE *readfile, long file_size) {
    assert (readfile != nullptr);

    char *buff_file = (char *) calloc(file_size + 2, sizeof(char));

    if (buff_file == nullptr) {
        perror ("buf_file is nullptr");
    }

    if (fread(buff_file, sizeof(char), file_size, readfile) != file_size) {
        printf("Error in reading file\n");
    }

    if (buff_file[file_size - 1] != '\n') {
        buff_file[file_size] = '\n';
        buff_file[file_size + 1] = '\0';
        return buff_file;
    }

    buff_file[file_size] = '\0';
    return buff_file;
}

long count_symb (char *buff_file, char symb) {
    char *begin_line = buff_file;
    char *end_line   = buff_file;

    long num_symb = 0;

    while ((end_line = strchr (begin_line, symb)) != nullptr) {
        begin_line = end_line + 1;
        num_symb++;
    }

    return num_symb;
}

long count_lines (char *buff_file) {
    return count_symb (buff_file, '\n');
}

long get_file_size (FILE *readfile) {
    assert (readfile != nullptr);

    if (fseek (readfile, 0, SEEK_END) != 0) {
        perror ("Error in fseek\n");
        return -1;
    }
    long file_size = ftell (readfile);

    if (file_size < 0) {
        perror ("Error in ftell\n");
        return -1;
    }

    rewind (readfile);

    return file_size;
}

String* fill_strings_array (char *file, long file_size, long num_lines, String *strings_array) {

    if (file_size < 0) {
        perror("Error in file size\n");
        return nullptr;
    }
    char *buff_file = file;
    if (buff_file == nullptr) {
        perror("Error in buff_file\n");
        return nullptr;
    }

    char* begin_line = buff_file;
    char* end_line   = buff_file;

    for (int i = 0; i < num_lines; i++)
    {
        end_line = strchr (begin_line, '\n');
        *end_line = '\0';

        strings_array[i].str = begin_line;
        strings_array[i].length = end_line - begin_line;
        begin_line = end_line + 1;
    }

    return strings_array;
}

String *create_strings_array (char* file_buffer, long num_lines, long file_size) {
    String *strings_array = (String *) calloc (num_lines, sizeof(String));
    assert (strings_array != nullptr);

    strings_array = fill_strings_array (file_buffer, file_size, num_lines, strings_array);
    assert (strings_array != nullptr);

    return strings_array;
}

void print_to_file (const String *strings_array, long num_lines, FILE *writefile, const char *separator) {
    assert (writefile != nullptr);

    fputs (separator, writefile);

    for (int i = 0; i < num_lines; i++) {
        fputs (strings_array[i].str, writefile);
        fputc ('\n', writefile);
    }
}

void print_initial_text (char *file_buffer, FILE *writefile, const char *separator) {
    fputs (separator, writefile);

    char* begin = file_buffer;

    for (int i = 0; i < 4165; i++)
    {
        fputs(begin, writefile);
        fputc('\n', writefile);

        begin = strchr (begin, '\0') + 1;
    }
}

void dtor (Text text) {
    free (text.buffer);
    free (text.strings);

    text.num_lines = 0;
    text.size      = 0;
    text.strings   = nullptr;
    text.buffer    = nullptr;
}

