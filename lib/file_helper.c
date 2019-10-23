#include "file_helper.h"

int 
check_file_availability (const char* filename)
{
    FILE *file = fopen(filename, "rb");
    if (file  == NULL)
        return 0;

    fclose(file);
    return 1;
}


long int 
get_next_offset (const char*   filename, 
                 long int      start_offset, 
                 int           number_of_chunks)
{
    FILE *file = fopen(filename, "rb");
    if (file == NULL) 
        return -1;

    // SEEK_END - не определен в стандартах
    fseek(file, 0L, SEEK_END); // переход к концу файла
    long int file_size = ftell(file);
    long int file_remaining_size = file_size - start_offset;

    if (file_remaining_size <= 0 ) {
        fclose(file);
        return 0;
    }
    
    // Если оставшееся количество символов слишком мало, чтобы его разделить
    // на нужное количество частей, то берем кусок до конца файла
    long int finish_offset = 0;
    if (number_of_chunks <= 1 || 
        (file_remaining_size / number_of_chunks) == 0) {
        fclose(file);
        return file_size;
    } else {
        finish_offset = file_remaining_size / 
                      number_of_chunks + start_offset;
    }
         
    fseek(file, finish_offset, SEEK_SET);

    //Беспрерывное слово состоить только из букв или цифр
    char c;
    while (fread(&c, sizeof(char), 1, file) && 
           finish_offset != file_size && isalnum(c)) {
        finish_offset++;
    }

    fclose(file);
    // Переходим на следующий после буквенного символа символ
    return ++finish_offset;
}


long int 
get_max_word (const char*   filename, 
              long int      start_offset, 
              long int      finish_offset)
{
    FILE *file = fopen(filename, "rb");
    if (file == NULL) 
        return -1;

    fseek(file, start_offset, SEEK_SET);

    long int chunk_size = finish_offset - start_offset;
    char c;
    long int max_word_size = 0;
    long int current_word_size = 0;
    while (chunk_size > 0 && 
           fread(&c, sizeof(char), 1, file)) {
        //printf("%c", c);
        chunk_size--;

        if (isalnum(c)) {
            current_word_size++;
        } else {
            max_word_size = current_word_size > max_word_size ? 
                    current_word_size : max_word_size;
            current_word_size = 0;
        }
    }

    fclose(file);
    return max_word_size;
}