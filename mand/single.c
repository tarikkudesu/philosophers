/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 13:42:27 by tamehri           #+#    #+#             */
/*   Updated: 2024/04/13 15:29:39 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	*dinner(void *param)
{
	t_table	*table;
	long	time_stamp;

	table = (t_table *)param;
	time_stamp = get_current_time() - rl_mutex(&table->table_m, \
		&table->simu_start_time);
	print_status(table->philos, FORK);
	ft_usleep(table->philos, table->t_die);
	print_status(table->philos, DIED);
	return (NULL);
}

int	single_philo(t_table *table)
{
	table->simu_start_time = get_current_time();
	if (0 != pthread_create(&table->philos[0].thread_id, \
		NULL, &dinner, table))
		return (quit(PTHREAD_CREATE));
	if (0 != pthread_join(table->philos[0].thread_id, NULL))
		return (quit(PTHREAD_CREATE));
	return (0);
}
