#include "handlers.h"


int main(int argc, char *argv[])
{
    Bot bot;
    BotInit(&bot);
    InitHanlers();
    LPThink(&bot);

    return 0;
}
