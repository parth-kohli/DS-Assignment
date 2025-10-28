#ifndef PLATFORM_H
#define PLATFORM_H
#include "post.h"
#include <stdbool.h>
typedef struct Platform {
    Post *posts;
    Post *lastViewedPost;
} Platform;
extern Platform *platform;
//global declaration of a single platform
Platform * createPlatform();
bool addPost(char *username, char *caption);
bool deletePost(int n);
Post* viewPosts(int n);
Post *currPost();
Post *nextPost();
Post *previousPost();
bool addComment(char *username, char *content);
bool deleteComment(int n);
Comment* viewComments();
bool addReply(char *username, char *content, int n);
bool deleteReply(int n, int m);
#endif

