#include "Onegin.h"

long count_symb (String file, char symb) {
    if (file.str == nullptr) {
        perror ("Error in counting symbols\n");
        return -1;
    }

    long num_symb = 0;
    for (int i = 0; i < file.length; i++) {
        if (file.str[i] == symb)
            num_symb++;
    }

    // strchr
    return num_symb;
}

long count_lines (String file) {
    return count_symb (file, '\n');
    // проверка \n на конце буффера
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

String read_from_file (FILE *readfile) {
    assert (readfile != nullptr);

    long file_size = get_file_size(readfile);

    char *buff_file = (char *) calloc(file_size + 1, sizeof(char));

    if (fread(buff_file, sizeof(char), file_size, readfile) != file_size) {
        printf("Error in reading file\n");
    }

    String file = {file_size, buff_file};

    if (file.str == nullptr || file.length < 0) {
        perror ("Error in struct String file\n");

        return String {
                .length = -1,
                .str = nullptr
        };
    }

    return file;
}

int find_symbol (long file_size, char *buff_file, char symbol, int i) {

    while (i < file_size) {
        if (buff_file[i] == symbol) {
            break;
        }
        i++;
    }
    return i;
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

    char* begin_line = nullptr;
    char* end_line = buff_file - 1;

    int i = 0;
    for (int j = 0; j < num_lines; j++)
    {
        begin_line = end_line + 1;

        i = find_symbol (file_size, buff_file, '\n', i);
        // strchr()

        end_line = buff_file + i;
        *end_line = '\0';
        strings_array[j].str = begin_line;
        strings_array[j].length = end_line - begin_line;
    }

    return strings_array;
}

// int comp (const void* a, const void* b)
int comp_left_to_right (String s1, String s2) {
    assert (s1.str != nullptr);
    assert (s2.str != nullptr);

    // String* s1 = (String *) a;

    return strcmp (s1.str, s2.str);

    // aaa bb
    // aa abb
    // aa; abb
}

int char_cmp (char c1, char c2) {
    return c1 - c2;
}

/* int comp_right_to_left (String s1, String s2) {
    assert (is_valid_string (s1));
    assert (is_valid_string (s2));

    s1.str += s1.length - 1;
    s2.str += s2.length - 1;

    for (int i = ; i < 0; i++) {

    }
    while (char_cmp (*s1.str, *s2.str) == 0) {

    }

} */

// универсальный swap (без memcpy);
void swap_strings (String *strings_array, int i, int j) {
    String temp = {0};

    temp = strings_array[i];
    strings_array[i] = strings_array[j];
    strings_array[j] = temp;
}

// добавить аргумент separator
void print_to_file (const String *strings_array, int num_lines, FILE *writefile) {
    assert (writefile != nullptr);


    fprintf (writefile, "--------------------------------Text sorted from left to right:--------------------------------\n\n");
    for (int i = 0; i < num_lines; i++) {
        fprintf (writefile, "%s\n", strings_array[i].str);
        // fputs
        // fputc
    }
}

bool is_valid_string (String string) {
    return !(string.str == nullptr || string.length < 0);
}

void dump_strings (String *strings, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        printf ("%zu) %ld -> %s\n", i, strings[i].length, strings[i].str);
    }
}

String open_read_close_file (const char *filename) {

    FILE *readfile = fopen(filename, "r");
    assert (readfile != nullptr);

    String file = read_from_file(readfile);
    assert (is_valid_string(file));

    fclose(readfile);
    return file;
}

String* sort_strings (String file_buffer) {
    long num_lines = count_lines (file_buffer);

    String *strings_array = (String *) calloc (num_lines, sizeof(String));
    assert (strings_array != nullptr);

    strings_array = fill_strings_array(file_buffer, num_lines, strings_array);
    assert (strings_array != nullptr);

    qsort (strings_array, num_lines, sizeof (String), (int (*)(const void *, const void *)) comp_left_to_right);

    return strings_array;
}

void open_write_close_file (const char *file_name, String *strings_array, long num_lines) {
    FILE *writefile  = fopen(file_name, "w");
    assert (writefile != nullptr);

    print_to_file (strings_array, num_lines, writefile);

    fclose (writefile);
}

void free_memory (String file_buffer, String *strings_array) {
    free (file_buffer.str);
    free (strings_array);
}