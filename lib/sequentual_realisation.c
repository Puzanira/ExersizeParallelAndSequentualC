#include "sequentual_realisation.h"

long int 
process_sequentual (const char* filename)
{
    int result = get_next_offset(filename, 0, 1);
    long int maxWord = get_max_word(filename, 0, result);
}