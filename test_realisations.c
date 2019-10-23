#include <stdio.h>
#include <assert.h>

#include "parallel_realisation.h"
#include "sequentual_realisation.h"

void test(const char* fileName)
{
    {
        printf("Test 1 medium file, workers = 3\n");
        long int resultParallel = process_parallel(FALSE, fileName, 3);
	if (resultParallel) {
        	//printf("\nResult Parallel = %ld\n", resultParallel);
        	long int resultSequentual = process_sequentual(fileName);
        	//printf("\nResult Sequentual = %ld\n", resultSequentual);
        	assert(resultParallel == resultSequentual);

		{
        		printf("Test 2 medium file, workers = 100\n");
        		long int resultParallel = process_parallel(FALSE, fileName, 100);
        		if (resultParallel) {
        			//printf("\nResult Parallel = %ld\n", resultParallel);
        			long int resultSequentual = process_sequentual(fileName);
        			//printf("\nResult Sequentual = %ld\n", resultSequentual);
        			assert(resultParallel == resultSequentual);
			}
    		}
	}
    }
}

int main(int argc, const char *argv[])
{
    if (argc != 2)
        return -1;
    
    test(argv[1]);
    return 0;
}
