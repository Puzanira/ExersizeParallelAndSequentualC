#include <stdio.h>
#include <assert.h>

#include "ParallelRealisation.h"
#include "SequentualRealisation.h"

void test()
{
    {
        printf("Test 1 medium file, workers = 3\n");
        long int resultParallel = process_parallel(FALSE, "TestFiles/test3.txt", 3);
        //printf("Result Parallel = %ld", resultParallel);
        long int resultSequentual = process_sequentual("TestFiles/test3.txt");
        //printf("Result Sequentual = %ld", resultSequentual);
        assert(resultParallel == resultSequentual);
    }
    {
        printf("Test 2 medium file, workers = 100\n");
        long int resultParallel = process_parallel(FALSE, "TestFiles/test3.txt", 100);
        //printf("Result Parallel = %ld", resultParallel);
        long int resultSequentual = process_sequentual("TestFiles/test3.txt");
        //printf("Result Sequentual = %ld", resultSequentual);
        assert(resultParallel == resultSequentual);
    }
    printf("passed");
}

int main(int argc, char const *argv[])
{
    test();
    return 0;
}
