#include "SequentualRealisation.h"

long int process_sequentual(const char* fileName)
{
    int result = get_next_offset(fileName, 0, 1);
    long int maxWord = get_max_word(fileName, 0, result);
}