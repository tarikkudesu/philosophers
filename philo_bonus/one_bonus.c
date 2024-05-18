/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 13:42:27 by tamehri           #+#    #+#             */
/*   Updated: 2024/05/18 14:27:47 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos_bonus.h"

static void	one_philo_routine(t_table *table)
{
	print_status(table->philos, FORK);
	ft_usleep(table->t_die);
	print_status(table->philos, DIED);
	exit(0);
}

int	one_philo(t_table *table)
{
	pid_t	pid;

	table->simu_start_time = get_current_time();
	pid = fork();
	if (-1 == pid)
		return (_error(ERROR_FORK));
	if (!pid)
		one_philo_routine(table);
	waitpid(pid, NULL, 0);
	return (0);
}
