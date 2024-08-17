SRCS = ./builtins/echo/echo.c ./builtins/pwd/pwd.c env_vars.c minishell.c \
        ./builtins/cd/cd.c ./linked_list/ft_command.c ./builtins/exit/exit.c \
        ./builtins/env/env.c ./builtins/unset/unset.c redirect.c ./builtins/export/export.c \
        ./builtins/export/export_help.c ./entry_point/execution.c ./entry_point/execute_command.c \
        ./entry_point/exec_utils.c ./entry_point/handle_pipes.c ./expander/expander.c \
        ./open_fd_layer/open_fd.c  ./heredoc/heredoc.c ./heredoc/heredoc_help.c ./parse/garbage.c ./parse/parser.c \
		./parse/utils.c ./parse/tokenizer.c ./linker.c ./open_fd_layer/open_fd_help.c ./signals/cmd_signal.c \
		./builtins/cd/cd_help.c ./builtins/export/export_help2.c env_vars2.c ./entry_point/execute_command_help.c \
		./entry_point/exec_help.c ./entry_point/exec_help2.c ./parse/syntax.c ./parse/parser_utils.c ./parse/exit_status.c ./parse/redir_utils.c \
		./parse/redirections.c ./parse/expansion.c ./parse/tokenizer_utils.c ./parse/str_manip.c ./parse/modded_func.c \
		./parse/errors.c ./parse/handle_token.c ./parse/handle_token_extras.c ./parse/redirections_extras.c

OBJS = $(SRCS:.c=.o)

CC = cc

READLINE_HEADER =  "-I/Users/mel-houd/.brew/opt/readline/include"

READLINE_LIB = "-L/Users/mel-houd/.brew/opt/readline/lib"


CFLAGS = $(READLINE_HEADER) 

LIBFT = make -C ./libft

NAME = minishell


LIBFT_PATH = ./libft

LIBFT_A = libft/libft.a


all: lib $(NAME)

$(NAME): $(OBJS)
	$(CC) -lreadline $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_A) $(READLINE_LIB)

lib :
	$(LIBFT)

%.o: %.c ./libft/libft.h ./inc/execution.h ./inc/macros.h ./inc/parse.h ./inc/garbage.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C $(LIBFT_PATH)
	rm -rf $(OBJS)

fclean: clean
	make fclean -C $(LIBFT_PATH)
	rm -rf $(NAME)

re: fclean all

.PHONY: clean lib
