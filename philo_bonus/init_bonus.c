/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:58:21 by tamehri           #+#    #+#             */
/*   Updated: 2024/04/20 10:56:48 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos_bonus.h"

static int	init_semaphores(t_table *table)
{
	sem_unlink("/print_sem");
	table->print_s = sem_open("/print_sem", O_CREAT, 0644, 1);
	if (table->print_s == SEM_FAILED)
		return (quit(SEM_OPEN));
	sem_unlink("/forks_sem");
	table->fork_s = sem_open("/forks_sem", O_CREAT, 0644, table->philos_n);
	if (table->fork_s == SEM_FAILED)
		return (quit(SEM_OPEN));
	sem_unlink("/full_sem");
	table->full_s = sem_open("/full_sem", O_CREAT, 0644, 0);
	if (table->full_s == SEM_FAILED)
		return (quit(SEM_OPEN));
	sem_unlink("/end_simu_sem");
	table->end_simu_s = sem_open("/end_simu_sem", O_CREAT, 0644, 0);
	if (table->end_simu_s == SEM_FAILED)
		return (quit(SEM_OPEN));
	return (0);
}

static int	init_philos(t_table *table)
{
	long		i;
	char		*tmp;
	t_philos	*philos;

	i = -1;
	while (++i < table->philos_n)
	{
		philos = table->philos + i;
		philos->table = table;
		philos->philo_id = i + 1;
		philos->meals_eaten = 0;
		tmp = ft_itoa(i * 10000);
		if (!tmp)
			return (quit(ERROR_MAL));
		philos->sem_name = ft_strjoin("/sem", tmp);
		free(tmp);
		if (!philos->sem_name)
			return (quit(ERROR_MAL));
		philos->dead = false;
		sem_unlink(philos->sem_name);
		philos->philo_s = sem_open(philos->sem_name, O_CREAT, 0644, 1);
		if (philos->philo_s == SEM_FAILED)
			return (quit(SEM_OPEN));
	}
	return (0);
}

int	fill_table(t_table *table)
{
	table->philos = malloc(sizeof(t_philos) * table->philos_n);
	if (!table->philos)
		return (quit(ERROR_MAL));
	if (-1 == init_philos(table))
		return (quit(-1));
	if (-1 == init_semaphores(table))
		return (quit(-1));
	return (0);
}
