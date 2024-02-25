/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 20:29:36 by tamehri           #+#    #+#             */
/*   Updated: 2024/02/24 12:30:32 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/philos.h"

int	parsing(t_philos *table, char **av)
{
	table->philos = ft_atoi(*(av + 0));
	table->t_die = ft_atoi(*(av + 1));
	table->t_eat = ft_atoi(*(av + 2));
	table->t_sleep = ft_atoi(*(av + 3));
	table->forks = table->philos;
	if (*(av + 4))
	{
		table->num_eat = ft_atoi(*(av + 4));
		if (table->num_eat == -1)
			return (quit(ERR_ARG_FORMAT));
		table->stop = 1;
	}
	else
	{
		table->num_eat = -1;
		table->stop = 0;
	}
	if (table->philos < 1 || table->philos > 200 || table->t_die < 0 \
		|| table->t_eat < 0 || table->t_sleep < 0)
		return (quit(ERR_ARG_FORMAT));
	return (0);
}
