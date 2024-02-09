/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:40:59 by mel-houd          #+#    #+#             */
/*   Updated: 2024/02/08 20:04:23 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/execution.h"

char	*get_pwd(void)
{
	char	buffer[5000];

	getcwd(buffer, 5000);
	return (ft_strjoin("PWD=", buffer));
}

t_list	*give_empty_env(void)
{
	char	*pwd;
	char	*underscore;
	char	*shlvl;
	t_list	*head;
	t_list	*tmp;

	pwd = get_pwd();
	head = ft_lstnew(pwd);
	underscore = ft_strdup("_=/usr/bin/env");
	tmp = ft_lstnew(underscore);
	ft_lstadd_back(&head, tmp);
	shlvl = ft_strdup("SHLVL=1");
	tmp = ft_lstnew(shlvl);
	ft_lstadd_back(&head, tmp);
	return (head);
}

t_list	*get_env_var(char **env)
{
	int		i;
	t_list	*head;
	t_list	*node;

	if (!env || env[0] == NULL)
		return (give_empty_env());
	i = 0;
	head = ft_lstnew(ft_strdup(env[i]));
	if (env[1] == NULL)
		return (head);
	while (env[++i])
	{
		node = ft_lstnew(ft_strdup(env[i]));
		if (!node)
			return (NULL);
		ft_lstadd_back(&head, node);
	}
	return (head);
}

void	update_env_var(t_list **head, char *env_var_name, char *arg)
{
	t_list	*env_var;
	char	*new_arg;

	env_var = ft_lstfind_str(head, env_var_name);
	if (!env_var)
	{
		create_env_var(head, env_var_name, arg);
		return ;
	}
	free(env_var->content);
	new_arg = ft_strjoin(env_var_name, arg);
	if (!new_arg)
		return ;
	env_var->content = new_arg;
}

void	join_env_var(t_list **env_var, char *var_name, char *var_to_join)
{
	t_list	*node;
	char	*new_var;

	node = ft_lstfind_str(env_var, var_name);
	if (!node)
	{
		create_env_var(env_var, var_name, var_to_join);
		return ;
	}
	new_var = ft_strjoin(node->content, var_to_join);
	if (!new_var)
		return ;
	free(node->content);
	node->content = new_var;
}
