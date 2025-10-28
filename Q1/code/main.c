#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "platform.h" 

int main(){
    printf("----------------------------------\n");
    printf("Welcome to the social media platform\n");
    printf("----------------------------------\n");
    printf("Enter the following commands to proceed :\n");
    printf("1. create_platform \n2. add_post \n3. delete_post \n4. view_posts \n5. curr_post \n6. next_post \n7. previous_post \n8. add_comment \n9. delete_comment \n10. view_comments \n11. add_reply \n12. delete_reply \n13. exit\n");
    char command[50];
    Platform *platform = NULL;
    while(1){
        printf("==================================\n");
        printf("Enter command: ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0;
        if(strcmp(command, "create_platform") == 0){
            if(platform != NULL){
                printf("Platform already exists\n");
            } 
            else {
                platform = createPlatform();
                printf("Platform created successfully\n");
            }
        }
        else if(strcmp(command, "add_post") == 0){
            if(platform == NULL){
                printf("No platform available\n");
            }
            else {
                char username[50], caption[200];
                printf("Enter username: ");
                fgets(username, sizeof(username), stdin);
                username[strcspn(username, "\n")] = 0; 
                printf("Enter caption: ");
                fgets(caption, sizeof(caption), stdin);
                caption[strcspn(caption, "\n")] = 0; 
                if(addPost(username, caption)){
                    printf("Post added successfully\n");
                }
                else {
                    printf("Failed to add post\n");
                }
            }
        }
        else if(strcmp(command, "delete_post") == 0){
            if(platform == NULL){
                printf("No platform available\n");
            }
            else {
                int n;
                printf("Enter post number to delete: ");
                scanf("%d", &n);
                while (getchar() != '\n');
                if(deletePost(n)){
                    printf("Post deleted successfully\n");
                }
                else {
                    printf("Failed to delete post\n");
                }
            }
        }
        else if(strcmp(command, "view_posts") == 0){
            if(platform == NULL){
                printf("No platform available\n");
            }
            else {
                int n;
                printf("Enter index of post to view (1 for most recent): ");
                scanf("%d", &n);
                while (getchar() != '\n');
                Post *post = viewPosts(n);
                if(post == NULL){
                    printf("No posts available\n");
                }
                else {
                    printf("Post %d:\n", n);
                    printf("Username: %s\n", post->username);
                    printf("Caption: %s\n", post->caption);
                }
            }
        }
        else if(strcmp(command, "curr_post") == 0){
            if(platform == NULL){
                printf("No platform available\n");
            }
            else {
                Post *post = currPost();
                if(post == NULL){
                    printf("No current post available\n");
                }
                else {
                    printf("Current Post:\n");
                    printf("Username: %s\n", post->username);
                    printf("Caption: %s\n", post->caption);
                }
            }
        }
        else if(strcmp(command, "next_post") == 0){
            if(platform == NULL){
                printf("No platform available\n");
            }
            else {
                Post *post = nextPost();
                if(post == NULL){
                    printf("No next post available\n");
                }
                else {
                    printf("Next Post:\n");
                    printf("Username: %s\n", post->username);
                    printf("Caption: %s\n", post->caption);
                }
            }
        }
        else if(strcmp(command, "previous_post") == 0){
            if(platform == NULL){
                printf("No platform available\n");
            }
            else {
                Post *post = previousPost(platform);
                if(post == NULL){
                    printf("No previous post available\n");
                }
                else {
                    printf("Previous Post:\n");
                    printf("Username: %s\n", post->username);
                    printf("Caption: %s\n", post->caption);
                }
            }
        }
        else if(strcmp(command, "add_comment") == 0){
            if(platform == NULL){
                printf("No platform available\n");
            }
            else {
                char username[50], content[200];
                printf("Enter username: ");
                fgets(username, sizeof(username), stdin);
                username[strcspn(username, "\n")] = 0;
                printf("Enter comment content: ");
                fgets(content, sizeof(content), stdin);
                content[strcspn(content, "\n")] = 0;
                if(addComment(username, content)){
                    printf("Comment added successfully\n");
                }
                else {
                    printf("Failed to add comment\n");
                }
            }
        }
        else if(strcmp(command, "delete_comment") == 0){
            if(platform == NULL){
                printf("No platform available\n");
            }
            else {
                int n;
                printf("Enter comment number to delete: ");
                scanf("%d", &n);
                while (getchar() != '\n');
                if(deleteComment(n)){
                    printf("Comment deleted successfully\n");
                }
                else {
                    printf("Failed to delete comment\n");
                }
            }
        }
        else if(strcmp(command, "view_comments") == 0){
            if(platform == NULL){
                printf("No platform available\n");
            }
            else {
                Comment *comment = viewComments();
                if(comment == NULL){
                    printf("No comments available for the current post\n");
                }
                else {
                    int count = 1;
                    while(comment != NULL){
                        printf("----------------------------------\n");
                        printf("Comment %d:\n", count);
                        printf("Username: %s\n", comment->username);
                        printf("Content: %s\n", comment->content);
                        Reply *reply = comment->replies;
                        int replyCount = 1;
                        while(reply != NULL){
                            printf("----------------------------------\n");
                            printf("  Reply %d:\n", replyCount);
                            printf("  Username: %s\n", reply->username);
                            printf("  Content: %s\n", reply->content);
                            reply = reply->next;
                            replyCount++;
                        
                        }
                        comment = comment->next;
                        count++;
                    }
                    printf("----------------------------------\n");
                }
            }
        }
        else if(strcmp(command, "add_reply") == 0){
            if(platform == NULL){
                printf("No platform available\n");
            }
            else {
                char username[50], content[200];
                int n;
                printf("Enter comment number to reply to: ");
                scanf("%d", &n);
                while (getchar() != '\n');
                printf("Enter username: ");
                fgets(username, sizeof(username), stdin);
                username[strcspn(username, "\n")] = 0;
                printf("Enter reply content: ");
                fgets(content, sizeof(content), stdin);
                content[strcspn(content, "\n")] = 0;
                if(addReply(username, content, n)){
                    printf("Reply added successfully\n");
                }
                else {
                    printf("Failed to add reply\n");
                }
            }
        }
        else if(strcmp(command, "delete_reply") == 0){
            if(platform == NULL){
                printf("No platform available\n");
            }
            else {
                int n, m;
                printf("Enter comment number: ");
                scanf("%d", &n);
                while (getchar() != '\n');
                printf("Enter reply number to delete: ");
                scanf("%d", &m);
                while (getchar() != '\n');
                if(deleteReply(n, m)){
                    printf("Reply deleted successfully\n");
                }
                else {
                    printf("Failed to delete reply\n");
                }
            }
        }
        else if(strcmp(command, "exit") == 0){
            printf("Exiting the platform\n");
            break;
        }
        else {
            printf("Invalid command\n");
        }

    }
    return 0;
}
                        