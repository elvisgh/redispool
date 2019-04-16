#include "redispool.h"

int main()
{
    redisContext* redis_pool[MAX_CONNECTION_NUM];
    redis_pool_init(redis_pool);
    redisContext *c = getConn(redis_pool);

    redisReply *reply = redisCommand(c, "auth %s", "your_pin");
    if (reply->type != REDIS_REPLY_ERROR) {
        printf("success\n");
    }
    else
    {
        printf("fail\n");
    }
    reply = redisCommand(c, "keys %s", "special_key");
    if (reply->element == NULL) {
        printf("reply->element == NULL\n");
    }

    if (reply->elements == 0) {
        printf("reply->element == 0\n");
    }
    else {
        printf("reply->element = %zu\n", reply->elements);
    }
    redisReply** replyArr = reply->element;
    int pos = 0;
    while (pos != reply->elements) {
        /* Create the poc room */
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

    return 0;
}
