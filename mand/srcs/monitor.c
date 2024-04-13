/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:04:04 by tamehri           #+#    #+#             */
/*   Updated: 2024/04/13 10:18:05 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

static void	all_started_execution(t_table *table)
{
	long tmp;
	while (1)
	{
		tmp = rl_mutex(&table->table_m, &table->start_monitor);
		if (tmp == table->philos_n)
			break ;
	}
}

static bool	philo_died(t_philos *philo)
{
	long	elapsed;
	long	t_die;

	if (rb_mutex(&philo->philo_m, &philo->full) == true)
		return (false);
	elapsed = get_current_time() - rl_mutex(&philo->philo_m, &philo->last_eaten);
	t_die = philo->table->t_die;
	if (elapsed > t_die)
		return (true);	
	return (false);
}

void	*monitor(void *param)
{
	t_table	*table;
	iter	i;

	table = (t_table *)param;
	all_started_execution(table);
	while (rb_mutex(&table->table_m, &table->end_simu) == false)
	{
		i = -1;
		while (++i < table->philos_n && rb_mutex(&table->table_m, &table->end_simu) == false)
		{
			if (philo_died(table->philos + i))
			{
				wb_mutex(&table->table_m, &table->end_simu, true);
				print_status(table->philos + i, DIED, 0, 0);
			}
			// if (rl_mutex(&table->table_m, &table->start_monitor) == 0)
			// 	wb_mutex(&table->table_m, &table->end_simu, true);
		}
	}
	return (NULL);
}
