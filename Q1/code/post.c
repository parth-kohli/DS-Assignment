#include <stdlib.h>
#include <string.h>
#include "post.h"
Post *createPost(char *username, char *caption) {
    Post *newPost = (Post *)malloc(sizeof(Post));
    newPost->username = malloc(strlen(username) + 1);
    strcpy(newPost->username, username);
    newPost->caption = malloc(strlen(caption) + 1);
    strcpy(newPost->caption, caption);
    newPost->comments = NULL;
    newPost->next = NULL;
    return newPost;
}