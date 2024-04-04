/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initia.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:58:21 by tamehri           #+#    #+#             */
/*   Updated: 2024/04/04 18:36:29 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

static void	assign_forks(t_philos *philos, t_table *table, int i)
{
	philos->left_fork = table->forks + i;
	if (i == table->philos_n - 1)
		philos->right_fork = table->forks;
	else
		philos->right_fork = table->forks + i + 1;
}

static int	init_philos(t_table *table)
{
	int			i;
	t_philos	*philos;

	i = -1;
	while (++i < table->philos_n)
	{
		philos = table->philos + i;
		philos->table = table;
		philos->tid = i + 1;
		philos->meals_eaten = 0;
		philos->full = false;
		philos->all_out = false;
		assign_forks(philos, table, i);
	}
	return (0);
}

static int	init_mutex(t_table *table)
{
	int	i;

	i = -1;
	if (0 != pthread_mutex_init(&table->print_m, NULL))
		return (quit(ERR_MUTEX_INIT));
	if (0 != pthread_mutex_init(&table->table_m, NULL))
		return (quit(ERR_MUTEX_INIT));
	while (++i < table->forks_n)
	{
		if (0 != pthread_mutex_init(&table->philos[i].philo_m, NULL))
			return (quit(ERR_MUTEX_INIT));
		if (0 != pthread_mutex_init(&table->forks[i].fork_m, NULL))
			return (quit(ERR_MUTEX_INIT));
		table->forks[i].fork_id = i + 1;
	}
	return (0);
}

int	fill_table(t_table *table)
{
	table->ready = false;
	table->end_simulation = false;
	table->philos = malloc(sizeof(t_philos) * table->philos_n);
	if (!table->philos)
		return (quit(ERR_MAL));
	table->forks = malloc(sizeof(t_fork) * table->forks_n);
	if (!table->philos)
		return (free(table->philos), quit(ERR_MAL));
	if (-1 == init_mutex(table))
		return (free(table->forks), free(table->philos), -1);
	init_philos(table);
	return (0);
}
