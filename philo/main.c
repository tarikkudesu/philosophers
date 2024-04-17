/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:58:48 by tamehri           #+#    #+#             */
/*   Updated: 2024/04/17 09:50:11 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

static int	clean_table(t_table *table)
{
	long	i;

	i = -1;
	while (++i < table->philos_n)
	{
		if (0 != pthread_mutex_destroy(&table->forks[i].fork_m))
			return (quit(PTHREAD_MUTEX_DESTROY));
		if (0 != pthread_mutex_destroy(&table->philos[i].philo_m))
			return (quit(PTHREAD_MUTEX_DESTROY));
	}
	if (0 != pthread_mutex_destroy(&table->print_m))
		return (quit(PTHREAD_MUTEX_DESTROY));
	if (0 != pthread_mutex_destroy(&table->table_m))
		return (quit(PTHREAD_MUTEX_DESTROY));
	return (0);
}

int	dinner_served(t_table *table)
{
	long	i;

	i = -1;
	if (table->philos_n == 1)
		return (single_philo(table));
	while (++i < table->philos_n)
	{
		if (0 != pthread_create(&table->philos[i].thread_id, \
			NULL, &have_dinner, &table->philos[i]))
			return (quit(PTHREAD_CREATE));
	}
	table->simu_start_time = get_current_time();
	wb_mutex(&table->table_m, &table->ready, true);
	monitor(table);
	i = -1;
	while (++i < table->philos_n)
	{
		if (0 != pthread_join(table->philos[i].thread_id, NULL))
			return (quit(PTHREAD_CREATE));
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac != 5 && ac != 6)
		return (quit(ERROR_ARGS));
	if (-1 == parsing(&table, av + 1))
		return (1);
	if (-1 == fill_table(&table))
		return (1);
	dinner_served(&table);
	clean_table(&table);
}
