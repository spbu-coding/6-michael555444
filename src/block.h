#include <stdio.h>
#include <stdlib.h>

#include "checkup.h"
#include "sortings.h"

typedef int sort_num_t, comparator_num_t;

void input_block(fname_t, array_size_t, strings_array_t);

void output_block(fname_t, array_size_t, strings_array_t);

void sort_block(strings_array_t, array_size_t, comparator_num_t, sort_num_t);
