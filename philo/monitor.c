/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:04:04 by tamehri           #+#    #+#             */
/*   Updated: 2024/04/22 15:29:54 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

static bool	philo_died(t_philos *philo)
{
	long	passed;
	long	t_die;

	pthread_mutex_lock(&philo->philo_m);
	passed = get_current_time() - philo->last_eaten \
		- philo->table->simu_start_time;
	pthread_mutex_unlock(&philo->philo_m);
	t_die = philo->table->t_die;
	if (passed >= t_die)
		return (true);
	return (false);
}

void	*monitor(void *param)
{
	int		i;
	t_table	*table;

	table = (t_table *)param;
	while (simu_ended(table) == false)
	{
		i = -1;
		while (++i < table->philos_n && simu_ended(table) == false)
		{
			if (philo_died(table->philos + i))
			{
				pthread_mutex_lock(&table->table_m);
				table->end_simu = true;
				pthread_mutex_unlock(&table->table_m);
				print_status(table->philos + i, DIED);
			}
		}
	}
	return (NULL);
}
