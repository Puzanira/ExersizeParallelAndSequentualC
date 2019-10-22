#include "ParallelRealisation.h"

long int process_parallel(int debug, const char* fileName, const int NUMBER_OF_CHILDREN)
{
    // Pipe child_to_parent используется для возврата значения максимума,
    // найденного ребенком. 
    int child_to_parent[2];
    // Т.к родитель должен выполнить свою работу (разбить файл на куски),
    // перед тем, как дети начнут свою, parent_to_child используется для 
    // передачи команды старта от родителя к детям
    int parent_to_child[2];
    pipe(parent_to_child);
    pipe(child_to_parent);

    // Массив с pid детей, для удаления зомби после работы
    pid_t shut_down[NUMBER_OF_CHILDREN];

    int childrenWorking = NUMBER_OF_CHILDREN;
    int pid;

    // Массив, куда кладуться границы кусков файла, нужные детям для поиска
    long int *offsetsForChildProcessing = mmap(NULL, (NUMBER_OF_CHILDREN + 1) * sizeof(long int),
                  PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED,
                  -1, 0);

    long int maxWordLength = 0;
    long int currentChildWordLength = 0;
    
    for (int i = 0; i < NUMBER_OF_CHILDREN; i++)
    {
        pid = fork();
        if (pid < 0) 
        {
            fprintf( stderr, "CHILDREN CREATION %d FAILED\n", i);
            return -1;
        }

        if (pid == 0) // child
        {
            child_processing(child_to_parent, parent_to_child, i, 
                    offsetsForChildProcessing, fileName, debug);
            break;
        }
        else //parent
        {
            break_file_into_chunks(NUMBER_OF_CHILDREN, fileName,
                     offsetsForChildProcessing);

            // сохраняем pid в массив для отслеживания зомби
            shut_down[i] = pid;
        }
          
    } //конец цикла создания детей

    if (pid > 0) // parent
    {
        int loop = TRUE;
        while (loop) 
        {
        
            // Родитель подает команду ребенку, что пора работать
            write(parent_to_child[1], &childrenWorking, SIZE_OF_INT);
            // Родитель дожидается ответа ребенка, что он закончил
            read(child_to_parent[0], &currentChildWordLength, SIZE_OF_LONG_INT);
            childrenWorking--;

            maxWordLength = currentChildWordLength > maxWordLength ?
                     currentChildWordLength : maxWordLength;

            if (debug)
                printf("Current max = %ld\n", maxWordLength);

            if (childrenWorking == 0) 
            {
                loop = FALSE;
            }
        }

        for (int i = 0; i < NUMBER_OF_CHILDREN; i++) 
        {
            waitpid(shut_down[i], NULL, 0);
        }
    }

    if (pid > 0)
    {
        if (debug)
        {
            printf("-----------------------------\n");
            printf("There are no ZOMBIES!\n");
            printf("\nMaximum length found: %ld\n", maxWordLength);
        }
    }
    return maxWordLength;
}


void break_file_into_chunks(int NUMBER_OF_CHILDREN, const char* fileName, 
            long int* offsetsForChildProcessing)
{
    // Разбиваем файл на куски и записываем границы в offsetsForChildProcessing
    long int startOffset = 0;
    long int finishOffset = 0;
    offsetsForChildProcessing[0] = startOffset;
    for (int i = 0; i < NUMBER_OF_CHILDREN; i++)
    {
        finishOffset = get_next_offset(fileName, startOffset, NUMBER_OF_CHILDREN - i);
        offsetsForChildProcessing[i+1] = finishOffset;
        startOffset = finishOffset;
    } 
}

void child_processing(int* child_to_parent, int* parent_to_child, int id, 
        long int * sharedOffsetsArray, const char* fileName, int debug)
{
    // Ждет команду родителя для начала работы
    int commandToStart = 0;
    read(parent_to_child[0], &commandToStart, SIZE_OF_INT);

    long int startOffset = sharedOffsetsArray[id];
    long int finishOffset = sharedOffsetsArray[id+1];
    long int maxWord = get_max_word(fileName, startOffset, finishOffset);

    if (debug)
        printf("\nI am child %d, searching in chunk: start=%ld, finish=%ld\n", id, startOffset, finishOffset);
    write(child_to_parent[1], &maxWord, SIZE_OF_LONG_INT);
}
