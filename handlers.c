#include "handlers.h"

int CMDS_COUNT = 0;
int EVENTS_COUNT = 0;

void HandleCmd(const char *cmd, void(*func)(Event*), int access, void *other)
{

    if(!CMDS)
    {
        CMDS = malloc(sizeof (CmdHandler));
        CMDS_COUNT = 1;

        CMDS[0].cmd = cmd;
        CMDS[0].func = func;
        CMDS[0].access = access;
        CMDS[0].other = other;
\
    } else {

        CMDS = realloc(CMDS, sizeof (CmdHandler) * ++CMDS_COUNT);

        CMDS[CMDS_COUNT].cmd = cmd;
        CMDS[CMDS_COUNT].func = func;
        CMDS[CMDS_COUNT].access = access;
        CMDS[CMDS_COUNT].other = other;

    }
}


void test(Event *event)
{
    message_send(event, "Я работаю, все норм!", 0, 0);
}

void InitHanlers()
{
    HandleCmd("test", &test, 0, 0);
}

CmdHandler *GetCmd(const char *cmd)
{
    for(int i = 0; i < CMDS_COUNT; i++) {
        if(!strcmp(CMDS[i].cmd, cmd))
            return &CMDS[i];
    }

    return NULL;
}
