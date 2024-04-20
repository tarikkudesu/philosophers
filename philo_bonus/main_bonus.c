/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:58:48 by tamehri           #+#    #+#             */
/*   Updated: 2024/04/20 11:17:15 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos_bonus.h"

static void	clean_table(t_table *table)
{
	long	i;

	i = -1;
	while (++i < table->philos_n)
	{
		sem_close((table->philos + i)->philo_s);
		sem_unlink((table->philos + i)->sem_name);
		free((table->philos + i)->sem_name);
	}
	sem_close(table->print_s);
	sem_unlink("/print_sem");
	sem_close(table->fork_s);
	sem_unlink("/forks_sem");
	sem_close(table->full_s);
	sem_unlink("/full_sem");
	sem_close(table->end_simu_s);
	sem_unlink("/end_simu_sem");
	free(table->philos);
	table->philos = NULL;
}

static void	*full_checker(void *param)
{
	long	i;
	t_table	*table;

	i = -1;
	table = (t_table *)param;
	while (++i < table->philos_n)
		sem_wait(table->full_s);
	sem_post(table->end_simu_s);
	return (NULL);
}

static void	kill_them(t_table *table, long pnumber)
{
	long	i;

	i = -1;
	while (++i < pnumber)
	{
		sem_post(table->full_s);
		kill((table->philos + i)->pid, SIGKILL);
	}
}

static int	dinner_served(t_table *table)
{
	long		i;
	pthread_t	tid;

	i = -1;
	if (1 == table->philos_n)
		return (one_philo(table));
	table->simu_start_time = get_current_time();
	while (++i < table->philos_n)
	{
		(table->philos + i)->pid = fork();
		if (-1 == (table->philos + i)->pid)
			return (kill_them(table, i + 1), quit(ERROR_FORK));
		if (0 == (table->philos + i)->pid)
			routine(table->philos + i);
	}
	if (0 != pthread_create(&tid, NULL, &full_checker, table))
		return (kill_them(table, table->philos_n), quit(PTHREAD_CREATE));
	pthread_detach(tid);
	sem_wait(table->end_simu_s);
	kill_them(table, table->philos_n);
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
