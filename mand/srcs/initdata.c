/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initdata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:58:21 by tamehri           #+#    #+#             */
/*   Updated: 2024/02/26 18:05:47 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	assign_forks(t_philos *philos, t_table *table, int i)
{
	philos->left_fork = table->forks + i;
	if (i == table->philos_n - 1)
		philos->right_fork = table->forks;
	else
		philos->right_fork = table->forks + i + 1;
}

int	init_philos(t_table *table)
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
		assign_forks(philos, table, i);
	}
	return (0);
}

int	init_mutex(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->forks_n)
	{
		// printf("fork %3d was put on the table\n", i + 1);
		if (-1 == pthread_mutex_init(&table->forks[i].fork, NULL))
			return (quit(ERR_MUTEX_INIT));
		table->forks[i].fork_id = i + 1;
	}
	return (0);
}

int	init_data(t_table *table)
{
	table->philos = malloc(sizeof(t_philos) * table->philos_n);
	if (!table->philos)
		return (quit(ERR_MAL));
	table->forks = malloc(sizeof(t_fork) * table->forks_n);
	if (!table->philos)
		return (quit(ERR_MAL));
	init_mutex(table);
	init_philos(table);
	return (0);
}
