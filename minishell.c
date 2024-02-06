/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 02:25:44 by mel-houd          #+#    #+#             */
/*   Updated: 2024/02/05 14:09:09 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/execution.h"
#include "./inc/parse.h"

int exit_status;

void	reset_fd(int o_stdin, int o_stdout)
{
	dup2(o_stdin, 0);
	dup2(o_stdout, 1);
	close(o_stdin);
	close(o_stdout);
}

void	incr_shell_lvl(t_list **env_adr)
{
	t_list	*node;
	char	*num;
	int		i;
	char	*cont;
	char	*new_cont;

	node =ft_lstfind_str(env_adr, "SHLVL=");
	if (node == NULL)
		return ;
	else
	{
		cont = node->content;
		i = 0;
		while (cont[i] != '=')
			i++;
		i++;
		num = ft_strdup(&cont[i]);
		i = ft_atoi(num);
		free(num);
		i++;
		num = ft_itoa(i);
		new_cont = ft_strjoin("SHLVL=", num);
		free(num);
		free(node->content);
		node->content = new_cont;
	}
}

int	main(int ac, char **av, char **env)
{
	t_list		*env_var;

	(void)ac;
	(void)av;
	env_var = get_env_var(env);
	
	incr_shell_lvl(&env_var);
	main_loop(&env_var);
	return (exit_status);
}
