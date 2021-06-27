#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_FILE_NAME 100

int main() {
    srand(time(NULL));
    FILE *fp;
    int count = 1;  // Line counter (result)
    unsigned int line_count = 0;
    char filename[MAX_FILE_NAME];
    char c;  // To store a character read from file
  
    // Get file name from user. The file should be
    // either in current folder or complete path should be provided

    printf("Enter file name: ");
    scanf("%s", filename);
  
    // Open the file
    fp = fopen(filename, "r");
 
    // Check if file exists
    if (fp == NULL)
    {
        printf("Could not open file %s", filename);
        return 0;
    }
    clock_t inicio = clock();
  
    // Extract characters from file and store in character c
    // for (c = getc(fp); c != EOF; c = getc(fp))
    //     if (c == '\n') // Increment count if this character is newline
    //         count = count + 1;
    while (EOF != (fscanf(fp, "%*[^\n]"), fscanf(fp,"%*c")))
        ++count;
    
    clock_t fim = clock();

    // Calcula Tempo
    double tempoProc = (double)(fim - inicio) / CLOCKS_PER_SEC;

    rewind(fp);

    while (fgets(filename, MAX_FILE_NAME, fp))
    {
        /* Print each line */
        printf("line[%06d]: %s", ++line_count, filename);
        
        /* Add a trailing newline to lines that don't already have one */
        if (filename[strlen(filename) - 1] != '\n')
            printf("\n");
    }

    printf("Tempo decorrido %.6fs",tempoProc);
    printf("\n");
  
    // Close the file
    fclose(fp);
    printf("The file has %d lines\n ", count);
  
    return 0;
}