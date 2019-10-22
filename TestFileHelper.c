#include <stdio.h>
#include <assert.h>

#include "lib/FileHelper.h"

void test(const char* fileTest1, const char* fileTest2, const char* fileTest3)
{
    printf("SMALL FILE TESTS\n\n");
    {
        printf("Test Case 1: no file\n");
        int result = check_file_availability("text.txt");
        assert(result == 0);
    }
    {
        printf("Test Case 2: is file\n");
        int result = check_file_availability(fileTest1);
        //printf("%d", result2);
        assert(result == 1);
    }
//     {
//         printf("Test Case 3: small file 1 chunk\n");
//         int result = get_next_offset(fileTest1, 0, 1);
//         //printf("%d", result);
//         assert(result == 8);
//     }
//     {
//         printf("Test Case 4: small file, start=2, 1 chunk\n");
//         int result = get_next_offset(fileTest1, 2, 1);
//         //printf("%d\n", result);
//         assert(result == 8);
//     }
//     {
//         printf("Test Case 5: small file, start=fileSize, 1 chunk\n");
//         int result = get_next_offset(fileTest1, 8, 1);
//         //printf("%d\n", result);
//         assert(result == 0);
//     }
//     {
//         printf("Test Case 5.2: small file, start>fileSize, 1 chunk\n");
//         int result = get_next_offset(fileTest1, 10, 1);
//         //printf("%d\n", result);
//         assert(result == 0);
//     }
//     {
//         printf("Test Case 6: small file, start=0, 2 chunks\n");
//         int result = get_next_offset(fileTest1, 0, 2);
//         //printf("%d\n", result);
//         assert(result == 8);
//     }
//     {
//         printf("Test Case 6.2: small file, start=7, 1 chunks\n");
//         int result = get_next_offset(fileTest1, 7, 1);
//         //printf("%d\n", result);
//         assert(result == 8);
//     }
//     {
//         printf("Test Case 6.3: small file, start=7, 2 chunks\n");
//         int result = get_next_offset(fileTest1, 7, 2);
//         //printf("%d\n", result);
//         assert(result == 8);
//     }
//     {
//         printf("Test Case 7: small file, start=0, 3 chunks\n");
//         int result = get_next_offset(fileTest1, 0, 3);
//         //printf("%d\n", result);
//         assert(result == 3);
//     }
//     {
//         printf("Test Case 7.2: small file, start=3, 2 chunks\n");
//         int result = get_next_offset(fileTest1, 0, 2);
//         //printf("%d\n", result);
//         assert(result == 8);
//     }
//     {
//         printf("Test Case 8: small file, start=0, 4 chunks\n");
//         int result = get_next_offset(fileTest1, 0, 4);
//         //printf("%d\n", result);
//         assert(result == 3);
//     }
//     {
//         printf("Test Case 9: small file, start=3, 3 chunks\n");
//         int result = get_next_offset(fileTest1, 3, 3);
//         //printf("%d\n", result);
//         assert(result == 8);
//     }

//     printf("\nMEDIUM FILE TESTS\n\n");

//     /// TECTЫ НА ФАЙЛЕ СРЕДНЕГО РАЗМЕРА
//     /*-------------------------------------------------------*/

//     {
//         printf("Test Case 10: medium file 1 chunk\n");
//         int result = get_next_offset(fileTest2, 0, 1);
//         //printf("%d\n", result);
//         assert(result == 1156);
//     }
//     {
//         printf("Test Case 11: medium file, start=0, 2 chunks\n");
//         int result = get_next_offset(fileTest2, 0, 2);
//         //printf("%d\n", result);
//         assert(result == 579);
//     }
//     {
//         printf("Test Case 11.2: medium file, start=579, 1 chunk\n");
//         int result = get_next_offset(fileTest2, 579, 1);
//         //printf("%d\n", result);
//         assert(result == 1156);
//     }
//     {
//         printf("Test Case 12: medium file, start=0, 5 chunks\n");
//         int chunks = 5;
//         long int currentStartOffset = 0;
//         for (int i = chunks; i > 0; i--)
//         {
//             //printf("%ld  ", currentStartOffset);
//             currentStartOffset = get_next_offset(fileTest2, currentStartOffset, i);
//             //printf("%ld\n", currentStartOffset);
//         }
//         //printf("%ld\n", currentStartOffset);
//         assert(currentStartOffset == 1156);
//     }
//     {
//         printf("Test Case 13: medium file, start=0, 10 chunks\n");
//         int chunks = 10;
//         long int currentStartOffset = 0;
//         for (int i = chunks; i > 0; i--)
//         {
//             printf("%ld  ", currentStartOffset);
//             currentStartOffset = get_next_offset(fileTest2, currentStartOffset, i);
//             printf("%ld\n", currentStartOffset);
//         }
//         //printf("%d\n", result);
//         //assert(currentStartOffset == 1156);
//     }

//     printf("\nMAX WORD FILE TESTS\n\n");

//     {
//         printf("Test Case 14: small file 1 chunk\n");
//         int result = get_next_offset(fileTest1, 0, 1);
//         long int maxWord = get_max_word(fileTest1, 0, result);
//         printf("Max = %ld\n\n", maxWord);
//         assert(maxWord == 4);
//     }
//     {
//         printf("Test Case 15: small file, start=2, 1 chunk\n");
//         int result = get_next_offset(fileTest1, 2, 1);
//         long int maxWord = get_max_word(fileTest1, 0, result);
//         printf("Max = %ld\n\n", maxWord);
//         //printf("%d\n", result);
//         assert(maxWord == 4);
//     }
//     {
//         printf("Test Case 16: small file, start=0, 3 chunks\n");
//         int result = get_next_offset(fileTest1, 0, 3);
//         long int maxWord = get_max_word(fileTest1, 0, result);
//         //printf("%d\n", result);
//         printf("Max = %ld\n\n", maxWord);
//         assert(maxWord == 2);
//     }
//     {
//         printf("Test Case 17: medium file start=5, finish=12\n");
//         long int maxWord = get_max_word(fileTest3, 5, 12);
//         printf("Max = %ld\n\n", maxWord);
//         //assert(result == 1156);
//     }
//     {
//         printf("Test Case 18: medium file start=34, finish=130\n");
//         long int maxWord = get_max_word(fileTest3, 34, 130);
//         printf("Max = %ld\n\n", maxWord);
//         //assert(result == 1156);
//     }
//     {
//         printf("Test Case 19: medium file start=0 chunks = 1\n");
//         int result = get_next_offset(fileTest3, 0, 1);
//         long int maxWord = get_max_word(fileTest3, 0, result);
//         printf("Max = %ld\n\n", maxWord);
//         //assert(result == 1156);
//     }
}

int main(int argc, char const *argv[])
{
    test(argv[1], argv[2], argv[3]);
    return 0;
}
