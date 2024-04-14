/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:19:00 by tamehri           #+#    #+#             */
/*   Updated: 2024/04/14 19:32:34 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	print_status(t_philos *philo, t_status status)
{
	long	time_stamp;

	if (philo->full)
		return ;
	time_stamp = get_current_time() - rl_mutex(&philo->table->table_m, \
		&philo->table->simu_start_time);
	pthread_mutex_lock(&philo->table->print_m);
	if (status == DIED)
		printf("%ld\t%d\t%s\n", time_stamp, philo->tid, "died");
	else if (status == FORK && simu_ended(philo->table) == false)
		printf("%ld\t%d\t%s\n", time_stamp, philo->tid, "has taken a fork");
	else if (status == FORK && simu_ended(philo->table) == false)
		printf("%ld\t%d\t%s\n", time_stamp, philo->tid, "has taken a fork");
	else if (status == EATING && simu_ended(philo->table) == false)
		printf("%ld\t%d\t%s\n", time_stamp, philo->tid, "is eating");
	else if (status == SLEEPING && simu_ended(philo->table) == false)
		printf("%ld\t%d\t%s\n", time_stamp, philo->tid, "is sleeping");
	else if (status == THINKING && simu_ended(philo->table) == false)
		printf("%ld\t%d\t%s\n", time_stamp, philo->tid, "is thinking");
	pthread_mutex_unlock(&philo->table->print_m);
}

void	synchronize(t_philos *philo)
{
	while (rb_mutex(&philo->table->table_m, &philo->table->ready) == false)
		;
	wl_mutex(&philo->philo_m, &philo->last_eaten, get_current_time());
	pthread_mutex_lock(&philo->table->table_m);
	philo->table->start_monitor++;
	pthread_mutex_unlock(&philo->table->table_m);
	if (philo->tid % 2)
		ft_usleep(philo, philo->table->t_eat);
}

void	eating(t_philos *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork_m);
	print_status(philo, FORK);
	pthread_mutex_lock(&philo->right_fork->fork_m);
	print_status(philo, FORK);
	wl_mutex(&philo->philo_m, &philo->last_eaten, get_current_time());
	philo->meals_eaten++;
	print_status(philo, EATING);
	ft_usleep(philo, philo->table->t_eat);
	if (philo->table->meals_nbr > 0 \
		&& philo->meals_eaten == philo->table->meals_nbr)
		philo->full = true;
	pthread_mutex_unlock(&philo->left_fork->fork_m);
	pthread_mutex_unlock(&philo->right_fork->fork_m);
}

void	*have_dinner(void *param)
{
	t_philos	*philo;

	philo = (t_philos *)param;
	synchronize(philo);
	while (simu_ended(philo->table) == false)
	{
		if (philo->full)
		{
			pthread_mutex_lock(&philo->table->table_m);
			philo->table->start_monitor--;
			pthread_mutex_unlock(&philo->table->table_m);
			break ;
		}
		eating(philo);
		print_status(philo, SLEEPING);
		ft_usleep(philo, philo->table->t_sleep);
		print_status(philo, THINKING);
	}
	return (NULL);
}
