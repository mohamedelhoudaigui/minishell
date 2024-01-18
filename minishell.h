/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:31:28 by mel-houd          #+#    #+#             */
/*   Updated: 2024/01/18 13:12:30 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "./libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdarg.h>
# include <stdbool.h>

typedef struct s_env_var
{
	char				*key;
	char				*value;
	struct s_env_var	*next;
	struct s_env_var	*prev;
	struct s_env_var	*head;
	struct s_env_var	*tail;
}				t_env_var;

typedef struct s_commands
{
	char				**command;
	int					in;
	int					out;
	struct s_commands	*next;
}				t_commands ;

//linked list:
t_commands	*ft_new_command(char **commands, int in, int out);
t_commands	*get_last_command(t_commands **head);
void		ft_add_command(t_commands **head, t_commands *node);
void		ft_clear_commands(t_commands **head);
// env_vars : 
t_list	*get_env_var(char **env);

// expanding :
int	return_expande(char *dollar_var, t_list *env_var);

// echo :
int		echo(t_commands *command);
int		check_flag(char *flag);
void	call_expander(char *str);

// pwd :
int	pwd(void);

//cd :
int	cd(t_list **env_adr, t_list *args);

#endif