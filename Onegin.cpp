#include "Onegin.h"

String read_from_file (FILE *readfile) {
    assert (readfile != nullptr);

    long file_size = get_file_size(readfile);

    char *buff_file = (char *) calloc(file_size + 2, sizeof(char));

    if (buff_file == nullptr) {
        perror ("buf_file is nullptr");
    }

    if (fread(buff_file, sizeof(char), file_size, readfile) != file_size) {
        printf("Error in reading file\n");
    }

    String file = {file_size, buff_file};

    if (buff_file[file_size - 1] != '\n') {
        buff_file[file_size] = '\n';
        buff_file[file_size + 1] = '\0';
        return file;
    }

    buff_file[file_size] = '\0';
    return file;
}

String open_read_close_file (const char *filename) {

    FILE *readfile = fopen(filename, "r");
    assert (readfile != nullptr);

    String file = read_from_file(readfile);
    assert (is_valid_string(file));

    fclose(readfile);
    return file;
}

long count_symb (String file, char symb) {
    char *begin_line = file.str;
    char *end_line   = file.str;

    long num_symb = 0;

    while ((end_line = strchr (begin_line, symb)) != nullptr) {
        begin_line = end_line + 1;
        num_symb++;
    }

    return num_symb;
}

long count_lines (String file) {
    count_symb (file, '\n');
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
    }

    rewind (readfile);

    return file_size;
}

String* fill_strings_array (String file, long num_lines, String *strings_array) {
    long file_size = file.length;
    if (file_size < 0) {
        perror("Error in file size\n");
        return nullptr;
    }
    char *buff_file = file.str;
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

StringBuff create_strings_array (String file_buffer) {
    long num_lines = count_lines (file_buffer);

    String *strings_array = (String *) calloc (num_lines, sizeof(String));
    assert (strings_array != nullptr);

    strings_array = fill_strings_array (file_buffer, num_lines, strings_array);
    assert (strings_array != nullptr);

    StringBuff string_buff = {
            .num_lines = num_lines,
            .string = strings_array
    };

    return string_buff;
}

StringBuff make_copy_StringBuff (StringBuff strings_array) {
    StringBuff copy = {0};
    copy.string = (String *) calloc (strings_array.num_lines, sizeof (String));
    copy.num_lines = strings_array.num_lines;
    memcpy (copy.string, strings_array.string, strings_array.num_lines * sizeof (String));
    return copy;
}

void print_to_file (const StringBuff strings_array, FILE *writefile, const char *separator) {
    assert (writefile != nullptr);

    fputs (separator, writefile);

    for (int i = 0; i < strings_array.num_lines; i++) {
        fputs (strings_array.string[i].str, writefile);
        fputc ('\n', writefile);
    }
}

void print_initial_text (String file_buffer, FILE *writefile, const char *separator) {
    fputs (separator, writefile);

//    for (int i = 0; i < file_buffer.length; i++) {
//        fputc (file_buffer.str[i], writefile);
//
//        if (file_buffer.str[i] == '\0') {
//            fputc ('\n', writefile);
//        }
//    }

    char* begin = file_buffer.str;

    for (int i = 0; i < 4165; i++)
    {
        fputs(begin, writefile);
        fputc('\n', writefile);

        begin = strchr (begin, '\0') + 1;
    }
}

void free_memory (String file_buffer, StringBuff strings_array) {
    free (file_buffer.str);
    free (strings_array.string);
}

bool is_valid_string (String string) {
    return !(string.str == nullptr || string.length < 0);
}

bool is_valid_buff (StringBuff buff) {
    return !(buff.string == nullptr || buff.num_lines < 0);
}

void dump_strings (String *strings, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        printf ("%zu) %ld -> %s\n", i, strings[i].length, strings[i].str);
    }
}

void dump_buf_strings (StringBuff string_buff) {
    printf ("Number strings: %ld\n", string_buff.num_lines);
    dump_strings(string_buff.string, string_buff.num_lines);
}