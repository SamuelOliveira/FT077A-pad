#include <stdio.h>

int main(int argc, char* argv[])
{
    char const* const fileName = argv[1]; /* should check that argc > 1 */
    char const* const fileName2 = argv[2]; /* should check that argc > 1 */
    char const* const fileName3 = argv[3]; /* should check that argc > 1 */
 
    FILE* file = fopen(fileName, "r"); /* should check the result */
    FILE* file2 = fopen(fileName2, "w+"); /* should check the result */
    FILE* file3 = fopen(fileName3, "w"); /* should check the result */
    
    char line[256];
    int l = 0;

    while (fgets(line, sizeof(line), file)) {
        /* note that fgets don't strip the terminating \n, checking its
           presence would allow to handle lines longer that sizeof(line) */
        printf("%s", line);
        l++;
        if (l <= 2) {
            if (fputs(line, file2) == EOF)
                printf("Erro ao tentar gravar os dados! \n");
        }; 
        if (fputs(line, file3) == EOF)
            printf("Erro ao tentar gravar os dados! \n");
    }

    if (fputs("\n###########\n", file3) == EOF)
        printf("Erro ao tentar gravar os dados! \n");

    fseek( file2, 0, SEEK_SET );

    while (fgets(line, sizeof(line), file2)) {
        if (fputs(line, file3) == EOF)
            printf("Erro ao tentar gravar os dados! \n");
    }

    fclose(file);
    fclose(file2);
    fclose(file3);

    return 0;
}
