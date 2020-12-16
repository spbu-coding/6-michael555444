#include <stdio.h>

#include "checkup.h"
#include "array.h"


int main(int argc, char *argv[]) {
    int exit_code = check_parameters(argc - 1, argv);
    if (exit_code == UNSUCCESSFUL_EXIT_CODE) {
        return exit_code;
    }
    int count_of_strings = string_to_int(argv[ARG_COUNT_OF_STRINGS]);
    char **strings_array = malloc(sizeof(char *) * count_of_strings);
    for (int i = 0; i < count_of_strings; i++) {
        strings_array[i] = malloc(sizeof(char) * STRING_SIZE);
    }
    input_array(argv[ARG_INPUT_FILE_NAME], count_of_strings, strings_array);
    int comparator_num = is_string_in_array(argv[ARG_COMPARATOR_NAME], COMP_NAMES, COMPS_COUNT);
    int sort_num = is_string_in_array(argv[ARG_SORT_NAME], SORT_NAMES, SORTS_COUNT);
    sort_array(strings_array, count_of_strings, comparator_num, sort_num);
    output_array(argv[ARG_OUTPUT_FILE_NAME], count_of_strings, strings_array);
    for (int i = 0; i < count_of_strings; i++) {
        free(strings_array[i]);
    }
    free(strings_array);
    return exit_code;
}
