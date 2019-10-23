#include "parallel_realisation.h"

long int 
process_parallel (int           debug, 
                  const char*   filename, 
                  const int     number_of_children)
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
    pid_t shut_down[number_of_children];

    int children_still_working = number_of_children;
    int pid;

    // Массив, куда кладуться границы кусков файла, нужные детям для поиска
    long int* array_of_shared_offsets = mmap(NULL, 
                                             (number_of_children + 1) * sizeof(long int),
                                             PROT_READ | PROT_WRITE, 
                                             MAP_ANONYMOUS | MAP_SHARED,
                                             -1, 0);

    long int max_word_length = 0;
    long int current_word_length = 0;
    
    for (int i = 0; i < number_of_children; i++)
    {
        pid = fork();
        if (pid < 0) 
        {
            fprintf( stderr, "CHILDREN CREATION %d FAILED\n", i);
            return -1;
        }

        if (pid == 0) // child
        {
            child_processing (child_to_parent, 
                              parent_to_child, 
                              i, 
                              array_of_shared_offsets, 
                              filename, 
                              debug);
            break;
        }
        else //parent
        {
            break_file_into_chunks (number_of_children, 
                                    filename,
                                    array_of_shared_offsets);

            // сохраняем pid в массив для отслеживания зомби
            shut_down[i] = pid;
        }
          
    } //конец цикла создания детей

    if (pid > 0) { // parent
        int loop = TRUE;

        while (loop) {
        
            // Родитель подает команду ребенку, что пора работать
            write(parent_to_child[1], &children_still_working, SIZE_OF_INT);
            // Родитель дожидается ответа ребенка, что он закончил
            read(child_to_parent[0], &current_word_length, SIZE_OF_LONG_INT);
            children_still_working--;

            max_word_length = current_word_length > max_word_length ?
                     current_word_length : max_word_length;

            if (debug)
                printf("Current max = %ld\n", max_word_length);

            if (children_still_working == 0) 
                loop = FALSE;
        }

        for (int i = 0; i < number_of_children; i++) 
            waitpid(shut_down[i], NULL, 0);
    }

    if (pid > 0) {
        if (debug) {
            printf("-----------------------------\n");
            printf("There are no ZOMBIES!\n");
            printf("\nMaximum length found: %ld\n", max_word_length);
        }
    }
    return max_word_length;
}


void 
break_file_into_chunks (int         number_of_children, 
                        const char* filename, 
                        long int*   array_of_shared_offsets)
{
    // Разбиваем файл на куски и записываем границы в array_of_shared_offsets
    long int start_offset = 0;
    long int finish_offset = 0;
    array_of_shared_offsets[0] = start_offset;
    for (int i = 0; i < number_of_children; i++)
    {
        finish_offset = get_next_offset(filename, 
                                        start_offset, 
                                        number_of_children - i);
        array_of_shared_offsets[i+1] = finish_offset;
        start_offset = finish_offset;
    } 
}

void 
child_processing (int*          child_to_parent, 
                  int*          parent_to_child, 
                  int           id, 
                  long int*     array_of_shared_offsets, 
                  const char*   filename, 
                  int           debug)
{
    // Ждет команду родителя для начала работы
    int command_to_start = 0;
    read(parent_to_child[0], &command_to_start, SIZE_OF_INT);

    long int start_offset = array_of_shared_offsets[id];
    long int finish_offset = array_of_shared_offsets[id+1];
    long int max_word = get_max_word (filename, 
                                     start_offset, 
                                     finish_offset);

    if (debug)
        printf("\nI am child %d, searching in chunk: start=%ld, finish=%ld\n", id, start_offset, finish_offset);
    
    write(child_to_parent[1], &max_word, SIZE_OF_LONG_INT);
}
