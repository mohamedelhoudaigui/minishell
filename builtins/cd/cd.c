/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:26:41 by mel-houd          #+#    #+#             */
/*   Updated: 2024/01/17 18:12:12 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	change_old_pwd(t_list **env_var)
{
	t_list	*pwd;
	t_list	*old_pwd;
	char	*pwd_path;

	pwd = ft_lstfind_str(env_var, "PWD=");
	old_pwd = ft_lstfind_str(env_var, "OLDPWD=");
	if (!pwd || !old_pwd)
		return (1);
	pwd_path = ft_strjoin("OLDPWD=", &pwd->content[4]);
	free(old_pwd->content);
	old_pwd->content = pwd_path;
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

// int	change_cwd_env(t_list **env_var, char *path)
// {
// 	char	*new_path;

// 	if (ft_strncmp(path, ".", ft_strlen(path)) == 0)
// 		return (0);
	
// 	return (1);
// }

int	cd(t_list **env_adr, t_list *args)
{
	char	*path;
	t_list	*env_var;
	// char	*r_path;

	if (!args || args->content == NULL)
		return (1);
	env_var = *env_adr;
	path = args->content;
	if (access(path, F_OK) == 0)
	{
		if (change_old_pwd(env_adr) == 1)
			return (1);
		// change_cwd_env(&env_var, path);
		chdir(path);
		printf("%s\n", path);
		system("ls");
		return (0);
	}
	return (0);
}