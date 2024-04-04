/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:04:04 by tamehri           #+#    #+#             */
/*   Updated: 2024/04/04 18:38:30 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	all_started_execution(t_table *table)
{
	long	i;

	while (1)
	{
		i = 0;
		while (b_mutex_read(&table->philos[i].philo_m, \
			&table->philos[i].all_in) == true && i < table->philos_n)
			i++;
		if (i == table->philos_n)
			break ;
	}
	return (1);
}

void	*monitor(void *param)
{
	long	meals_number;
	t_table	*table;
	long	i;

	table = (t_table *)param;
	all_started_execution(table);
	while (b_mutex_read(&table->table_m, &table->end_simulation) == false)
	{
		i = -1;
		while (++i < table->philos_n)
		{
			long	time;
		
			time = l_mutex_read(&table->philos->philo_m, &table->philos[i].last_meal_time);
			if (get_current_time() - time > table->t_die)
			{
				// time = l_mutex_read(&table->philos->philo_m, &table->philos[i].last_meal_time);
				b_mutex_read_and_write(&table->table_m, &table->end_simulation, true);
				print_status_d(&table->philos[i], ST_DIED, get_current_time(), get_current_time() - time);
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
