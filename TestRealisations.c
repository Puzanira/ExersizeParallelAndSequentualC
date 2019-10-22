#include <stdio.h>
#include <assert.h>

#include "ParallelRealisation.h"
#include "SequentualRealisation.h"

void test(const char* fileName)
{
    {
        printf("Test 1 medium file, workers = 3\n");
        long int resultParallel = process_parallel(FALSE, fileName, 3);
        //printf("Result Parallel = %ld", resultParallel);
        long int resultSequentual = process_sequentual("TestFiles/test3.txt");
        //printf("Result Sequentual = %ld", resultSequentual);
        assert(resultParallel == resultSequentual);
    }
    {
        printf("Test 2 medium file, workers = 100\n");
        long int resultParallel = process_parallel(FALSE, fileName, 100);
        //printf("Result Parallel = %ld", resultParallel);
        long int resultSequentual = process_sequentual(fileName);
        //printf("Result Sequentual = %ld", resultSequentual);
        assert(resultParallel == resultSequentual);
    }
    printf("passed");
}

int main(int argc, char const *argv[])
{
    if (argc != 2)
        return -1;
    
    test(argv[1]);
    return 0;
}
