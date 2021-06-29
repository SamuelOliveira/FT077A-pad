#include <stdio.h>

void erroGravacao()
{
    printf("Erro ao tentar gravar os dados!\n");
}

int showTamanho(char *name, FILE *file)
{
    long tamanho;

    fseek(file, 0, SEEK_END);
    tamanho = ftell(file);

    printf(name,tamanho);

    return tamanho;
}

int contaLinhas(FILE *file)
{
    int ch=0;
    int lines=1;

    while(!feof(file))
    {
        ch = fgetc(file);
        if(ch == '\n')
        {
            lines++;
        }
    }

    fseek(file, 0, SEEK_SET);

    printf("Total de linhas %d\n",lines);    
}

int main(int argc, char* argv[])
{
    char *fileName1;  /* should check that argc > 1 */
    char const* const fileName = argv[1];   /* should check that argc > 1 */
    char const* const fileName2 = argv[2];  /* should check that argc > 1 */
    char const* const fileName3 = argv[3];  /* should check that argc > 1 */
 
    fileName1 = "file1.txt";

    FILE* file  = fopen(fileName, "r");     /* should check the result */
    FILE* file1 = fopen(fileName1, "w+");   /* should check the result */
    FILE* file2 = fopen(fileName2, "w+");   /* should check the result */
    FILE* file3 = fopen(fileName3, "w");    /* should check the result */
    
    char line[256];
    int l = 0;
    
    printf("\n");

    contaLinhas(file);

    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
        l++;
        if (l <= 2) {
            if (fputs(line, file1) == EOF)
                erroGravacao();
        };
        if (l >= 3 && l <= 5) {
            if (fputs(line, file2) == EOF)
                erroGravacao();
        };
    }

    fseek(file1, 0, SEEK_SET);
    fseek(file2, 0, SEEK_SET);

    while (fgets(line, sizeof(line), file1)) {
        if (fputs(line, file3) == EOF)
            erroGravacao();
    }

    if (fputs("-----------------------\n", file3) == EOF)
        erroGravacao();

    while (fgets(line, sizeof(line), file2)) {
        if (fputs(line, file3) == EOF)
            erroGravacao();
    }

    printf("\n\n");

    showTamanho("Tamanho base %ld\n", file);
    showTamanho("Tamanho File1 %ld\n", file1);
    showTamanho("Tamanho File2 %ld\n", file2);
    showTamanho("Tamanho File3 %ld\n", file3);
    
    printf("\n");

    fclose(file);
    fclose(file1);
    fclose(file2);
    fclose(file3);

    remove(fileName1);
    remove(fileName2);

    return 0;
}
