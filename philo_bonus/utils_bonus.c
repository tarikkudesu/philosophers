/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:51:26 by tamehri           #+#    #+#             */
/*   Updated: 2024/05/18 14:31:11 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos_bonus.h"

static long	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (*(str + i))
		i++;
	return (i);
}

char	*fill_strs(char const *s1, char const *s2, char **res)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1)
	{
		i = -1;
		while (*(s1 + ++i))
			*(*res + i) = *(s1 + i);
	}
	if (s2)
	{
		j = 0;
		while (*(s2 + j))
			*(*res + i++) = *(s2 + j++);
	}
	*(*res + i) = '\0';
	return (*res);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		l1;
	int		l2;
	char	*res;

	l1 = 0;
	l2 = 0;
	if (!s1 && !s2)
		return (NULL);
	if (s1)
		l1 = ft_strlen(s1);
	if (s2)
		l2 = ft_strlen(s2);
	res = malloc((l1 + l2 + 1) * sizeof(char));
	if (!res)
		return (NULL);
	return (fill_strs(s1, s2, &res));
}
