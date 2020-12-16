#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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

void quick(strings_array_t strings_array, array_size_t array_size, comparator_func_t comparator_func) {
    int left = 0;
    int right = array_size - 1;
    char *mid, *temp;
    mid = strings_array[array_size / 2];
    do {
        while (comparator_func(strings_array[left], mid) < 0) left++;
        while (comparator_func(strings_array[right], mid) > 0) right--;
        if (left <= right) {
            temp = strings_array[left];
            strings_array[left] = strings_array[right];
            strings_array[right] = temp;
            left++;
            right--;
        }
    } while (left <= right);
    if (right > 0)
        quick(strings_array, right + 1, comparator_func);
    if (left < (int) array_size)
        quick(&strings_array[left], array_size - left, comparator_func);
}

void radix(strings_array_t array, array_size_t size, comparator_func_t compare_func) {
    compare_func(array[0], array[0]);
    size_t length[size], max_length = 0;
    for (unsigned int i = 0; i < size; i++) {
        length[i] = strlen(array[i]) - 1;
        if (length[i] > max_length) {
            max_length = length[i];
        }
    }
    for (int i = (int) max_length - 1; i >= 0; i--) {
        unsigned int char_counter[128] = {
                0
        };
        for (unsigned int j = 0; j < size; j++) {
            if ((int) length[j] - 1 >= i) {
                char_counter[(unsigned int) array[j][i]]++;
            } else {
                char_counter[0]++;
            }
        }
        for (unsigned int j = 1; j < 128; j++) {
            char_counter[j] += char_counter[j - 1];
        }
        char *buffer[size];
        size_t buffer_length[size];
        for (int j = (int) size - 1; j >= 0; j--) {
            if ((int) length[j] - 1 >= i) {
                buffer[(char_counter[(unsigned int) array[j][i]]) - 1] = array[j];
                buffer_length[(char_counter[(unsigned int) array[j][i]]--) - 1] = length[j];
            } else {
                buffer[(char_counter[0]) - 1] = array[j];
                buffer_length[(char_counter[0]--) - 1] = length[j];
            }
        }
        memcpy(array, buffer, size * sizeof(char *));
        memcpy(length, buffer_length, size * sizeof(size_t));
    }
}
