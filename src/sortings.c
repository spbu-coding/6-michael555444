#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "sortings.h"

void bubble(strings_array_t strings_array, array_size_t array_size, comparator_func_t comparator) {
    for (array_size_t i = 0; i < array_size; i++)
        for (array_size_t j = i + 1; j < array_size; j++)
            if (comparator(strings_array[i], strings_array[j]) > 0) {
                char *swapper = strings_array[i];
                strings_array[i] = strings_array[j];
                strings_array[j] = swapper;
            }
}

void insertion(strings_array_t strings_array, array_size_t array_size, comparator_func_t comparator) {
    int place;
    for (int i = 0; i < (int) array_size; i++) {
        char *next_element = strings_array[i];
        place = i - 1;
        while (place >= 0 && comparator(strings_array[place], next_element)) {
            strings_array[place + 1] = strings_array[place];
            place--;
        }
        strings_array[place + 1] = next_element;
    }
}

void merge(strings_array_t strings_array, array_size_t array_size, comparator_func_t comparator) {
    array_size_t step = 1;
    strings_array_t new_array = malloc(sizeof(char *) * array_size);

    while (step < array_size) {
        array_size_t index = 0, left = 0, middle = left + step, right = left + step * 2;
        do {
            if (middle > array_size) {
                middle = array_size;
            }
            if (right > array_size) {
                right = array_size;
            }
            array_size_t i = left, j = middle;
            while (i < middle && j < right) {
                if (comparator(strings_array[j], strings_array[i])) {
                    new_array[index++] = strings_array[i++];
                } else {
                    new_array[index++] = strings_array[j++];
                }
            }
            while (i < middle) {
                new_array[index++] = strings_array[i++];
            }
            while (j < right) {
                new_array[index++] = strings_array[j++];
            }
            left += step * 2;
            middle += step * 2;
            right += step * 2;
        } while (left < array_size);
        for (array_size_t i = 0; i < array_size; i++) {
            strings_array[i] = new_array[i];
        }
        step *= 2;
    }
    free(new_array);
}

void quick_sorting(strings_array_t strings_array, int left, int right, comparator_func_t comparator) {
    int i = left, j = right;
    char *middle = strings_array[(left + right) / 2];

    do {
        while (comparator(middle, strings_array[i]) && (i < right)) {
            i++;
        }
        while (comparator(strings_array[j], middle) && (j > left)) {
            j--;
        }
        if (i <= j) {
            char *swapper = strings_array[i];
            strings_array[i] = strings_array[j];
            strings_array[j] = swapper;
            i++;
            j--;
        }
    } while (i <= j);

    if (left < j) {
        quick_sorting(strings_array, left, j, comparator);
    }
    if (i < right) {
        quick_sorting(strings_array, i, right, comparator);
    }
}

void quick(strings_array_t strings_array, array_size_t array_size, comparator_func_t comparator) {
    quick_sorting(strings_array, 0, (int) array_size - 1, comparator);
}

void swapper(strings_array_t first_array, strings_array_t second_array) {
    char *swapper = *first_array;
    *first_array = *second_array;
    *second_array = swapper;
}

void radix_sorting(strings_array_t strings_array, array_size_t array_size, int position) {
    array_size_t count[UCHAR_MAX + 1], mode, i;
    strings_array_t bucket[UCHAR_MAX + 1], top[UCHAR_MAX + 1];
    while (array_size > 1) {
        memset(count, 0, sizeof(array_size_t) * (UCHAR_MAX + 1));
        for (i = 0; i < array_size; i++) {
            count[(int) strings_array[i][position]]++;
        }

        mode = 1;
        for (i = 2; i <= UCHAR_MAX; i++)
            if (count[i] > count[mode]) {
                mode = i;
            }

        if (count[mode] < array_size) {
            bucket[0] = strings_array;
            top[0] = strings_array;
            for (i = 1; i <= UCHAR_MAX; i++) {
                top[i] = bucket[i] = bucket[i - 1] + count[i - 1];
            }

            for (i = 0; i <= UCHAR_MAX; i++) {
                while (top[i] < bucket[i] + count[i])
                    if ((array_size_t) top[i][0][position] == i) {
                        top[i]++;
                    } else {
                        swapper(top[i], top[(int) top[i][0][position]]++);
                    }
            }

            for (i = 1; i <= UCHAR_MAX; i++)
                if (i != mode) {
                    radix_sorting(bucket[i], count[i], position + 1);
                }

            array_size = count[mode];
            strings_array = bucket[mode];
            position++;
        } else {
            position++;
        }
    }
}

void radix(strings_array_t strings_array, array_size_t array_size, comparator_func_t comparator) {
    radix_sorting(strings_array, array_size, 0);
    if (comparator == descending) {
        for (array_size_t i = 0; i < array_size / 2; i++) {
            char *swapper = strings_array[i];
            strings_array[i] = strings_array[array_size - i - 1];
            strings_array[array_size - i - 1] = swapper;
        }
    }
}


int ascending(const char *first_string, const char *second_string) {
    char first_string_char, second_string_char;
    do {
        first_string_char = *first_string++;
        second_string_char = *second_string++;
        if (first_string_char == END_OF_STRING) {
            return (first_string_char - second_string_char) > 0;
        }
    } while (first_string_char == second_string_char);
    return (first_string_char - second_string_char) > 0;
}

int descending(const char *first_string, const char *second_string) {
    char first_string_char, second_string_char;
    do {
        first_string_char = *first_string++;
        second_string_char = *second_string++;
        if (first_string_char == END_OF_STRING) {
            return (first_string_char - second_string_char) < 0;
        }
    } while (first_string_char == second_string_char);
    return (first_string_char - second_string_char) < 0;
}
