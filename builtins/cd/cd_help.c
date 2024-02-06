/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:54:03 by mel-houd          #+#    #+#             */
/*   Updated: 2024/02/06 17:38:04 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

int	change_old_pwd(t_list **env_var)
{
	t_list	*pwd;

	pwd = ft_lstfind_str(env_var, "PWD=");
	if (!pwd)
		return (1);
	update_env_var(env_var, "OLDPWD=", &pwd->content[4]);
	return (0);
}

char	*change_to_var(t_list **env_adr, char *var_name)
{
	t_list	*var;
	char	*new_path;

	var = ft_lstfind_str(env_adr, var_name);
	if (!var)
		return (NULL);
	new_path = ft_strdup(&var->content[ft_strlen(var_name)]);
	if (!new_path)
		return (NULL);
	return (new_path);
}

int	change_cwd_env(t_list **env_var, char *path)
{
	update_env_var(env_var, "PWD=", path);
	return (0);
}

char	*handle_path_cases(t_list **env_adr, char **path_d)
{
	char	*path;

	path = *path_d;
	if (path == NULL)
		path = change_to_var(env_adr, "HOME=");
	if (path == NULL)
	{
		ft_putstr_fd("cd : HOME not set\n", 2);
		g_exit_status = 1;
	}
	return (path);
}
