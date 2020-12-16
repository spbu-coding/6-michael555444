#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "sortings.h"

#define string_to_int(string) strtol(string, NULL, 10)
#define size_of(array) sizeof(array) / sizeof(char*)

typedef size_t count_of_strings_t;
typedef int parameters_count_t;
typedef char *string_t, *fname_t;
typedef const char **const_string_array_t;
typedef char **parameters_t;

static const int SUCCESS = 0;
static const int UNSUCCESS = -1;
static const int COUNT_OF_STRINGS = 1;
static const int INPUT_FILE_NAME = 2;
static const int OUTPUT_FILE_NAME = 3;
static const int SORT_NAME = 4;
static const int COMPARATOR_NAME = 5;
static const int PARAMS_COUNT = 5;
static const int SORTINGS_COUNT = size_of(SORTINGS);
static const int COMPARERS_COUNT = size_of(COMPARERS);
static const char *SORTINGS[] = {"bubble", "insertion", "merge", "quick", "radix"};
static const char *COMPARERS[] = {"asc", "des"};

int is_string_in_array(string_t, const_string_array_t, array_size_t);

int check_parameters(parameters_count_t, parameters_t);