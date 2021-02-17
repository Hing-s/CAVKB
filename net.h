#ifndef NET_H
#define NET_H

#include "curl/curl.h"
#include "stdlib.h"
#include "cJSON/cJSON.h"
#include "bot.h"


typedef struct {
    const char *param;
    const char *value;
} net_param;


typedef struct {
    net_param **params;
    size_t size;
} net_params;


net_params *CreateParam(const char*, const char *);
net_params *CreateParams(char *[][2]);
void AddParam(net_params *, const char *, const char *);
cJSON *request(const char *url, const char *);
char *convParams(net_params *);

void NetParams_Free(net_params *);

#endif // NET_H
