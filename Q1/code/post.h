#ifndef POST_H
#define POST_H
#include "comment.h"
typedef struct Post {
    char *username;
    char *caption;
    Comment *comments;
    struct Post *next;
} Post;
Post *createPost(char *username, char *caption);
#endif
//post is made with username, caption, pointer to the comments and pointer to next post