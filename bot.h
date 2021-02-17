#ifndef BOT_H
#define BOT_H

#include "cJSON/cJSON.h"


typedef struct Bot_s {
    const char *token;
    char **names;
    char *api_v;

    char *id;
} Bot;

#endif // BOT_H
