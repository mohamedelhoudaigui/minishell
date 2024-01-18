/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:05:55 by mel-houd          #+#    #+#             */
/*   Updated: 2023/11/09 10:55:54 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_max(int sign, unsigned long long res)
{
	if (res > 9223372036854775807 && sign == 1)
	{
		res = -1;
		return ((int)res);
	}
	else if (res > 9223372036854775807 && sign == -1)
	{
		res = 0;
		return ((int)res);
	}
	return ((int)(res * sign));
}

int	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	res;
	int					sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -sign;
		i++;
	}
	while (str[i] && str[i] == '0')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		res = (str[i++] - '0') + (res * 10);
	return (check_max(sign, res));
}
