/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:19:00 by tamehri           #+#    #+#             */
/*   Updated: 2024/02/27 15:19:18 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	print_status(t_philos *philo, char *status, size_t time)
{
	pthread_mutex_lock(&philo->table->print_m);
	printf("%ld\t%d\t%s\n", time  - philo->table->simulation_start_time, philo->tid, status);
	pthread_mutex_unlock(&philo->table->print_m);
}

void	*monitor_f(void *param)
{
	t_table	*table;

	table = (t_table *)param;
	while (1)
	{
		ft_usleep(200);
		// puts("--------------------");
		for (long i = 0; i < table->philos_n; i++) {
			if (table->philos[i].meals_eaten == 10)
				return (NULL);
			// printf("philo %d -> %ld\n", table->philos[i].tid, table->philos[i].meals_eaten);
		}
		// puts("--------------------");
	}
	return (NULL);
}

void	eat(t_philos *philo)
{
	print_status(philo, ST_EAT, get_current_time());
	ft_usleep(philo->table->t_eat);
	philo->meals_eaten += 1;
	philo->last_meal_time = get_current_time();
}

void    *routine(void *param)
{
	t_philos    *philo;

	philo = (t_philos *)param;
	if (philo->tid % 2 == 0)
		ft_usleep(philo->table->t_eat);
	while (1)
	{
		pthread_mutex_lock(&philo->left_fork->fork_m);
		print_status(philo, ST_FORK, get_current_time());
		pthread_mutex_lock(&philo->right_fork->fork_m);
		print_status(philo, ST_FORK, get_current_time());
		eat(philo);
		pthread_mutex_unlock(&philo->left_fork->fork_m);
		pthread_mutex_unlock(&philo->right_fork->fork_m);
		print_status(philo, ST_SLEEP, get_current_time());
		ft_usleep(philo->table->t_sleep);
	}
	return (NULL);
}

int dinner_served(t_table *table)
{
	pthread_t	monitor;
	long 		i;

	i = -1;
	puts("starting");
	table->simulation_start_time = get_current_time();
	while (++i < table->philos_n)
	{
		if (-1 == pthread_create(&table->philos[i].thread_id, NULL, &routine, &table->philos[i]))
			return (quit(ERR_THREAD_CREATE));
		pthread_detach(table->philos[i].thread_id);
	}
	if (-1 == pthread_create(&monitor, NULL, &monitor_f, table))
		return (quit(ERR_THREAD_CREATE));
	pthread_join(monitor, NULL);
	return (0);
}
