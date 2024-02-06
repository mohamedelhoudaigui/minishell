SRCS = ./builtins/echo/echo.c ./builtins/pwd/pwd.c env_vars.c minishell.c \
        ./builtins/cd/cd.c ./linked_list/ft_command.c ./builtins/exit/exit.c \
        ./builtins/env/env.c ./builtins/unset/unset.c redirect.c ./builtins/export/export.c \
        ./builtins/export/export_help.c ./entry_point/execution.c ./entry_point/execute_command.c \
        ./entry_point/exec_utils.c ./entry_point/handle_pipes.c ./expander/expander.c \
        ./open_fd_layer/open_fd.c  ./heredoc/heredoc.c ./heredoc/heredoc_help.c ./parse/garbage.c ./parse/parser.c \
		./parse/utils.c ./parse/tokenizer.c ./linker.c ./open_fd_layer/open_fd_help.c ./signals/cmd_signal.c \

OBJS = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

LIBFT = make -C ./libft

NAME = minishell


LIBFT_PATH = ./libft

LIBFT_A = libft/libft.a

RD_FLAGS = -lreadline

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_A) $(RD_FLAGS)

lib :
	$(LIBFT)

%.o: %.c lib
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C $(LIBFT_PATH)
	rm -rf $(OBJS)

fclean: clean
	make fclean -C $(LIBFT_PATH)
	rm -rf $(NAME)

re: fclean all

.PHONY: clean