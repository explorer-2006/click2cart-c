#include <stdio.h>
#include <string.h>

int main()
{
    char fname[30] = "meet";
    char space[30] = " ";

    char lname[30] = "buddhdev";
    char name[30];
    snprintf(name, sizeof(name), "%s %s", fname, lname);
    FILE *pFile = fopen("registered.txt", "a");
    fprintf(pFile, "%s", name);
    fclose(pFile);

    return 0;
}