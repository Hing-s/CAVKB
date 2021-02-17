#include "event.h"


Event *CreateEvent(Bot *bot, cJSON *updates)
{
    Event *event = (Event*)malloc(sizeof (Event));
    event->updates = updates;
    event->etype =  cJSON_GetObjectItem(updates, "type")->valuestring;
    event->bot = bot;

    if(!strcmp(event->etype, "message_new")) {
        event->etype = "MSG";

        cJSON *object = cJSON_GetObjectItem(updates, "object");
        event->peer_id = strconv(cJSON_GetObjectItem(object, "peer_id")->valueint, 15);
        event->userid = strconv(cJSON_GetObjectItem(object, "from_id")->valueint, 15);
        event->text = cJSON_GetObjectItem(object, "text")->valuestring;
    }

    return event;
}
