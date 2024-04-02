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

int	parsing(t_table *table, char **av)
{
	table->philos_n = ft_atoi(*(av + 0));
	table->t_die = ft_atoi(*(av + 1));
	table->t_eat = ft_atoi(*(av + 2));
	table->t_sleep = ft_atoi(*(av + 3));
	if (table->t_die < 60 || table->t_eat < 60 || table->t_sleep < 60)
		return (quit(ERR_TIME));
	if (table->philos_n < 1 || table->philos_n > 200)
		return (quit(ERR_ARG_FORMAT));
	table->forks_n = table->philos_n;
	if (*(av + 4))
	{
		table->num_eat = ft_atoi(*(av + 4));
		if (table->num_eat == -1 || table->num_eat == 0)
			return (quit(ERR_ARG_FORMAT));
		table->stop = 1;
	}
	else
	{
		table->num_eat = -1;
		table->stop = 0;
	}
	return (0);
}
