#include "Onegin.h"

int char_cmp (char c1, char c2) {
    return toupper(c1) - toupper(c2);
}

bool skip_symb (char elem) {
    return ispunct (elem) || isdigit (elem);
}

int comp_left_to_right (const void *lhs, const void *rhs) {
    const char* lhs_c = ((const String *) lhs)->str;
    const char* rhs_c = ((const String *) rhs)->str;

    //const char* lhs_c = lhs->str;
    //const char *rhs_c = rhs->str;

    assert (lhs_c != nullptr);
    assert (rhs_c != nullptr);

    if (skip_symb (*lhs_c)) {
        lhs_c++;
    }
    if (skip_symb (*rhs_c)) {
        rhs_c++;
    }
    while ((char_cmp (*lhs_c, *rhs_c)) == 0) {
        if (*lhs_c == '\0' || *rhs_c == '\0') {
            break;
        }
        while (skip_symb (*lhs_c)) {
            lhs_c++;
        }
        while (skip_symb (*rhs_c)) {
            rhs_c++;
        }
        lhs_c++, rhs_c++;
    }

    return char_cmp (*(lhs_c), *(rhs_c));
}

int comp_right_to_left (const void *lhs, const void *rhs) {
    const String *lhs_s = (const String *) lhs;
    const String *rhs_s = (const String *) rhs;

    int cur_len_lhs = lhs_s->length - 1;
    int cur_len_rhs = rhs_s->length - 1;

    for (; cur_len_lhs >= 0 && cur_len_rhs >= 0; --cur_len_lhs, --cur_len_rhs) {
        if (*(lhs_s->str + cur_len_lhs) != *(rhs_s->str + cur_len_rhs)) {
            return char_cmp(*(lhs_s->str + cur_len_lhs), *(rhs_s->str + cur_len_rhs));
        }
    }
    return cur_len_lhs - cur_len_rhs;
}

void swap_strings (String *lhs, String *rhs) {

    String temp = *lhs;
    *lhs = *rhs;
    *rhs = temp;
}

void bubble_sort (String *strings_array, long num_lines, int (*compare) (const void *, const void *))
{
    for (int i = 0; i < num_lines - 1; i++) {
        for (int j = 0; j < num_lines - i - 1; j++) {
            if (compare (&strings_array[j], &strings_array[j + 1]) > 0) {
                swap_strings (&strings_array[j], &strings_array[j + 1]);
            }
        }
    }
}

void my_qsort (String * text, int left, int right, int (*comp) (const void *, const void *)) {
    int last = 0;
    if (left >= right)
        return;
    swap_strings (&text[left], &text[(left + right) / 2]);
    last = left;
    for (int i = left + 1; i <= right; i++) {
        if ((*comp) (&text[i], &text[left]) < 0) {
            swap_strings (&text[++last], &text[i]);
        }
    }
    swap_strings (&text[left], &text[last]);
    my_qsort (text, left, last - 1, comp);
    my_qsort (text, last + 1, right, comp);
}

void sort_left_to_right (String *strings_array, long num_lines) {
    qsort (strings_array, num_lines, sizeof (String), comp_left_to_right);
    //bubble_sort (strings_array, comp_left_to_right);
    //my_qsort (strings_array, 0, num_lines - 1, comp_left_to_right);
}

void sort_right_to_left (String *strings_array, long num_lines) {
    //qsort (strings_array, num_lines, sizeof (String), comp_right_to_left);
    //bubble_sort (strings_array, num_lines, comp_right_to_left);
    my_qsort (strings_array, 0, num_lines - 1, comp_right_to_left);
}



