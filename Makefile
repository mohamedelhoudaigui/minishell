SRCS = ./builtins/echo/echo.c ./builtins/pwd/pwd.c env_vars.c expanding.c minishell.c \
		./builtins/cd/cd.c ./linked_list/ft_command.c

OBJS = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g

LIBFT = make -C libft && make bonus -C libft

NAME = minishell

LIBFT_PATH = -Llibft

LIBFT_NAME = -lft

all: libs $(NAME)

$(NAME): $(OBJS) ./libft/libft.a
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_PATH) $(LIBFT_NAME) $(LIBFTPRINTF_PATH) $(LIBFTPRINTF_NAME)

libs:
	$(LIBFT)

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(LIBFT) clean

fclean: clean
	$(RM) $(NAME)
	$(LIBFT) fclean

re: fclean all

.PHONY: clean