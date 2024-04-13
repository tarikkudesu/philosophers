/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:51:26 by tamehri           #+#    #+#             */
/*   Updated: 2024/04/13 10:19:20 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

bool	simu_ended(t_table *table)
{
	return (rb_mutex(&table->table_m, &table->end_simu));
}

void	print_status(t_philos *philo, t_status status, int f, int fd)
{
	long	time_stamp;

	if (philo->full)
		return ;
	time_stamp = get_current_time() - rl_mutex(&philo->table->table_m, \
		&philo->table->simu_start_time);
	pthread_mutex_lock(&philo->table->print_m);
	if (status == DIED)
		printf("%ld\t%d\t%s\n", time_stamp, philo->tid, "died");
	else if (status == FORK && simu_ended(philo->table) == false && f == 1)
		printf("%ld\t%d\t%s : %d\n", time_stamp, philo->tid, "has taken a left fork", fd);
	else if (status == FORK && simu_ended(philo->table) == false)
		printf("%ld\t%d\t%s : %d\n", time_stamp, philo->tid, "has taken a right fork", fd);
	else if (status == EATING && simu_ended(philo->table) == false)
		printf("%ld\t%d\t%s\n", time_stamp, philo->tid, "is eating");
	else if (status == SLEEPING && simu_ended(philo->table) == false)
		printf("%ld\t%d\t%s\n", time_stamp, philo->tid, "is sleeping");
	else if (status == THINKING && simu_ended(philo->table) == false)
		printf("%ld\t%d\t%s\n", time_stamp, philo->tid, "is thinking");
	pthread_mutex_unlock(&philo->table->print_m);
}

void	wl_mutex(pthread_mutex_t *mutex, long *var, long value)
{
	pthread_mutex_lock(mutex);
	*var = value;
	pthread_mutex_unlock(mutex);
}

void	wb_mutex(pthread_mutex_t *mutex, bool *var, bool value)
{
	pthread_mutex_lock(mutex);
	*var = value;
	pthread_mutex_unlock(mutex);
}

long	rl_mutex(pthread_mutex_t *mutex, long *var)
{
	long	value;

	pthread_mutex_lock(mutex);
	value = *var;
	pthread_mutex_unlock(mutex);
	return (value);
}

bool	rb_mutex(pthread_mutex_t *mutex, bool *var)
{
	bool	value;

	pthread_mutex_lock(mutex);
	value = *var;
	pthread_mutex_unlock(mutex);
	return (value);
}
