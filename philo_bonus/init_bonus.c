/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:58:21 by tamehri           #+#    #+#             */
/*   Updated: 2024/04/24 14:46:02 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos_bonus.h"

static int	init_semaphores(t_table *table)
{
	sem_unlink("/print_s");
	table->print_s = sem_open("/print_s", O_CREAT, 0644, 1);
	if (table->print_s == SEM_FAILED)
		return (_error(SEM_OPEN));
	sem_unlink("/forks_s");
	table->fork_s = sem_open("/forks_s", O_CREAT, 0644, table->philos_n);
	if (table->fork_s == SEM_FAILED)
		return (_error(SEM_OPEN));
	sem_unlink("/full_s");
	table->full_s = sem_open("/full_s", O_CREAT, 0644, 0);
	if (table->full_s == SEM_FAILED)
		return (_error(SEM_OPEN));
	sem_unlink("/end_simu_s");
	table->end_simu_s = sem_open("/end_simu_s", O_CREAT, 0644, 0);
	if (table->end_simu_s == SEM_FAILED)
		return (_error(SEM_OPEN));
	return (0);
}

static int	init_philos(t_table *table)
{
	t_philos	*philo;
	char		*tmp;
	int			i;

	i = -1;
	while (++i < table->philos_n)
	{
		philo = table->philos + i;
		philo->table = table;
		philo->philo_id = i + 1;
		philo->dead = false;
		philo->sem_name = NULL;
		tmp = ft_itoa((i + 1) * 100);
		if (!tmp)
			return (_error(ERROR_MAL));
		philo->sem_name = ft_strjoin("/sem", tmp);
		free(tmp);
		if (!philo->sem_name)
			return (_error(ERROR_MAL));
		sem_unlink(philo->sem_name);
		philo->philo_s = sem_open(philo->sem_name, O_CREAT, 0644, 1);
		if (philo->philo_s == SEM_FAILED)
			return (_error(SEM_OPEN));
	}
	return (0);
}

int	fill_table(t_table *table)
{
	table->philos = malloc(sizeof(t_philos) * table->philos_n);
	if (!table->philos)
		return (_error(ERROR_MAL));
	if (-1 == init_philos(table))
		return (_error(-1));
	if (-1 == init_semaphores(table))
		return (_error(-1));
	return (0);
}
