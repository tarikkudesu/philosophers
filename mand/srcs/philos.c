/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:58:48 by tamehri           #+#    #+#             */
/*   Updated: 2024/04/04 18:31:22 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

static int	all_finished_execution(t_table *table)
{
	long	i;

	while (1)
	{
		i = 0;
		while (b_mutex_read(&table->philos[i].philo_m, \
			&table->philos[i].all_out) == true && i < table->philos_n)
			i++;
		if (i == table->philos_n)
			break ;
	}
	return (1);
}

static int	clean_table(t_table *table)
{
	long	i;

	i = -1;
	while (++i < table->philos_n)
	{
		if (0 != pthread_mutex_destroy(&table->forks[i].fork_m))
			return (quit(ERR_MUTEX_DESTROY));
		if (0 != pthread_mutex_destroy(&table->philos[i].philo_m))
			return (quit(ERR_MUTEX_DESTROY));
	}
	if (0 != pthread_mutex_destroy(&table->print_m))
		return (quit(ERR_MUTEX_DESTROY));
	if (0 != pthread_mutex_destroy(&table->table_m))
		return (quit(ERR_MUTEX_DESTROY));
	free(table->philos);
	free(table->forks);
	return (0);
}

void f() {system("leaks philo");}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac != 5 && ac != 6)
		return (quit(ERR_ARG_NUM));
	if (-1 == parsing(&table, av + 1))
		return (quit(NULL));
	if (fill_table(&table))
		return (1);
	dinner_served(&table);
	if (all_finished_execution(&table))
		clean_table(&table);
}
