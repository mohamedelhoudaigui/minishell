SRCS = ./builtins/echo/echo.c ./builtins/pwd/pwd.c env_vars.c minishell.c \
        ./builtins/cd/cd.c ./linked_list/ft_command.c ./builtins/exit/exit.c \
        ./builtins/env/env.c ./builtins/unset/unset.c redirect.c ./builtins/export/export.c \
        ./builtins/export/export_help.c ./entry_point/execution.c ./entry_point/execute_command.c \
        ./entry_point/exec_utils.c ./entry_point/handle_pipes.c ./expander/expander.c \
        ./open_fd_layer/open_fd.c ./heredoc/heredoc.c ./parse/garbage.c ./parse/lexer.c \
		./parse/utils.c ./parse/tokenizer.c

OBJS = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address

LIBFT = make -C libft

NAME = minishell

LIBFT_PATH = ./libft/libft.a

READ_LINE_NAME = -lreadline

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_PATH) $(READ_LINE_NAME)


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