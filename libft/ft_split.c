/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 21:54:26 by mel-houd          #+#    #+#             */
/*   Updated: 2024/01/16 01:27:50 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char *delimiters)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (s && s[i])
	{
		if (!ft_strchr(delimiters, s[i]))
		{
			res++;
			while (*s && !ft_strchr(delimiters, *s))
				s++;
		}
		else
			s++;
	}
	return (res);
}

static int	word_size(char const *s, char *delimiters, int i)
{
	int	res;

	res = 0;
	while (s[i] && !ft_strchr(delimiters, s[i]))
	{
		res++;
		i++;
	}
	return (res);
}

static void	memory_free(char **strings, int max_index)
{
	while (max_index >= 0)
		free(strings[max_index--]);
	free(strings);
}

static int	fill_string(char const *s,
		char *delimiters, char **res, int number_words)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	j = 0;
	while (j < number_words)
	{
		while (ft_strchr(delimiters, s[i]))
			i++;
		size = word_size(s, delimiters, i);
		res[j] = ft_substr(s, i, size);
		if (res[j] == NULL)
		{
			memory_free(res, j);
			return (1);
		}
		j++;
		i += size;
	}
	res[j] = NULL;
	return (0);
}

char	**ft_split(char const *s, char *delimiters)
{
	int		number_words;
	char	**res;

	number_words = count_words(s, delimiters);
	res = (char **)malloc(sizeof(char *) * (number_words + 1));
	if (!res || fill_string(s, delimiters, res, number_words))
		return (NULL);
	return (res);
}
