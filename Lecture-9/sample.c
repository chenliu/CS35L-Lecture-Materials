#include <stdio.h>

int main()
{
    int iNumber = 0;
    char* sWords = "hellow world\n";
    int iMonth, iDate, iYear;
    char buffer[256];
    char cBuf;

    // Output functions
    fprintf(stdout, "%d: %s", iNumber, sWords);
    fputs(sWords, stdout);
    fputc(sWords[0], stdout);
    fprintf(stdout, "\n\n");

    // Input functions
    fscanf(stdin, "%d-%d-%d,", &iMonth, &iDate, &iYear);
    cBuf = fgetc(stdin);
    fgets(buffer, 5, stdin);

    printf("%d/%d/%d\n", iDate, iMonth, iYear);
    printf("%c\n", cBuf);
    printf("%s\n", buffer);
    return 0;
}
