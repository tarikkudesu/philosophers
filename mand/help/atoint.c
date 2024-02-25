/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 11:04:46 by tamehri           #+#    #+#             */
/*   Updated: 2024/02/24 12:05:35 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/philos.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	else if (c == '\r' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	long	res;
	int		sign;
	int		i;

	i = 0;
	sign = 1;
	res = 0;
	while (ft_isspace(*(str + i)))
		i++;
	if (*(str + i) == '-')
	{
		sign *= -1;
		i++;
	}
	else if (*(str + i) == '+')
		i++;
	while (*(str + i) && *(str + i) >= '0' && *(str + i) <= '9')
	{
		res = res * 10 + *(str + i) - '0';
		i++;
	}
	if (*(str + i) != '\0' || res > INT_MAX || res < INT_MIN)
		return (-1);
	return ((int)(res * sign));
}
