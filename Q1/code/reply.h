#ifndef REPLY_H
#define REPLY_H 
typedef struct Reply {
    char *username;
    char *content;
    struct Reply *next;
} Reply;
Reply *createReply(char *username, char *content);
#endif 

//reply is made with username, content and pointer to next reply