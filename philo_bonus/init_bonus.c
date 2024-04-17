/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:58:21 by tamehri           #+#    #+#             */
/*   Updated: 2024/04/15 10:03:10 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos_bonus.h"

static int	init_semaphores(t_table *table)
{
	sem_unlink("print_sem");
	table->print_s = sem_open("print_sem", O_CREAT, 0644, 1);
	if (table->print_s == SEM_FAILED)
		return (quit(SEM_OPEN));

	sem_unlink("start_sem");
	table->start_s = sem_open("start_sem", O_CREAT, 0644, 0);
	if (table->start_s == SEM_FAILED)
		return (quit(SEM_OPEN));

	sem_unlink("forks_sem");
	table->fork_s = sem_open("forks_sem", O_CREAT, 0644, table->philos_n);
	if (table->fork_s == SEM_FAILED)
		return (quit(SEM_OPEN));

	return (0);
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
		philos->philo_id = i + 1;
		philos->meals_eaten = 0;
		philos->full = false;
		/* assign_forks(table->philos + i, i); */
	}
}

int	fill_table(t_table *table)
{
	table->ready = false;
	table->end_simu = false;
	table->start_monitor = 0;
	table->philos = NULL;
	table->philos = malloc(sizeof(t_philos) * table->philos_n);
	if (!table->philos)
		return (quit(ERROR_MAL));
	/* table->forks = malloc(sizeof(t_fork) * table->philos_n); */
	/* if (!table->philos) */
	/* 	return (free(table->philos), quit(ERROR_MAL)); */
	init_philos(table);
	init_semaphores(table);
	return (0);
}
