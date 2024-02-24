/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 20:09:04 by tamehri           #+#    #+#             */
/*   Updated: 2024/02/23 20:36:46 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/philos.h"

int	are_digits(char *s)
{
	int	i;

	i = 0;
	while (*(s + i))
	{
		if (*(s + i) <= '0' && *(s + i) >= '9')
			return (0);
		i++;
	}
	return (1);
}

void	exit_error_code(char *s)
{
	(putendl_fd(s, 2), exit(EXIT_FAILURE));
}

void	putendl_fd(char *s, int fd)
{
	if (!s || fd < 0)
		return ;
	while (*s)
		write(fd, s++, 1);
	write(fd, "\n", 1);
}
