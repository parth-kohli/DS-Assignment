#include <stdlib.h>
#include <string.h>
#include "reply.h"
Reply *createReply(char *username, char *content) {
    Reply *newReply = (Reply *)malloc(sizeof(Reply));
    newReply->username = malloc(strlen(username) + 1);
    strcpy(newReply->username, username);
    newReply->content = malloc(strlen(content) + 1);
    strcpy(newReply->content, content);
    newReply->next = NULL;
    return newReply;
}