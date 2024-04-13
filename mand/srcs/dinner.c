/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:19:00 by tamehri           #+#    #+#             */
/*   Updated: 2024/04/13 10:17:58 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	synchronize(t_philos *philo)
{
	while (rb_mutex(&philo->table->table_m, &philo->table->ready) == false)
		;
	wl_mutex(&philo->philo_m, &philo->last_eaten, get_current_time());
	pthread_mutex_lock(&philo->table->table_m);
	philo->table->start_monitor++;
	pthread_mutex_unlock(&philo->table->table_m);
	if (philo->tid % 2 == 0)
		ft_usleep(philo, philo->table->t_eat / 2);
}

void	eating(t_philos *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork_m);
	print_status(philo, FORK, 1, philo->left_fork->fork_id);
	pthread_mutex_lock(&philo->right_fork->fork_m);
	print_status(philo, FORK, 2, philo->right_fork->fork_id);
	wl_mutex(&philo->philo_m, &philo->last_eaten, get_current_time());
	philo->meals_eaten++;
	print_status(philo, EATING, 0, 0);
	ft_usleep(philo, philo->table->t_eat);
	if (philo->table->meals_nbr > 0 \
		&& philo->meals_eaten == philo->table->meals_nbr)
		wb_mutex(&philo->philo_m, &philo->full, true);
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
			break ;
		eating(philo);
		print_status(philo, SLEEPING, 0, 0);
		ft_usleep(philo, philo->table->t_sleep);
		print_status(philo, THINKING, 0, 0);
	}
	// if (philo->full)
	// {
	// 	pthread_mutex_lock(&philo->table->table_m);
	// 	philo->table->start_monitor--;
	// 	pthread_mutex_unlock(&philo->table->table_m);
	// }
	return (NULL);
}

int	dinner_served(t_table *table)
{
	iter		i;
	pthread_t	monitor_id;

	if (1 == table->philos_n)
		;// Later
	i = -1;
	while (++i < table->philos_n)
	{
		if (0 != pthread_create(&table->philos[i].thread_id, \
			NULL, &have_dinner, &table->philos[i]))
			return (quit(PTHREAD_CREATE));
		// pthread_detach(table->philos[i].thread_id);
	}
	if (0 != pthread_create(&monitor_id, NULL, &monitor, table))
		return (quit(PTHREAD_CREATE));
	table->simu_start_time = get_current_time();
	wb_mutex(&table->table_m, &table->ready, true);
	if (0 != pthread_join(monitor_id, NULL))
		return (quit(PTHREAD_JOIN));
	i = -1;
	while (++i < table->philos_n)
	{
		if (0 != pthread_join(table->philos[i].thread_id, NULL))
			return (quit(PTHREAD_JOIN));
	}
	return (0);
}

