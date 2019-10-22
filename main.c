#include <stdio.h>

#include "ParallelRealisation.h"
#include "SequentualRealisation.h"

int main(int argc, char const *argv[])
{
    long int resultParallel = process_parallel(FALSE, "TestFiles/test3.txt", 3);
    printf("Result Parallel = %ld", resultParallel);

    long int resultSequentual = process_sequentual("TestFiles/test3.txt");
    printf("Result Sequentual = %ld", resultSequentual);
    return 0;
}
