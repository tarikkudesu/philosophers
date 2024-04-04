/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:19:00 by tamehri           #+#    #+#             */
/*   Updated: 2024/04/04 15:28:06 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	print_status(t_philos *philo, char *status, size_t time)
{
	long	time_stamp;

	pthread_mutex_lock(&philo->table->print_m);
	time_stamp = time - l_mutex_read(&philo->table->table_m, \
		&philo->table->simulation_start_time);
	printf("%ld\t%d\t%s\n", time_stamp, philo->tid, status);
	pthread_mutex_unlock(&philo->table->print_m);
}

void	*monitor_f(void *param)
{
	long	meals_number;
	t_table	*table;
	long	i;

	table = (t_table *)param;
	while (b_mutex_read(&table->table_m, &table->end_simulation) == false)
	{
		i = -1;
		while (++i < table->philos_n)
		{
			if (b_mutex_read(&table->philos[i].philo_m, &table->philos[i].dead) == true)
			{
				b_mutex_read_and_write(&table->table_m, &table->end_simulation, true);
				break;
			}
		}
		meals_number = l_mutex_read(&table->table_m, &table->meals_number);
		if (meals_number != -1)
		{
			i = -1;
			while (++i < table->philos_n)
				if (l_mutex_read(&table->philos[i].philo_m, &table->philos[i].meals_eaten) != meals_number)
					break ;
			if (i == table->philos_n)
				b_mutex_read_and_write(&table->table_m, &table->end_simulation, true);
		}
	}
	return (NULL);
}

void	eat(t_philos *philo)
{
	print_status(philo, ST_EAT, get_current_time());
	ft_usleep(philo->table->t_eat);
	l_mutex_read_and_write(&philo->philo_m, &philo->meals_eaten, philo->meals_eaten + 1);
	l_mutex_read_and_write(&philo->philo_m, &philo->last_meal_time, get_current_time());
}

void	synchronise(t_table *table)
{
	while (b_mutex_read(&table->table_m, &table->ready) == false)
		;
}

void    *routine(void *param)
{
	t_philos    *philo;

	philo = (t_philos *)param;
	synchronise(philo->table);
	if (philo->tid % 2 == 0)
		ft_usleep(philo->table->t_eat);
	while (b_mutex_read(&philo->table->table_m, &philo->table->end_simulation) == false)
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
	b_mutex_read_and_write(&philo->philo_m, &philo->out, true);
	return (NULL);
}

int	all_finished_execution(t_table *table)
{
	long	i;

	while (1)
	{
		i = 0;
		while (b_mutex_read(&table->philos[i].philo_m, &table->philos[i].out) == true)
			i++;
		if (i == table->philos_n)
			break ;
	}
	return (1);
}

int	destrroy_mutex(t_table *table)
{
	long	i;

	i = -1;
	while (++i < table->philos_n)
	{
		if (0 != pthread_mutex_destroy(&table->forks[i].fork_m))
			return (quit(ERR_MUTEX_DESTROY));
		if (0 != pthread_mutex_destroy(&table->philos[i].philo_m))
			return (quit(ERR_MUTEX_DESTROY));
	}
	if (0 != pthread_mutex_destroy(&table->print_m))
		return (quit(ERR_MUTEX_DESTROY));
	if (0 != pthread_mutex_destroy(&table->table_m))
		return (quit(ERR_MUTEX_DESTROY));
	return (0);
}

int dinner_served(t_table *table)
{
	pthread_t	monitor;
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
	if (0 != pthread_create(&monitor, NULL, &monitor_f, table))
		return (quit(ERR_THREAD_CREATE));
	if (0 != pthread_join(monitor, NULL))
		return (quit(ERR_THREAD_JOIN));
	if (all_finished_execution(table))
		destrroy_mutex(table);
	return (0);
}
