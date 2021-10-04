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
/** /brief struct Text
 * buffer is a pointer to a buffer of text
 * size is size of text in bytes
 * num_lines is number of strings in text
 * strings is a pointer to array of strings */
//---------------------------------------------------------
struct Text {
    char *buffer    = nullptr;
    long size       = 0;
    long num_lines  = 0;
    String *strings = nullptr;
};

//---------------------------------------------------------
/** \brief Function is a constructor of structure Text
 * @param filename name of file
 * @return structure Text */
//---------------------------------------------------------
Text ctor (const char *filename);

//---------------------------------------------------------
/** \brief Function read_from_file reads text from file to buffer
 * @param [in] readfile file we read from
 * @param [in] file_size size of file
 * @return pointer to buffer and size of file */
//---------------------------------------------------------
char *read_from_file (FILE *readfile, long file_size);

//---------------------------------------------------------
/** \brief Function count_symb counts number of certain symbol in array
 * @param [in] file_buffer
 * @param [in] symb
 * @return number of counted symbols */
//---------------------------------------------------------
long count_symb (char *file_buffer, char symb);

//---------------------------------------------------------
/** \brief Function count_lines counts number of strings in file
 * @param [in] buff_file is buffer of file where we count number of lines
 * @return number of lines in buffer of file */
//---------------------------------------------------------
long count_lines    (char *buff_file);

//---------------------------------------------------------
/** \brief Function get_file_size calculates the file size in bytes
 * @param [in] readfile file we read from
 * @return number of bytes in file */
//---------------------------------------------------------
long get_file_size (FILE *readfile);

//---------------------------------------------------------
/** \brief Function create_strings_array creates and fills array of strings
 * @param [in] file_buffer from which we create array of strings
 * @param [in] num_lines is number of strings in file
 * @param [in] file_size size of file
 * @return buffer of strings */
//---------------------------------------------------------
String *create_strings_array (char *file_buffer, long num_lines, long file_size);

//---------------------------------------------------------
/** \brief Function fill_strings_array fills array with string pointers
 * @param [in] file duffer of file we read from
 * @param [in] file_size is size of file
 * @param [in] num_lines number of strings in text
 * @param [in] strings_array array we fill in
 * @return array of strings */
//---------------------------------------------------------
String* fill_strings_array (char *file, long file_size, long num_lines, String *strings_array);

//---------------------------------------------------------
/** \brief Function print_to_file prints array of strings to file
 * @param [in] strings_array the pointer to array of strings
 * @param [in] num_lines number of strings in array
 * @param [in] writefile file we write information to */
//---------------------------------------------------------
void print_to_file (const String *strings_array, long num_lines, FILE *writefile, const char *separator);

//---------------------------------------------------------
/** \brief Function print_initial_text prints initial text
 * @param [in] file_buffer buffer we print
 * @param [in] writefile file we print to
 * @param [in] separator a separator */
//---------------------------------------------------------
void print_initial_text (char *file_buffer, FILE *writefile, const char *separator);

//---------------------------------------------------------
/** \brief Function dtor clears memory and zeros structure's fields
 * @param [in] file_buffer
 * @param [in] strings_array */
//---------------------------------------------------------
void dtor (Text text);

//---------------------------------------------------------
/** \brief Function skip_symb skips unnecessary symbols
 * @param [in] elem element we check
 * @return 1 if elem is unnecessary symbol, 0 if it's not */
//---------------------------------------------------------
bool skip_symb (char elem);

//---------------------------------------------------------
/** \brief Function comp_left_to_right compares two strings from left to right
 * @param s1 [in] the first string
 * @param s2 [in] the second string
 * @return difference of strings */
//---------------------------------------------------------
int comp_left_to_right (const void *lhs, const void *rhs);

//---------------------------------------------------------
/** \brief Function comp_right_to_left compares two strings from right to left
 * @param s1 [in] the first string
 * @param s2 [in] the second string
 * @return difference of strings */
//---------------------------------------------------------
int comp_right_to_left (const void *lhs, const void *rhs);

//---------------------------------------------------------
/** \brief Function sort_left_to_right sorts text from left to right
 * @param [in] strings_array array of strings we want to sort
 * @param [in] num_lines is number of lines */
//---------------------------------------------------------
void sort_left_to_right (String *strings_array, long num_lines);

//---------------------------------------------------------
/** \brief Function sort_right_to_left sorts text from right to left
 * @param [in] strings_array array of strings we want to sort
 * @param [in] num_lines is number of line */
//---------------------------------------------------------
void sort_right_to_left (String *strings_array, long num_lines);

//---------------------------------------------------------
/** \brief Function swap_strings swaps two strings
 * @param [in] lhs the first string
 * @param [in] rhs the second string */
//---------------------------------------------------------
void swap_strings (String *lhs, String *rhs);

//---------------------------------------------------------
/** \brief Function bubble_sort sorts text using bubble sort
 * @param [in] strings_array is buffer
 * @param [in] compare is comparator */
//---------------------------------------------------------
void bubble_sort (String *strings_array, long num_lines, int (*compare) (const void *, const void *));

//---------------------------------------------------------
/** \brief my implementation of qsort */
//---------------------------------------------------------
void my_qsort (String *text, int left, int right, int (*comp) (const void *, const void *));