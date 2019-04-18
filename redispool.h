#ifndef _REDISPOOL_H
#define _REDISPOOL_H

#include <hiredis/hiredis.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_CONNECTION_NUM 10

redisContext* pool[MAX_CONNECTION_NUM];

static void redispool_init() 
{
    printf("redis pool init...\n");
    for (int i = 0; i < MAX_CONNECTION_NUM; i++) 
    {
        pool[i] = redisConnect("127.0.0.1", 6379);
    }
}

static redisContext* getContext() 
{
    for (int i = 0; i < MAX_CONNECTION_NUM; i++) 
    {
        if (pool[i] != NULL) 
        {
            redisContext* c = pool[i];
            pool[i] = NULL;
            return c;
        }
    }

    return NULL;
}

static void reidspool_destroy()
{
    printf("redis pool destroy...\n");
    for (int i = 0; i < MAX_CONNECTION_NUM; i++)
    {
        redisFree(pool[i]);
    }
}

#endif
