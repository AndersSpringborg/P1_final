#include "allIncludes.h"

/* ---------------------- Opens file in readmode and returns students ---------------------- */
structStudent *loadStructStudent(int *numberOfStudentsOutput)
{
    int numberOfStudents = 0,
        choose = -1;
    structStudent *result;
    FILE *fileHandle;
    structfile *fileArray;

    fileArray = userSelectFile(&choose);

    fileHandle = fopen(fileArray[choose].name, "r");

    result = (structStudent *)malloc(sizeof(structStudent));
    while(!feof(fileHandle))
    {
        result = expandStructStudent(result, numberOfStudents + 1);
        result[numberOfStudents++] = loadStudent(fileHandle);
    }
    fclose(fileHandle);
    free (fileArray);
    *numberOfStudentsOutput = numberOfStudents;

    return result;
}
/* ---------------------- prompt the user for an class, and returns the input file according to input ---------------------- */
structfile *userSelectFile(int *choose)
{
    int count = 0, strLn, condition = 0;
    DIR *d;
    struct dirent *dir;
    structfile *fileArray;

    fileArray = (structfile *)malloc(sizeof(structfile));
    printf("Your input options are:\n");

    d = opendir(".");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            strLn = strlen(dir->d_name);
            if (dir->d_name[strLn - 1] == 't' && dir->d_name[strLn - 2] == 'x' && dir->d_name[strLn - 3] == 't' && dir->d_name[strLn - 4] == '.' && strcmp(dir->d_name, "result_group.txt") != 0)
            {
                fileArray = (structfile *)realloc(fileArray, (sizeof(structfile) * (count + 1)));
                sscanf(dir->d_name, " %[^'] ", fileArray[count++].name);
                printf("[%d] %s %s\n", count, count < 10 ? " |" : "|", fileArray[count - 1].name);
            }
        }
        closedir(d);
        putchar('\n');
    }

    printf("Insert a number from 1 to %d, according to the class you wish to use\n: ", count);
    do
    {
        if (condition)
        {
            printf("Invalid number, choose one between 1 and %d\n :", count);
        }
        scanf(" %d", choose);
        (*choose)--;
        condition = *choose < 0 || *choose >= count;
    } while (condition);

    return fileArray;
}

/* ---------------------- reallocating memory for students, if unsucessful exits program  ---------------------- */
structStudent *expandStructStudent(structStudent *inputPointer, int size)
{
    structStudent *tmp;
    int byteSize = size * sizeof(structStudent);

    tmp = realloc(inputPointer, byteSize);
    if (tmp != NULL)
        return tmp;
    else
    {
        printf("Program failure, try again\n");
        exit(1);
    }
}

/* ---------------------- Scanning input file, for every line. returns the information of one student at a time ---------------------- */
structStudent loadStudent(FILE *fileHandle)
{
    char tempString[CHAR_LENGTH];
    structStudent tempStruct;

    fscanf(fileHandle, " %[^,],"
                       " %[0-9 ]"
                       " %*[;] ",
                       tempStruct.name, tempString);
    initializeRoleStudent(&tempStruct, tempString);

    return tempStruct;
}

/* ---------------------- intialize tempStruct roles accoring to file input ---------------------- */
void initializeRoleStudent(structStudent *tempStruct, char *tempString)
{
    int i,
        strLen = strlen(tempString);

    for (i = 0; i < BELBINS_ROLES; i++)
    {
        (*tempStruct).role[i] = FALSE;
    }

    for (i = 0; i < strLen; i++)
    {
        if (isdigit(tempString[i]))
        {
            (*tempStruct).role[tempString[i] - ASCII_DIGIT_ONE] = TRUE;
        }
    }
}
