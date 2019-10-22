#include "FileHelper.h"

int check_file_availability(const char* filename)
{
    FILE *file = fopen(filename, "rb");
    if (file  == NULL)
        return 0;

    fclose(file);
    return 1;
}


long int get_next_offset(const char* filename, long int startOffset, int numberOfChunks)
{
    FILE *file = fopen(filename, "rb");
    if (file == NULL) 
        return -1;

    // SEEK_END - не определен в стандартах
    fseek(file, 0L, SEEK_END); // переход к концу файла
    long int fileSize = ftell(file);
    long int fileRemainingSize = fileSize - startOffset;

    if (fileRemainingSize <= 0 )
    {
        fclose(file);
        return 0;
    }
    
    // Если оставшееся количество символов слишком мало, чтобы его разделить
    // на нужное количество частей, то берем кусок до конца файла
    long int finalOffset = 0;
    if (numberOfChunks <= 1 || (fileRemainingSize / numberOfChunks) == 0)
    {
        fclose(file);
        return fileSize;
    }
    else
    {
        finalOffset = fileRemainingSize / numberOfChunks + startOffset;
    }
         
    fseek(file, finalOffset, SEEK_SET);

    //Беспрерывное слово состоить только из букв или цифр
    char c;
    while (fread(&c, sizeof(char), 1, file) && finalOffset != fileSize
        && isalnum(c) ) 
    {
        finalOffset++;
    }

    fclose(file);
    // Переходим на следующий после буквенного символа символ
    return ++finalOffset;
}


long int get_max_word(const char* filename, long int startOffset, long int finishOffset)
{
    FILE *file = fopen(filename, "rb");
    if (file == NULL) 
        return -1;

    fseek(file, startOffset, SEEK_SET);

    long int chunkSize = finishOffset - startOffset;
    char c;
    long int maxWordSize = 0;
    long int currentWordSize = 0;
    while (chunkSize > 0 && fread(&c, sizeof(char), 1, file))
    {
        //printf("%c", c);
        chunkSize--;

        if (isalnum(c))
        {
            currentWordSize++;
        }
        else
        {
            maxWordSize = currentWordSize > maxWordSize ? 
                    currentWordSize : maxWordSize;
            currentWordSize = 0;
        }
    }

    fclose(file);
    return maxWordSize;
}