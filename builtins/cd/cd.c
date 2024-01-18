/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:26:41 by mel-houd          #+#    #+#             */
/*   Updated: 2024/01/18 16:51:57 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	change_old_pwd(t_list **env_var)
{
	t_list	*pwd;

	pwd = ft_lstfind_str(env_var, "PWD=");
	if (!pwd)
		return (1);
	update_env_var(env_var, "OLDPWD=", &pwd->content[4]);
	return (0);
}

// int	change_to_home(t_list **env_var)
// {
// 	t_list	*home;
// 	t_list	*pwd;
// 	t_list	*old_pwd;

// 	pwd = ft_lstfind_str(&env_var, "PWD=");
// 	home = ft_lstfind_str(&env_var, "HOME=");
// 	if (!pwd || !home)
// 		return (1);
// }

int	change_cwd_env(t_list **env_var, char *path)
{
	update_env_var(env_var, "PWD=", path);
	return (0);
}

int	cd(t_list **env_adr, t_commands *command)
{
	char	*path;
	t_list	*env_var;
	char	**args;
	
	args = command->command;
	env_var = *env_adr;
	path = args[1];
	if (access(path, F_OK) == 0)
	{
		change_old_pwd(env_adr);
		if (change_cwd_env(&env_var, path) == 1)
			return (1);
		if (chdir(path) == -1)
		{
			perror("chdir");
			return (1);
		}
		return (0);
	}
	else
	{
		perror("access");
		return (1);
	}
	return (0);
}