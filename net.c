#include "net.h"

net_params *CreateParam(const char *param, const char *value)
{
    net_params *params = malloc(sizeof (net_params));
    net_param *new_param = malloc(sizeof (net_param));

    new_param->param = param;
    new_param->value = value;

    params->params = malloc(sizeof (net_param*));
    params->params[0] = new_param;
    params->size = 1;

    return params;
}


void AddParam(net_params *params, const char *param, const char *value)
{
    params->params = realloc(params->params, sizeof(net_param*) * ++params->size);
    net_param *new_param = malloc(sizeof (net_param));

    new_param->param = param;
    new_param->value = value;

    params->params[params->size-1] = new_param;
}

net_params *CreateParams(char* new_params[][2])
{
    size_t size = sizeof(new_params[0])/sizeof(new_params[0][0]);
    net_params *params = malloc(sizeof (net_params));
    net_param *new_param;
    params->params = malloc(sizeof (net_param*));

    for(int i = 0; i < size ; i++) {
        new_param = malloc(sizeof(net_param));
        new_param->param = new_params[i][0];
        new_param->value = new_params[i][1];

        params->params[i] = new_param;
        params->size++;
    }

    return params;

}

char *convParams(net_params *params)
{
    char *reqParam = calloc(512, sizeof(char));
    char *param;
    size_t param_size;


    for(int i = 0; i < params->size; i++) {
       if(!strcat(params->params[i]->param, ""))
           continue;

       param_size = snprintf(NULL, 0, "%s=%s&", params->params[i]->param, params->params[i]->value) + sizeof ('\0');
       param = malloc(param_size);
       snprintf(param, param_size, "%s=%s&", params->params[i]->param, params->params[i]->value);
       strcat(reqParam, param);
       free(param);
       param = 0;
    }

    NetParams_Free(params);
    return reqParam;
}



/* Code by Gerhardh(https://stackoverflow.com/questions/59454006/how-to-use-curl-in-c-and-parse-json-response) */
typedef struct {
    unsigned char *buffer;
    size_t len;
    size_t buflen;
} get_request;

#define CHUNK_SIZE 2048

size_t write_data(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    size_t realsize = size * nmemb;
    get_request *req = (get_request *) userdata;

    while (req->buflen < req->len + realsize + 1)
    {
        req->buffer = realloc(req->buffer, req->buflen + CHUNK_SIZE);
        req->buflen += CHUNK_SIZE;
    }
    memcpy(&req->buffer[req->len], ptr, realsize);
    req->len += realsize;
    req->buffer[req->len] = '\0';

    puts(req->buffer);

    return realsize;
}
/*  -------------------------------------------------------- */

cJSON *request(const char *url, const char *params) {
    get_request data = {.buffer = NULL, .len = 0, .buflen = 0};

    CURL *curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, params);
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &write_data);

    curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    cJSON *response = cJSON_Parse(data.buffer);

    free(data.buffer);
    free(params);

    return response;

}

void NetParams_Free(net_params *params) {
    for(int i = 0; i < params->size; i++)
        free(params->params[i]);

    free(params);
}

