#include <stdio.h>
#include <stdlib.h>
#include "comment.h"
#include <string.h>
Comment *createComment(char *username, char *content) {
    Comment *newComment = (Comment *)malloc(sizeof(Comment));
    newComment->username = malloc(strlen(username) + 1);
    strcpy(newComment->username, username);
    newComment->content = malloc(strlen(content) + 1);
    strcpy(newComment->content, content);
    newComment->replies = NULL;
    newComment->next = NULL;
    return newComment;
}