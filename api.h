#ifndef API_H
#define API_H

#include "event.h"

typedef struct {
    const char *key;
    const char *ts;
    const char *server;
} LPdata;

LPdata *GetLP(Bot *bot);
void LPThink(Bot *bot);
void BotInit(Bot *bot);
cJSON *vk_send(Bot *, const char*, net_params *);
cJSON *message_send(Event *, char *, char *, net_params *);
const char *BotID(Bot *);
void ExecuteEvent(Event *);

#endif // API_H
