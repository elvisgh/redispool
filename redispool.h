#ifndef _REDISPOOL_H
#define _REDISPOOL_H

#include <hiredis/hiredis.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_CONNECTION_NUM 10

void redis_pool_init(redisContext **redis_pool) {
    for (int i = 0; i < MAX_CONNECTION_NUM; i++) {
        redis_pool[i] = (redisContext*)malloc(sizeof(redisContext));
        redis_pool[i] = redisConnect("127.0.0.1", 6379);
    }
}

redisContext* getConn(redisContext **redis_pool) {
    for (int i = 0; i < MAX_CONNECTION_NUM; i++) {
        if (redis_pool[i] != NULL) {
            redisContext* c = redis_pool[i];
            redis_pool[i] = NULL;
            return c;
        }
    }

    return NULL;
}

#endif
