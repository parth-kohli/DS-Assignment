#include <stdio.h>
#include <stdlib.h>
typedef struct familymember{
    struct familymember* left;
    struct familymember* right;
} familymember;
typedef struct queue{
    familymember** items;
    int front;
    int rear;
    int maxsize;
} queue;
void initQueue(queue* q, int size) {
    q->items = (familymember**)malloc(size * sizeof(familymember*));
    q->front = 0;
    q->rear = -1;
    q->maxsize = size;
}
int isQueueEmpty(queue* q) {
    return q->front > q->rear;
}
int isQueueFull(queue* q) {
    return q->rear == q->maxsize - 1;
}
void enqueue(queue* q, familymember* member) {
    if (!isQueueFull(q)) {
        q->items[++q->rear] = member;
    }
}
familymember* dequeue(queue* q) {
    if (!isQueueEmpty(q)) {
        return q->items[q->front++];
    }
    return NULL;
}
familymember* createFamilyMember() {
    familymember* member = (familymember*)malloc(sizeof(familymember));
    member->left = NULL;
    member->right = NULL;
    return member;
}
int height(familymember* root) {
    if (root == NULL) {
        return 0;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}
/*
function returns value 0 to the parent if it doesn't have any phone and is not covered
returns 1 to the parent if it has a phone 
returns 2 if it's child has a phone*/
int numberofphones(familymember* node, int* phoneCount) {
    if (node == NULL) {
        return 2;
    }
    int left = numberofphones(node->left, phoneCount);
    int right = numberofphones(node->right, phoneCount);
    if (left == 0 || right == 0) {
        (*phoneCount)++;
        return 1;
    }
    if (left == 1 || right == 1) {
        return 2;
    }
    return 0;
}
//returns list of first count prime numbers
void getPrimes(int count, int* primes) {
    int curr = 2; 
    int index2 = 0;
    while (index2 < count) {
        int isPrime = 1;
        for (int i = 2; i * i <= curr; i++) {
            if (curr % i == 0) {
                isPrime = 0;
                break;
            }
        }
        if (isPrime==1) {
            primes[index2++] = curr;
        }
        curr++;
    }
}

int cactiCount(int count, int l, int r) {
    int primes[count];
    getPrimes(count, primes);
    int count2 = 0;
    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            int cacti = primes[i] ^ primes[j];
            if (cacti < l || cacti > r)
                count2++;
        }
    }
    return count2;
}

int main(){
    int n, l, r;
    printf("Enter length of level order traversal: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter level order traversal (0 for NULL): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    printf("Enter left limit: ");
    scanf("%d", &l);
    printf("Enter right limit: ");
    scanf("%d", &r);
    if (l > r) {
        printf("Invalid range\n");
        return 0;
    }
    if (arr[0]==0){
        printf("The family tree is empty.\n");
        return 0;
    }
    familymember* root = createFamilyMember();
    queue q;
    initQueue(&q, n);
    enqueue(&q, root);
    int index = 1;
    while (!isQueueEmpty(&q) && index < n) {
        familymember* current = dequeue(&q);
        if (arr[index] != 0) {
            current->left = createFamilyMember();
            enqueue(&q, current->left);
        }
        index++;
        if (index < n && arr[index] != 0) {
            current->right = createFamilyMember();
            enqueue(&q, current->right);
        }
        index++;
    }
    int count = 0;
    if (numberofphones(root, &count) == 0) {
        count++;
    }
    printf("Minimum number of phones needed: %d\n", count);
    int count2 = cactiCount(count, l,r);
    printf("Number of cacti outside range = ""%d\n", count2);
    return 0;
    
}
