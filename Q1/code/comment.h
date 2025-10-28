#ifndef COMMENT_H
#define COMMENT_H 
#include "reply.h"
typedef struct Comment {
    char *username;
    char *content;
    Reply *replies;
    struct Comment *next;
} Comment;
Comment *createComment(char *username, char *content);
#endif 
//coomment is made with username, content, pointer to the replies and pointer to next comment