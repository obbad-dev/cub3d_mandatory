CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lm -lmlx -lXext -lX11 -Lminilibx-linux
CC = cc
RM = rm -f
NAME = cube3D
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

all: $(NAME)
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	$(RM) $(OBJS)
fclean: clean
	$(RM) $(NAME)
re: fclean all
.PHONY: all clean fclean re

