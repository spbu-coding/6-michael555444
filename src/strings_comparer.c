#include <stdio.h>

#include "checkup.h"
#include "block.h"


int main(int argc, char *argv[]) {
    int exit_code = checks(argc - 1, argv);
    if (exit_code == UNSUCCESS) {
        return exit_code;
    }
    int count_of_strings = string_to_int(argv[COUNT_OF_STRINGS]);
    char **strings_array = malloc(sizeof(char *) * count_of_strings);
    for (int i = 0; i < count_of_strings; i++) {
        strings_array[i] = malloc(sizeof(char) * STRING_SIZE);
    }
    input_block(argv[INPUT_FNAME], count_of_strings, strings_array);
    int comparator_num = is_string_in_array(argv[COMPARATOR_NAME], COMPARERS, COMPARERS_COUNT);
    int sort_num = is_string_in_array(argv[SORT_NAME], SORTINGS, SORTINGS_COUNT);
    sort_block(strings_array, count_of_strings, comparator_num, sort_num);
    output_block(argv[OUTPUT_FNAME], count_of_strings, strings_array);
    for (int i = 0; i < count_of_strings; i++) {
        free(strings_array[i]);
    }
    free(strings_array);
    return exit_code;
}
