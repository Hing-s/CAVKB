#ifndef HANDLERS_H
#define HANDLERS_H

#include "api.h"

typedef struct {
    void (*func)(Event*);
    const char *cmd;
    int access;

    void *other;
} CmdHandler;

typedef struct {
    void (*func)(Event*);
    const char *etype;
} EventHandler;

void HandleCmd(const char*, void(*)(Event*), int, void*);
void HandleEvent(const char*, void(*)(Event*));
void InitHanlers();

CmdHandler *CMDS;
EventHandler *EVENTS;

CmdHandler *GetCmd(const char *);


#endif // HANDLERS_H
