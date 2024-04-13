/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initia.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:58:21 by tamehri           #+#    #+#             */
/*   Updated: 2024/04/13 15:30:01 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

static void	assign_forks(t_philos *philo, int i)
{
	philo->left_fork = philo->table->forks + i;
	if (i == philo->table->philos_n - 1)
		philo->right_fork = philo->table->forks;
	else
		philo->right_fork = philo->table->forks + i + 1;
}

static void	init_philos(t_table *table)
{
	long		i;
	t_philos	*philos;

	i = -1;
	while (++i < table->philos_n)
	{
		philos = table->philos + i;
		philos->table = table;
		philos->tid = i + 1;
		philos->meals_eaten = 0;
		philos->full = false;
		philos->out = false;
		philos->in = false;
		assign_forks(table->philos + i, i);
	}
}

static int	init_mutex(t_table *table)
{
	long	i;

	i = -1;
	if (0 != pthread_mutex_init(&table->print_m, NULL))
		return (quit(PTHREAD_MUTEX_INIT));
	if (0 != pthread_mutex_init(&table->table_m, NULL))
		return (quit(PTHREAD_MUTEX_INIT));
	while (++i < table->forks_n)
	{
		if (0 != pthread_mutex_init(&table->philos[i].philo_m, NULL))
			return (quit(PTHREAD_MUTEX_INIT));
		if (0 != pthread_mutex_init(&table->forks[i].fork_m, NULL))
			return (quit(PTHREAD_MUTEX_INIT));
		table->forks[i].fork_id = i + 1;
	}
	return (0);
}

int	fill_table(t_table *table)
{
	table->dead = false;
	table->ready = false;
	table->end_simu = false;
	table->start_monitor = 0;
	table->philos = NULL;
	table->forks = NULL;
	table->philos = malloc(sizeof(t_philos) * table->philos_n);
	if (!table->philos)
		return (quit(ERROR_MAL));
	table->forks = malloc(sizeof(t_fork) * table->forks_n);
	if (!table->philos)
		return (free(table->philos), quit(ERROR_MAL));
	if (-1 == init_mutex(table))
		return (-1);
	init_philos(table);
	return (0);
}
