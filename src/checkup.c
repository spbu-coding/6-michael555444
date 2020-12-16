#include "checkup.h"

#define error_print(...) fprintf(stderr, __VA_ARGS__)

int error(char *error) {
    error_print("%s\n", error);
    return UNSUCCESS;
}

bool check_count_of_parameters(parameters_count_t parameters_count) {
    if (parameters_count == PARAMS_COUNT) {
        return true;
    }
    return false;
}

bool check_existence_input_file(fname_t file_name) {
    FILE *input_file = fopen(file_name, "r");
    if (input_file == NULL) {
        return false;
    }
    fclose(input_file);
    return true;
}

bool check_count_of_strings(fname_t file_name, count_of_strings_t count_of_strings) {
    FILE *input_file = fopen(file_name, "r");
    array_size_t count_of_input_strings = 0;
    char *input_string = malloc(sizeof(char) * STRING_SIZE);
    while (!feof(input_file)) {
        if (fgets(input_string, STRING_SIZE, input_file) != NULL) {
            count_of_input_strings++;
        }
    }
    free(input_string);

    if (count_of_input_strings < count_of_strings) {
        fclose(input_file);
        return false;
    }
    fclose(input_file);
    return true;
}

bool is_integer(string_t string) {
    for (array_size_t i = 0; i < strlen(string); i++)
        if (string[i] < '0' || string[i] > '9') {
            return false;
        }
    return true;
}

int is_string_in_array(string_t string, const_string_array_t string_array, array_size_t array_size) {
    for (array_size_t i = 0; i < array_size; i++) {
        if (strcmp(string, string_array[i]) == 0) {
            return i;
        }
    }
    return UNSUCCESSFUL_EXIT_CODE;
}

int check_parameters(parameters_count_t parameters_count, parameters_t parameters) {
    if (!check_count_of_parameters(parameters_count)) {
        return error("Input correct count of parameters.");
    }

    if (!is_integer(parameters[ARG_COUNT_OF_STRINGS])) {
        return error("Input correct data type of strings count.");
    }

    if (!check_existence_input_file(parameters[ARG_INPUT_FILE_NAME])) {
        return error("Input correct input file name.");
    }

    int count_of_strings = string_to_int(parameters[ARG_COUNT_OF_STRINGS]);
    if (!check_count_of_strings(parameters[ARG_INPUT_FILE_NAME], count_of_strings)) {
        return error("Input correct count of strings.");
    }

    if (is_string_in_array(parameters[ARG_SORT_NAME], SORT_NAMES, SORTS_COUNT) == UNSUCCESSFUL_EXIT_CODE) {
        return error("Input correct sorting name.");
    }

    if (is_string_in_array(parameters[ARG_COMPARATOR_NAME], COMP_NAMES, COMPS_COUNT) == UNSUCCESSFUL_EXIT_CODE) {
        return error("Input correct comparator name.");
    }

    return SUCCESSFUL_EXIT_CODE;
}
