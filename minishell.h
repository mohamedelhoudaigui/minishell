/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:31:28 by mel-houd          #+#    #+#             */
/*   Updated: 2024/01/19 23:57:28 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdarg.h>
# include <stdbool.h>

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

//redirect :
void	redirect_out(int out);
void	redirect_in(int in);

//garbage : 
void    clear_garbage(t_garbg *head);
void    *garbage(int size, int len, int status);

//linked list:
t_commands	*ft_new_command(char **commands, int in, int out);
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
void    exit_b(t_commands *command, t_list **env_var, t_commands **args);

//env :
int	env_b(t_list *env_var, t_commands *args);

//unset :
int	unset(t_list **env_vars, t_commands *args);

//export :
void	print_export(t_list *env_var);
int		export(t_list **env_var, t_commands *args);

#endif