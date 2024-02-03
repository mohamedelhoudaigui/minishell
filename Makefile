SRCS = ./builtins/echo/echo.c ./builtins/pwd/pwd.c env_vars.c minishell.c \
		./builtins/cd/cd.c ./linked_list/ft_command.c ./builtins/exit/exit.c \
		./builtins/env/env.c ./builtins/unset/unset.c redirect.c ./builtins/export/export.c \
		./builtins/export/export_help.c ./entry_point/execution.c ./entry_point/execute_command.c \
		./entry_point/exec_utils.c ./entry_point/handle_pipes.c ./expander/expander.c \
		./open_fd_layer/open_fd.c ./heredoc/heredoc.c
		



OBJS = $(SRCS:.c=.o)


CC = cc

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address

LIBFT = make -C libft && make bonus -C libft  

NAME = minishell

LIBFT_PATH = -Llibft

READ_LINE_NAME = -lreadline

LIBFT_NAME = -lft

all: libs $(NAME)

$(NAME): $(OBJS) ./libft/libft.a
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_PATH) $(LIBFT_NAME) $(READ_LINE_NAME)

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