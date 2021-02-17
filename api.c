#include "handlers.h"


LPdata *GetLP(Bot *bot)
{
    LPdata *lpdata = malloc(sizeof (LPdata));

    cJSON *json = vk_send(bot, "groups.getLongPollServer", CreateParam("group_id", bot->id));
    cJSON *response = cJSON_GetObjectItem(json, "response");

    lpdata->key = cJSON_GetObjectItem(response, "key")->valuestring;
    lpdata->server = cJSON_GetObjectItem(response, "server")->valuestring;
    lpdata->ts = strconv(cJSON_GetObjectItem(response, "ts")->valueint, 32);

    cJSON_free(json);

    return lpdata;
}


void LPThink(Bot *bot)
{
    LPdata *lpdata = GetLP(bot);
    Event *event;
    cJSON *updates, *update;
    net_params *params;

    while(1) {
        params = CreateParam("key", lpdata->key);
        AddParam(params, "ts", lpdata->ts);
        AddParam(params, "wait", "45");
        AddParam(params, "act", "a_check");
        AddParam(params, "version", "3");
        AddParam(params, "mode", "2");
        updates = request(lpdata->server, convParams(params));

        COPYSTRING(lpdata->ts, cJSON_GetObjectItem(updates, "ts")->valuestring);

        if(cJSON_HasObjectItem(updates, "updates")) {
            for(int i = 0; i < cJSON_GetArraySize(cJSON_GetObjectItem(updates, "updates")); i++) {
                update = cJSON_GetArrayItem(cJSON_GetObjectItem(updates, "updates"), i);
                event = CreateEvent(bot, update);

                if(!strcmp(event->etype, "MSG")) {
                    event->splited = strsplit(event->text, " ");
                    if(event->splited) {
                        if(in_array(*&event->splited[0], event->bot->names) && event->splited[1] != NULL)
                            ExecuteEvent(event);
                        free(event->splited);
                        event->splited = NULL;
                    }
                }
            }
            event->updates = NULL;
            free(event);
        }

        cJSON_Delete(updates);
    }
}

cJSON *message_send(Event *event, char *text, char *peer_id, net_params *params)
{
    if(!peer_id)
        peer_id = event->peer_id;

    if(!params)
        params = CreateParam("access_token", event->bot->token);

    if(!has_field("random_id", params))
        AddParam(params, "random_id", "0");

    AddParam(params, "message", text);
    AddParam(params, "peer_id", peer_id);

    return vk_send(event->bot, "messages.send", params);
}


cJSON *vk_send(Bot* bot, const char *method, net_params *params)
{
    if(!params)
        params = CreateParam("access_token", bot->token);

    if(!has_field("access_token", params))
        AddParam(params, "access_token", bot->token);

    if(!has_field("v", params))
        AddParam(params, "v", bot->api_v);


    size_t *url_size = snprintf(NULL,  0, "https://api.vk.com/method/%s", method) + sizeof('\0');
    char *url = malloc(url_size);
    snprintf(url,  url_size, "https://api.vk.com/method/%s", method);
    char *reqParams = convParams(params);

    return request(url, reqParams);
}

const char *BotID(Bot *bot)
{
   char *bot_id = calloc(20, sizeof (char));
   cJSON *json = vk_send(bot, "groups.getById", 0);

   if(cJSON_HasObjectItem(json, "response")) {
       cJSON *response = cJSON_GetObjectItem(json, "response");
       cJSON *items = cJSON_GetArrayItem(response, 0);
       cJSON *id = cJSON_GetObjectItem(items, "id");

       sprintf(bot_id, "%d", id->valueint);
       cJSON_Delete(json);
       return bot_id;
   } else {

       cJSON *error = cJSON_GetObjectItem(json, "error");
       cJSON *error_msg = cJSON_GetObjectItem(error, "error_msg");
       printf("%s\n", error_msg->valuestring);
       cJSON_Delete(json);
       exit(1);
   }

}

void BotInit(Bot *bot)
{
    cJSON *config = cJSON_Parse(ReadFile("bot.json"));
    cJSON *bot_cfg = cJSON_GetObjectItem(config, "bot");

    cJSON *token = cJSON_GetObjectItem(bot_cfg, "token");
    cJSON *api_v = cJSON_GetObjectItem(bot_cfg, "api_v");
    cJSON *names = cJSON_GetObjectItem(bot_cfg,  "names");

    bot->token = token->valuestring;
    bot->api_v = api_v->valuestring;

    size_t names_size = cJSON_GetArraySize(names);
    bot->names = malloc(sizeof (char**) * names_size+1);

    for(int i = 0; i < names_size; i++)
        bot->names[i] = cJSON_GetArrayItem(names, i)->valuestring;

    // Just work!
    bot->names[names_size] = NULL;
    cJSON_free(config);

    bot->id = BotID(bot);
}

void ExecuteEvent(Event *event)
{
    CmdHandler *cmd = GetCmd(*&event->splited[1]);

    if(cmd) {
        cmd->func(event);
    } else {
        message_send(event, "Команда не найдена!", 0, 0);
    }
}
