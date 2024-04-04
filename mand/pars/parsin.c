/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 20:29:36 by tamehri           #+#    #+#             */
/*   Updated: 2024/04/04 14:36:02 by tamehri          ###   ########.fr       */
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
		table->meals_number = ft_atoi(*(av + 4));
		if (table->meals_number == -1 || table->meals_number == 0)
			return (quit(ERR_ARG_FORMAT));
		table->end_simulation = 1;
	}
	else
	{
		table->meals_number = -1;
		table->end_simulation = 0;
	}
	return (0);
}
