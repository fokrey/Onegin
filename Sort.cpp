#include "Onegin.h"

int char_cmp (char c1, char c2) {
    return toupper(c1) - toupper(c2);
}

bool skip_symb (char elem) {
    return ispunct (elem) || isdigit (elem);
}

int comp_left_to_right (const String *lhs, const String *rhs) {
    char* lhs_c = lhs->str;
    char* rhs_c = rhs->str;
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

int comp_right_to_left (const String *lhs, const String *rhs) {
    int cur_len_lhs = lhs->length - 1;
    int cur_len_rhs = rhs->length - 1;

    for (; cur_len_lhs >= 0 && cur_len_rhs >= 0; --cur_len_lhs, --cur_len_rhs) {
        if (*(lhs->str + cur_len_lhs) != *(rhs->str + cur_len_rhs)) {
            return char_cmp(*(lhs->str + cur_len_lhs), *(rhs->str + cur_len_rhs));
        }
    }
    return cur_len_lhs - cur_len_rhs;
}

void sort_left_to_right (StringBuff strings_array) {
    qsort (strings_array.string, strings_array.num_lines, sizeof (StringBuff), (int (*) (const void*, const void*)) comp_left_to_right);
}

void sort_right_to_left (StringBuff strings_array) {
    qsort (strings_array.string, strings_array.num_lines, sizeof (StringBuff), (int (*) (const void*, const void*)) comp_right_to_left);
}
