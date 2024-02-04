/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:31:28 by mel-houd          #+#    #+#             */
/*   Updated: 2024/02/04 20:40:16 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../libft/libft.h"
# include "./parse.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <paths.h>
# include <string.h>
# include <termios.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <errno.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>

extern int exit_status;

// typedef struct s_redir
// {
//   int					type;
//   char					*file;
//   struct s_redir		*next;
//   bool					flage;
//   }						t_redir;

typedef struct s_commands
{
	char				**command;
	int					in;
	int					out;
	struct s_commands	*next;
}				t_commands ;

// typedef struct s_parsing
// {
// 	char				**command;
// 	t_redir				*in_fd;
// 	t_redir				*out_fd;
// 	struct s_parsing	*next;
// }				t_parsing ;

// testing :
t_commands	*create_args(int ac, char **av, int in, int out);

// merging // opening fd : 
t_commands	*open_fd(t_cmd	*commands, t_list **env_adr);
char		**alloc_commands(char **com_args);
void		command_add_back(t_commands **head, t_commands *node);
int			handle_out_files(t_redir	*out_file);
int			handle_in_files(t_redir	*in_file, t_list **env_adr);
void		close_all_fd(t_commands *args);
void		reset_fd(int o_stdin, int o_stdout);

// 0 == > O_TRUNC | O_CREAT
// 1 == >> O_APPEND | O_CREAT
// 2 == < O_RDONLY
// 3 == << heredoc

//expander :
char    *expande_var(t_list **env_var, char *var);

//execve :
int		execute_command(t_list *env_var, t_commands *args);
char	**morph_env(t_list *env_var);

//here_doc :
int	here_doc(char *delimiter, t_list **env_adr, bool flag);

//execution :
int	execution(t_list **env_adr, t_commands *args);
int	redirect_command(t_list **env, t_commands *args);
int	ft_command_size(t_commands *args);
char	**morph_env(t_list *env_var);
char	**morph_args(t_commands *args);


//redirect :
void	redirect_out(int out);
void	redirect_in(int in);


//linked list:
t_commands	*ft_new_command(int in, int out);
t_commands	*get_last_command(t_commands **head);
void		ft_add_command(t_commands **head, t_commands *node);
void		ft_clear_commands(t_commands **head);

// env_vars : 
t_list	*get_env_var(char **env);
void	update_env_var(t_list **head, char *env_var_name ,char *arg);
void	create_env_var(t_list **head, char *env_var_name, char *arg);
void	remove_env_var(t_list **head, t_list **node);
void	add_env_var(t_list **env_var, char *var_value);
void	join_env_var(t_list **env_var, char *var_name ,char *var_to_join);

// echo :
int		echo(t_commands *command);
bool		check_flag(char *flag);
void	call_expander(char *str);

// pwd :
int	pwd(t_commands *args);

//cd :
int		cd(t_list **env_adr, t_commands *args);
int		change_cwd_env(t_list **env_var, char *path);
char	*change_to_var(t_list **env_adr, char *var_name);
int		change_old_pwd(t_list **env_var);

//exit :
void    exit_b(t_commands *command, t_list **env_var);

//env :
int	env_b(t_list *env_var, t_commands *args);

//unset :
int	unset(t_list **env_vars, t_commands *args);
int	parse_varname_unset(char *arg);

//export :
void	print_export(t_list *env_var);
int		calculate_to(char *var);
int		handle_flag(char *arg);
char	*get_key(char *arg);
char	*get_value(char *arg);
int		export(t_list **env_var, t_commands *args);
int		parse_varname(char *arg);

//pipes :
void	redirect_pipes(int i, int **pipes, int n_commands);
void	close_unused_pipes(int i, int **pipes, int n_commands);


#endif