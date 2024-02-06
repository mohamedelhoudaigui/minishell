/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 02:25:44 by mel-houd          #+#    #+#             */
/*   Updated: 2024/02/06 17:37:55 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/execution.h"
#include "./inc/parse.h"

int	g_exit_status;

void	reset_fd(int o_stdin, int o_stdout)
{
	dup2(o_stdin, 0);
	dup2(o_stdout, 1);
	close(o_stdin);
	close(o_stdout);
}

int	get_shell_lvl(char *cont)
{
	int		i;
	char	*num;

	i = 0;
	while (cont[i] != '=')
		i++;
	i++;
	num = ft_strdup(&cont[i]);
	i = ft_atoi(num);
	free(num);
	return (i);
}

void	set_shell_lvl(t_list *node, int lvl)
{
	char	*num;
	char	*new_cont;

	lvl++;
	num = ft_itoa(lvl);
	new_cont = ft_strjoin("SHLVL=", num);
	free(num);
	free(node->content);
	node->content = new_cont;
}

void	incr_shell_lvl(t_list **env_adr)
{
	t_list	*node;
	int		lvl;
	char	*cont;

	node = ft_lstfind_str(env_adr, "SHLVL=");
	if (node == NULL)
		return ;
	else
	{
		cont = node->content;
		lvl = get_shell_lvl(cont);
		set_shell_lvl(node, lvl);
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
	return (g_exit_status);
}
