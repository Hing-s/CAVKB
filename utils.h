#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON/cJSON.h"
#include "net.h"

#define COPYSTRING(a, b) strncpy(a, b, (sizeof(char) * strlen(b)) + sizeof('\0'))

char* ReadFile(char *filename);
int has_field(const char *, net_params *);
int in_array(char*, char**);
char *strconv(int, size_t);
char **strsplit(char *, char*);
char *toLower(char *);
#endif // UTILS_H
