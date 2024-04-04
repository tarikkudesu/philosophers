/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:51:26 by tamehri           #+#    #+#             */
/*   Updated: 2024/04/04 18:29:17 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	print_status_d(t_philos *philo, char *status, long time, long i)
{
	long	time_stamp;

	pthread_mutex_lock(&philo->table->print_m);
	time_stamp = time - l_mutex_read(&philo->table->table_m, \
		&philo->table->simulation_start_time);
	printf("%ld\t%d\t%s .  %ld\n", time_stamp, philo->tid, status, i);
	pthread_mutex_unlock(&philo->table->print_m);
}

void	print_status(t_philos *philo, char *status, long time)
{
	long	time_stamp;

	if (b_mutex_read(&philo->table->table_m, &philo->table->end_simulation) == true)
		return ;
	pthread_mutex_lock(&philo->table->print_m);
	time_stamp = time - l_mutex_read(&philo->table->table_m, \
		&philo->table->simulation_start_time);
	printf("%ld\t%d\t%s\n", time_stamp, philo->tid, status);
	pthread_mutex_unlock(&philo->table->print_m);
}

void	l_mutex_read_and_write(pthread_mutex_t *mutex, long *var, long value)
{
	pthread_mutex_lock(mutex);
	*var = value;
	pthread_mutex_unlock(mutex);
}

void	b_mutex_read_and_write(pthread_mutex_t *mutex, bool *var, bool value)
{
	pthread_mutex_lock(mutex);
	*var = value;
	pthread_mutex_unlock(mutex);
}

long	l_mutex_read(pthread_mutex_t *mutex, long *var)
{
	long	value;

	pthread_mutex_lock(mutex);
	value = *var;
	pthread_mutex_unlock(mutex);
	return (value);
}

bool	b_mutex_read(pthread_mutex_t *mutex, bool *var)
{
	bool	value;

	pthread_mutex_lock(mutex);
	value = *var;
	pthread_mutex_unlock(mutex);
	return (value);
}
