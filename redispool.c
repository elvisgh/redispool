#include "redispool.h"

int main()
{
    
    redispool_init();
    redisContext *c = getContext();

    redisReply *reply = redisCommand(c, "auth %s", "***");
    if (reply->type != REDIS_REPLY_ERROR) {
        printf("success\n");
    }
    else
    {
        printf("fail\n");
    }
    reply = redisCommand(c, "keys %s", "grp:*:mem");
    if (reply->element == NULL) {
        printf("reply->element == NULL\n");
    }

    if (reply->elements == 0) {
        printf("reply->elements == 0\n");
    }
    else {
        printf("reply->elements = %zu\n", reply->elements);
    }
    redisReply** replyArr = reply->element;
    int pos = 0;
    while (pos != reply->elements) {
        /* "grp:1234:mem" */
        redisReply *group = *(replyArr + pos);
        char idStr[20] = {'\0'};
        int pos_f = strlen("grp:");
        int pos_s = strlen(group->str) - strlen(":mem");
        int len = pos_s - pos_f;
        strncpy(idStr, group->str + pos_f, len);
        int room_id = atoi(idStr);

        if (room_id < 0 || room_id == 0) {
                printf("fatal room_id %d\n", room_id);
                ++pos;
                continue;
        }
        printf("room_id %d\n", room_id);
        ++pos;
    }

    reidspool_destroy();

    return 0;
}
