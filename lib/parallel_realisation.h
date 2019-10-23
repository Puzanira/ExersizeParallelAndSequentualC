#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "file_helper.h"

#define FALSE               0
#define TRUE                !(FALSE)

//required as a paramater for sending ints down a pipe
#define SIZE_OF_INT         sizeof(int)
#define SIZE_OF_LONG_INT    sizeof(long int)

void        child_processing        (int*           child_to_parent, 
                                     int*           parent_to_child, 
                                     int            id, 
                                     long int*      array_of_shared_offsets, 
                                     const char*    filename, 
                                     int            debug);

void        break_file_into_chunks  (int            number_of_children, 
                                     const char*    filename,
                                     long int*      array_of_shared_offsets);

long int    process_parallel        (int            debug, 
                                     const char*    filename, 
                                     const int      number_of_children);
