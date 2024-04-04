/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:19:00 by tamehri           #+#    #+#             */
/*   Updated: 2024/04/04 19:58:41 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

// void	print_status_d(t_philos *philo, char *status, size_t time)
// {
// 	long	time_stamp;

// 	pthread_mutex_lock(&philo->table->print_m);
// 	time_stamp = time - l_mutex_read(&philo->table->table_m, \
// 		&philo->table->simulation_start_time);
// 	printf("%ld\t%d\t%s\n", time_stamp, philo->tid, status);
// 	pthread_mutex_unlock(&philo->table->print_m);
// }

void	eat(t_philos *philo)
{
	print_status(philo, ST_EAT, get_current_time());
	ft_usleep(philo->table->t_eat);
	l_mutex_read_and_write(&philo->philo_m, &philo->meals_eaten, philo->meals_eaten + 1);
	l_mutex_read_and_write(&philo->philo_m, &philo->last_meal_time, get_current_time());
}

void	synchronise(t_table *table, t_philos *philo)
{
	l_mutex_read_and_write(&philo->philo_m, &philo->last_meal_time, get_current_time());
	while (b_mutex_read(&table->table_m, &table->ready) == false)
		;
}

void    *routine(void *param)
{
	t_philos    *philo;

	philo = (t_philos *)param;
	synchronise(philo->table, philo);
	if (philo->tid % 2 == 0)
		ft_usleep(philo->table->t_eat);
	b_mutex_read_and_write(&philo->philo_m, &philo->all_in, true);
	l_mutex_read_and_write(&philo->philo_m, &philo->last_meal_time, l_mutex_read(&philo->table->table_m, &philo->table->simulation_start_time));
	while (b_mutex_read(&philo->table->table_m, &philo->table->end_simulation) == false)
	{
		pthread_mutex_lock(&philo->left_fork->fork_m);
		print_status(philo, ST_FORK, get_current_time());
		pthread_mutex_lock(&philo->right_fork->fork_m);
		print_status(philo, ST_FORK, get_current_time());
		eat(philo);
		pthread_mutex_unlock(&philo->right_fork->fork_m);
		pthread_mutex_unlock(&philo->left_fork->fork_m);
		print_status(philo, ST_SLEEP, get_current_time());
		ft_usleep(philo->table->t_sleep);
		print_status(philo, ST_THINK, get_current_time());
	}
	b_mutex_read_and_write(&philo->philo_m, &philo->all_out, true);
	return (NULL);
}

int dinner_served(t_table *table)
{
	pthread_t	monitor_t;
	long 		i;

	i = -1;
	table->simulation_start_time = get_current_time();
	while (++i < table->philos_n)
	{
		if (0 != pthread_create(&table->philos[i].thread_id, \
			NULL, &routine, &table->philos[i]))
			return (quit(ERR_THREAD_CREATE));
		pthread_detach(table->philos[i].thread_id);
	}
	b_mutex_read_and_write(&table->table_m, &table->ready, true);
	if (0 != pthread_create(&monitor_t, NULL, &monitor, table))
		return (quit(ERR_THREAD_CREATE));
	if (0 != pthread_join(monitor_t, NULL))
		return (quit(ERR_THREAD_JOIN));
	return (0);
}
