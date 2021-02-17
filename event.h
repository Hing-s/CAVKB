#ifndef EVENT_H
#define EVENT_H

#include "utils.h"

typedef struct {
    const char *peer_id;
    const char *userid;
    const char *message_id;
    const char *etype;
    char *text;
    char **splited;

    Bot *bot;
    cJSON *updates;

} Event;

Event *CreateEvent(Bot *, cJSON *);
#endif // EVENT_H
