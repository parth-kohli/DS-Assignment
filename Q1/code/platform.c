
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "platform.h"
Platform *platform = NULL;
#define MAX_STACK_SIZE 1000
//A stack to delete the nth recent comment
typedef struct CommentStack {
    Comment *arr[MAX_STACK_SIZE];
    int top;
} CommentStack;


void push(CommentStack *s, Comment *c) {
    if (s->top < MAX_STACK_SIZE - 1) {
        s->arr[++(s->top)] = c;
    }
}
Comment* pop(CommentStack *s) {
    if (s->top == -1) return NULL;
    return s->arr[(s->top)--];
}
//Helper function to delete all replies
void freeReplies(Reply *reply){
    while(reply){
        Reply *temp = reply;
        reply = reply->next;
        free(temp->username); 
        free(temp->content);  
        free(temp);
    }
}
//Helper function to delete all comments
void freeComments(Comment *comment){
    while(comment){
        freeReplies(comment->replies);
        Comment *temp = comment;
        comment = comment->next;
        free(temp->username); 
        free(temp->content);  
        free(temp);
    }
}
Platform *createPlatform() {
    platform = (Platform *)malloc(sizeof(Platform));
    platform->posts = NULL;
    platform->lastViewedPost = NULL;
    return platform;
}
bool addPost(char *username, char *caption) {
    Post *newPost = createPost(username, caption);
    if (!newPost) return false;
    newPost->next = platform->posts;
    platform->posts = newPost;
    platform->lastViewedPost = newPost;
    return true;
}
bool deletePost(int n) {
    //returns false if no post to delete
    if (n < 1 || !platform->posts) return false;
    Post *temp = platform->posts;
    Post *prev = NULL;
    for (int i = 1; temp != NULL && i < n; i++) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) return false;
    
    if (prev == NULL) {
        platform->posts = temp->next;
    }
    if (platform->lastViewedPost == temp) {
        platform->lastViewedPost = platform->posts;
    }
else {
        prev->next = temp->next;
    }
    freeComments(temp->comments);
    free(temp->username);
    free(temp->caption);  
    free(temp);
    return true;
}
Post* viewPosts(int n) {
    if (n < 1) return NULL;
    Post *temp = platform->posts;
    for (int i = 1; temp != NULL && i < n; i++) {
        temp = temp->next;
    }
    if (temp) {
        platform->lastViewedPost = temp;
    }
    return temp;
}
Post *currPost(){
    return platform->lastViewedPost;
}
Post *nextPost(){
    if(platform->lastViewedPost && platform->lastViewedPost->next) 
        platform->lastViewedPost = platform->lastViewedPost->next;
    return platform->lastViewedPost;
}
Post* previousPost() {
    Post* current = currPost();
    if (current == NULL || current == platform->posts) 
        return current;
    Post* temp = platform->posts;
    while(temp != NULL && temp->next != current) 
        temp = temp->next;
    if (temp != NULL) 
         platform->lastViewedPost = temp;
    return temp;
}
bool addComment(char *username, char *content) {
    if (!platform->lastViewedPost) return false;
    Comment *newComment = createComment(username, content);
    if (!newComment) return false;
    Comment **curr = &platform->lastViewedPost->comments;
    while(*curr) curr = &((*curr)->next);
    *curr = newComment;
    newComment->next = NULL;
    return true;
}
//deletes comments by traversing the list of comments and adding to a stack and popping n elements to delete
bool deleteComment(int n) {
    if (!platform->lastViewedPost || n < 1 || !platform->lastViewedPost->comments) return false;
    CommentStack s;
    s.top = -1;
    Comment *temp = platform->lastViewedPost->comments;
    while (temp) {
        push(&s, temp);
        temp = temp->next;
    }
    if (n > s.top + 1) return false;
    Comment *toDelete = NULL;
    for (int i = 0; i < n; i++) {
        toDelete = pop(&s);
    }
    Comment *prev = (s.top == -1) ? NULL : s.arr[s.top];
    if (prev == NULL) {
        platform->lastViewedPost->comments = toDelete->next;
    } else {
        prev->next = toDelete->next;
    }
    freeReplies(toDelete->replies);
    free(toDelete->username);
    free(toDelete->content);
    free(toDelete);
    return true;
}
Comment* viewComments() {
    if (!platform->lastViewedPost) return NULL;
    return platform->lastViewedPost->comments;
}
bool addReply(char *username, char *content, int n) {
    if (!platform->lastViewedPost || n < 1 || !platform->lastViewedPost->comments) return false;
    Comment *tempComment = platform->lastViewedPost->comments;
    int len = 0;
    for (Comment *c = tempComment; c; c = c->next) len++;
    if (n > len) return false;
    int target = len - n + 1;
    for (int i = 1; tempComment != NULL && i < target; i++) {
        tempComment = tempComment->next;
    }
    if (!tempComment) return false;
    Reply *newReply = createReply(username, content);
    if (!newReply) return false;
    Reply **curr = &tempComment->replies;
    while(*curr) curr = &((*curr)->next);
    *curr = newReply;
    newReply->next = NULL;
    return true;
}
//goes through all replies and pops out n to get the nth recent one and deletes it
bool deleteReply(int n, int m) {
    if (!platform->lastViewedPost || n < 1 || m < 1 || !platform->lastViewedPost->comments) return false;
    Comment *tempComment = platform->lastViewedPost->comments;
    int comm_len = 0;
    for (Comment *c = tempComment; c; c = c->next) comm_len++;
    if (n > comm_len) return false;
    int comment = comm_len - n + 1;
    for (int i = 1; tempComment != NULL && i < comment; i++) {
        tempComment = tempComment->next;
    }
    if (!tempComment || !tempComment->replies) return false;
    Reply *head = tempComment->replies;
    int rep_len = 0;
    for (Reply *r = head; r; r = r->next) rep_len++;
    if (m > rep_len) return false;
    int reply = rep_len - m + 1;
    Reply *tempReply = head;
    Reply *prev = NULL;
    for (int i = 1; tempReply != NULL && i < reply; i++) {
        prev = tempReply;
        tempReply = tempReply->next;
    }
    if (tempReply == NULL) return false;
    if (prev == NULL) {
        tempComment->replies = tempReply->next;
    }
    else {
        prev->next = tempReply->next;
    }
    free(tempReply->username);
    free(tempReply->content);
    free(tempReply);
    return true;
}
