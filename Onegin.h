#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>
#include <ctype.h>
#include <stdint.h>
//---------------------------------------------------------
/** \brief struct String is used to
 * field length is length of te string
 * field str is a pointer to the string */
//---------------------------------------------------------
struct String {
    long length = 0;
    char *str = nullptr;
};

struct StringBuff {
    long num_lines = 0;
    String *string = nullptr;
};

//---------------------------------------------------------
/** \brief Function open_read_close_file opens file named filename,
 * reads it to file buffer and returns it
 * @param [in] filename is the name of file we open, read information from and close
 * @return struct String named file with pointer to file buffer and his size */
//---------------------------------------------------------
String open_read_close_file (const char *filename);

//---------------------------------------------------------
/** \brief Function read_from_file reads text from file to buffer
 * @param [in] readfile file we read from
 * @return pointer to buffer and size of file */
//---------------------------------------------------------
String read_from_file (FILE *readfile);

//---------------------------------------------------------
/** \brief Function count_lines counts number of strings in file
 * @param [in] file is buffer of file where we count number of lines
 * @return number of lines in buffer of file */
//---------------------------------------------------------
long   count_lines    (String file);

//---------------------------------------------------------
/** \brief Function get_file_size calculates the file size in bytes
 * @param [in] readfile file we read from
 * @return number of bytes in file */
//---------------------------------------------------------
long get_file_size (FILE *readfile);

//---------------------------------------------------------
/** \brief Function fill_strings_array fills array with string pointers
 * @param [in] file duffer of file we read from
 * @param [in] num_lines number of strings in text
 * @param [in] strings_array array we fill in
 * @return array of strings */
//---------------------------------------------------------
String* fill_strings_array (String file_buffer, long num_lines, String *strings_array);

//---------------------------------------------------------
/** \brief Function comp_left_to_right compares two strings from left to right
 * @param s1 [in] the first string
 * @param s2 [in] the second string
 * @return difference of strings */
//---------------------------------------------------------
int comp_left_to_right (const void *s1, const void *s2);

//---------------------------------------------------------
/** \brief Function swap_strings swaps two strings in strings_array
 * @param strings_array array or strings
 * @param i index of the first strings
 * @param j index of the second string */
//---------------------------------------------------------
void swap_strings (String *strings_array, int i, int j);

//---------------------------------------------------------
/** \brief
 * @param array_of_strings
 * @param left
 * @param right
 */
//---------------------------------------------------------
void q_sort (String *array_of_strings, int left, int right);

//---------------------------------------------------------
/** \brief Function sort_strings sort strings
 * @param file_buffer is file buffer we sort
 * @return sorted file buffer
 */
//---------------------------------------------------------
StringBuff sort_strings (String file_buffer);

//---------------------------------------------------------
/** \brief Function open_write_file opens file named file_name,
 * prints sorted text to file and closes it
 * @param file_name is the name of file we write information to
 * @param strings_array pointer to array of strings
 * @param num_lines number of strings in array */
//---------------------------------------------------------
void open_write_close_file (const char *file_name, StringBuff strings_array);

//---------------------------------------------------------
/** \brief Function print_to_file prints array of strings to file
 * @param strings_array the pointer to array of strings
 * @param num_lines number of strings in array
 * @param writefile file we write information to */
//---------------------------------------------------------
void print_to_file (const StringBuff strings_array, int num_lines, const char *separator, FILE *writefile);

//---------------------------------------------------------
/** \brief Function find_symbol finds symbol in buffer
 * @param file_size size of file
 * @param buff_file buffer of file
 * @param symbol symbol we want to find */
//---------------------------------------------------------
int find_symbol (long file_size, char *buff_file, char symbol, int i);

//---------------------------------------------------------
/** Function is_valid_string checks if string is valid
 * @param string string we want to check
 * @return 0, if string isn't valid, 1, if string is valid */
//---------------------------------------------------------
bool is_valid_string (String string);

//---------------------------------------------------------
/** \brief Function free_memory clears memory
 * @param file_buffer
 * @param strings_array */
//---------------------------------------------------------
void free_memory (String file_buffer, StringBuff strings_array);

//---------------------------------------------------------
/** \brief Function count_symb counts number of certain symbol in array
 * @param file_buffer
 * @param symb
 * @return number of counted symbols */
long count_symb (String file_buffer, char symb);