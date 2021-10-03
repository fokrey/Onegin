#include "Onegin.h"

int char_cmp (char c1, char c2) {
    return toupper(c1) - toupper(c2);
}

bool skip_symb (char elem) {
    return ispunct (elem) || isdigit (elem);
}

int comp_left_to_right (const void *lhs, const void *rhs) {
    char* lhs_c = ((const String *) lhs)->str;
    char* rhs_c = ((const String *) rhs)->str;
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

void sort_left_to_right (StringBuff strings_array) {
    qsort (strings_array.string, strings_array.num_lines, sizeof (StringBuff), comp_left_to_right);
}

void sort_right_to_left (StringBuff strings_array) {
    qsort (strings_array.string, strings_array.num_lines, sizeof (StringBuff), comp_right_to_left);
}
