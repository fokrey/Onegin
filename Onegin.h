#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>
#include <ctype.h>
#include <stdint.h>
#include <ctype.h>
//---------------------------------------------------------
/** \brief struct String
 * length is length of te string
 * str is a pointer to the string */
//---------------------------------------------------------
struct String {
    long length = 0;
    char *str = nullptr;
};

//---------------------------------------------------------
/** /brief struct StringBuff
 * num_lines is number of strings in buffer
 * string is a pointer to struct String
 */
//---------------------------------------------------------
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
/** \brief Function count_symb counts number of certain symbol in array
 * @param file_buffer
 * @param symb
 * @return number of counted symbols */
//---------------------------------------------------------
long count_symb (String file_buffer, char symb);

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
/** \brief Function create_strings_array creates and fills array of strings
 * @param [in] file_buffer from which we create array of strings
 * @return buffer of strings */
//---------------------------------------------------------
StringBuff create_strings_array (String file_buffer);

//---------------------------------------------------------
/** \brief Function fill_strings_array fills array with string pointers
 * @param [in] file duffer of file we read from
 * @param [in] num_lines number of strings in text
 * @param [in] strings_array array we fill in
 * @return array of strings */
//---------------------------------------------------------
String* fill_strings_array (String file_buffer, long num_lines, String *strings_array);

//---------------------------------------------------------
/** \brief Function make_copy_StringBuff makes a copy of strings_array
 * @param strings_array buffer we copy
 * @return a copy */
//---------------------------------------------------------
StringBuff make_copy_StringBuff (StringBuff strings_array);

//---------------------------------------------------------
/** \brief Function print_to_file prints array of strings to file
 * @param strings_array the pointer to array of strings
 * @param num_lines number of strings in array
 * @param writefile file we write information to */
//---------------------------------------------------------
void print_to_file (const StringBuff strings_array, FILE *writefile, const char *separator);

//---------------------------------------------------------
/** Function is_valid_string checks if string is valid
 * @param string string we want to check
 * @return 0, if string isn't valid, 1, if string is valid */
//---------------------------------------------------------
bool is_valid_string (String string);

//---------------------------------------------------------
/** Function is_valid_buff checks if buffer is valid
 * @param buff buffer we want to check
 * @return 0, if buffer isn't valid, 1, if buffer is valid */
//---------------------------------------------------------
bool is_valid_buff (StringBuff buff);

//---------------------------------------------------------
/** \brief Function free_memory clears memory
 * @param file_buffer
 * @param strings_array */
//---------------------------------------------------------
void free_memory (String file_buffer, StringBuff strings_array);

//---------------------------------------------------------
/** \brief Function skip_symb skips unnecessary symbols
 * @param elem element we check
 * @return 1 if elem is unnecessary symbol, 0 if it's not */
//---------------------------------------------------------
bool skip_symb (char elem);

//---------------------------------------------------------
/** \brief Function comp_left_to_right compares two strings from left to right
 * @param s1 [in] the first string
 * @param s2 [in] the second string
 * @return difference of strings */
//---------------------------------------------------------
int comp_left_to_right (const String *lhs, const String *rhs);

//---------------------------------------------------------
/** \brief Function comp_right_to_left compares two strings from right to left
 * @param s1 [in] the first string
 * @param s2 [in] the second string
 * @return difference of strings */
//---------------------------------------------------------
int comp_right_to_left (const String *lhs, const String *rhs);

//---------------------------------------------------------
/** \brief Function sort_left_to_right sorts text from left to right
 * @param strings_array array of strings we want to sort */
//---------------------------------------------------------
void sort_left_to_right (StringBuff strings_array);

//---------------------------------------------------------
/** \brief Function sort_right_to_left sorts text from right to left
 * @param strings_array array of strings we want to sort */
//---------------------------------------------------------
void sort_right_to_left (StringBuff strings_array);

// for debug
void dump_buf_strings (StringBuff string_buff);
void dump_strings (String *strings, size_t size);
