/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 20:29:36 by tamehri           #+#    #+#             */
/*   Updated: 2024/04/14 19:42:31 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	parsing(t_table *table, char **av)
{
	table->philos_n = ft_atoi(*(av + 0));
	table->t_die = ft_atoi(*(av + 1));
	table->t_eat = ft_atoi(*(av + 2));
	table->t_sleep = ft_atoi(*(av + 3));
	if (table->t_die < 60 || table->t_eat < 60 || table->t_sleep < 60)
		return (quit(ERROR_TIME));
	if (table->philos_n < 1 || table->philos_n > 200)
		return (quit(ERROR_FORMAT));
	if (*(av + 4))
	{
		table->meals_nbr = ft_atoi(*(av + 4));
		if (table->meals_nbr == -1 || table->meals_nbr == 0)
			return (quit(ERROR_FORMAT));
	}
	else
		table->meals_nbr = -1;
	return (0);
}
