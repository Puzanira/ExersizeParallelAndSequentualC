#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "FileHelper.h"

#define FALSE               0
#define TRUE                !(FALSE)

//required as a paramater for sending ints down a pipe
#define SIZE_OF_INT         sizeof(int)
#define SIZE_OF_LONG_INT    sizeof(long int)

void child_processing(int* child_to_parent, int* parent_to_child, int id, 
        long int * sharedOffsetsArray, const char* fileName, int debug);

void break_file_into_chunks(int NUMBER_OF_CHILDREN, const char* fileName,
    long int* offsetsForChildProcessing);

long int process_parallel(int debug, const char* fileName, const int NUMBER_OF_CHILDREN);
