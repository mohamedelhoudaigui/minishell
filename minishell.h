/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:31:28 by mel-houd          #+#    #+#             */
/*   Updated: 2024/01/21 13:38:16 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <paths.h>
# include <string.h>
# include <termios.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include "./libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>



typedef struct s_garbg
{
    void            *ptr;
    struct s_garbg    *next;
}    t_garbg;

typedef struct s_commands
{
	char				**command;
	int					in;
	int					out;
	struct s_commands	*next;
}				t_commands ;

// testing :
t_commands	*create_args(int ac, char **av, int in, int out);

//execve :
int		execute_command(t_list *env_var, t_commands *args);
char	**morph_env(t_list *env_var);
//here_doc :
int	here_doc(t_commands *args);

//execution :
int	execution(t_list **env_adr, t_commands *args);
int	redirect_command(t_list **env, t_commands *args);
int	ft_command_size(t_commands *args);


//redirect :
void	redirect_out(int out);
void	redirect_in(int in);

//garbage : 
void    clear_garbage(t_garbg *head);
void    *garbage(int size, int len, int status);

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
int	pwd(void);

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

//export :
void	print_export(t_list *env_var);
int		calculate_to(char *var);
int		handle_flag(char *arg);
char	*get_key(char *arg);
char	*get_value(char *arg);
int		export(t_list **env_var, t_commands *args);

#endif