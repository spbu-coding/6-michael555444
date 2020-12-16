#include "block.h"

void input_block(fname_t file_name, array_size_t array_size, strings_array_t strings_array) {
    FILE *input_file = fopen(file_name, "r");
    for (array_size_t i = 0; i < array_size; i++) {
        fgets(strings_array[i], STRING_SIZE, input_file);
    }
    fclose(input_file);
}

void output_block(fname_t file_name, array_size_t array_size, strings_array_t strings_array) {
    FILE *output_file = fopen(file_name, "w");
    for (array_size_t i = 0; i < array_size; i++) {
        fputs(strings_array[i], output_file);
    }
    if (array_size == 0) {
        fputs(END_OF_FILE, output_file);
    }
    fclose(output_file);
}

void sorts(strings_array_t strings_array, array_size_t array_size, comparator_func_t comparator, sort_num_t sort_num) {
    switch (sort_num) {
        case 0:
            bubble(strings_array, array_size, comparator);
            break;
        case 1:
            insertion(strings_array, array_size, comparator);
            break;
        case 2:
            merge(strings_array, array_size, comparator);
            break;
        case 3:
            quick(strings_array, array_size, comparator);
            break;
        case 4:
            radix(strings_array, array_size, comparator);
            break;
        default:
            break;
    }
}

void sort_block(strings_array_t strings_array, array_size_t array_size, comparator_num_t comparator_num,
                sort_num_t sort_num) {
    switch (comparator_num) {
        case 0:
            sorts(strings_array, array_size, comparator_asc, sort_num);
            break;
        case 1:
            sorts(strings_array, array_size, comparator_des, sort_num);
            break;
        default:
            break;
    }
}
