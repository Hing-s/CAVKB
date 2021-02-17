#include "utils.h"


// code by fzawacki(https://stackoverflow.com/questions/3463426/in-c-how-should-i-read-a-text-file-and-print-all-strings)
char* ReadFile(char *filename)
{
   char *buffer = NULL;
   int string_size, read_size;
   FILE *handler = fopen(filename, "r");

   if (handler)
   {
       // Seek the last byte of the file
       fseek(handler, 0, SEEK_END);
       // Offset from the first to the last byte, or in other words, filesize
       string_size = ftell(handler);
       // go back to the start of the file
       rewind(handler);

       // Allocate a string that can hold it all
       buffer = malloc(sizeof(char) * (string_size + 1) );

       // Read it all in one operation
       read_size = fread(buffer, sizeof(char), string_size, handler);

       // fread doesn't set it so put a \0 in the last position
       // and buffer is now officially a string
       buffer[string_size] = '\0';

       if (string_size != read_size)
       {
           // Something went wrong, throw away the memory and set
           // the buffer to NULL
           free(buffer);
           buffer = NULL;
       }

       // Always remember to close the file.
       fclose(handler);
    }

    return buffer;
}


int has_field(const char *key, net_params *params)
{
    for(int i = 0; i < params->size; i++)
        if(!strcmp(key, params->params[i]->param))
            return 1;

    return 0;
}

int in_array(char *item, char **array) {
    for(int i = 0;; i++)
    {
        if(!&*array[i])
            break;

        if(!strcmp(&*array[i], item))
            return  1;
    }
    return 0;
}

char *strconv(int value, size_t size)
{
    char *str = calloc(size, sizeof (char));
    sprintf(str, "%d", value);

    return str;
}


char **strsplit(char *str, char *token)
{
    if(!strcmp(str, ""))
        return NULL;

    int size = 1;
    char **arr = malloc(sizeof (char*));
   // char *lower = toLower(str);
    char *s = strtok(str, token);

    while(s) {
        arr[size-1] = s;
        size++;
        arr = realloc(arr, size*sizeof(char*));
        s = strtok(NULL, token );
    }

    return arr;
}


char *characters[][2] = {
    {'A', 'a'},
    {'B', 'b'},
    {'C', 'c'},
    {'D', 'd'},
    {'E', 'e'},
    {'F', 'f'},
    {'G', 'g'},
    {'H', 'h'},
    {'I', 'i'},
    {'J', 'j'},
    {'K', 'k'},
    {'L', 'l'},
    {'M', 'm'},
    {'N', 'n'},
    {'O', 'o'},
    {'P', 'p'},
    {'Q', 'q'},
    {'R', 'r'},
    {'S', 's'},
    {'T', 't'},
    {'U', 'u'},
    {'V', 'v'},
    {'W', 'w'},
    {'X', 'x'},
    {'Y', 'y'},
    {'Z', 'z'},
    {'А', 'а'},
    {'Б', 'б'},
    {'В', 'в'},
    {'Г', 'г'},
    {'Д', 'д'},
    {'Е', 'е'},
    {'Ё', 'ё'},
    {'Ж', 'ж'},
    {'З', 'з'},
    {'И', 'и'},
    {'Й', 'й'},
    {'К', 'к'},
    {'Л', 'л'},
    {'М', 'м'},
    {'Н', 'н'},
    {'О', 'о'},
    {'П', 'п'},
    {'Р', 'р'},
    {'С', 'с'},
    {'Т', 'т'},
    {'У', 'у'},
    {'Ф', 'ф'},
    {'Х', 'х'},
    {'Ч', 'ч'},
    {'Ш', 'ш'},
    {'Ъ', 'ъ'},
    {'Щ', 'щ'},
    {'Ь', 'ь'},
    {'Ц', 'ц'},
    {'Ы', 'ы'},
    {'Э', 'э'},
    {'Ю', 'ю'},
    {'Я', 'я'}
};


char *toLower(char *str)
{
    char *lower = calloc((strlen(str)+1)*sizeof(char), sizeof(char));
    strcpy(lower, str);

    for(int j = 0; j < strlen(str); j++) {
        for(int i = 0; i < 59; i++)
            if(str[j] == characters[i][0]) {
                lower[j] = characters[i][1];
                break;
            }
    }


    printf("LOWER: %s\n", lower);

    return lower;
}
