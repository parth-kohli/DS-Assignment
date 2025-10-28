CC = gcc
CFLAGS = -Wall -Wextra -std=c11
SRC = code/main.c code/platform.c code/post.c code/reply.c code/comment.c
OBJ = $(SRC:.c=.o)
OUT = main
all: $(OUT)
$(OUT): $(OBJ)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJ)

clean:
	rm -f $(OBJ) $(OUT)
