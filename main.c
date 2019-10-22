#include <stdio.h>

#include "ParallelRealisation.h"
#include "SequentualRealisation.h"

/*  Передаются параметры: 
    1: 0, если debug == FALSE, иначе 1
    2: имя файла для работы с ним
    3: количество процессов-детей
*/
int main(int argc, char const *argv[])
{
    if (argc != 4)
    {
        return -1;
    }

    int debug = argv[1];
    char* fileName = argv[2];
    int workers = argv[3];

    long int resultParallel = process_parallel(debug, fileName, 3);
    printf("Result Parallel = %ld", resultParallel);

    long int resultSequentual = process_sequentual(fileName);
    printf("Result Sequentual = %ld", resultSequentual);
    return 0;
}
