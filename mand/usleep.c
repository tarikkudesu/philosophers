/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usleep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:51:42 by tamehri           #+#    #+#             */
/*   Updated: 2024/04/13 15:29:32 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(t_philos *philo, long micro)
{
	long	start_time;
	long	rem_time;
	long	elapsed;

	start_time = get_current_time();
	while (get_current_time() - start_time < micro)
	{
		elapsed = get_current_time() - start_time;
		rem_time = micro - elapsed;
		if (simu_ended(philo->table))
			break ;
		if (rem_time > 1e3)
			usleep(rem_time / 2);
		else
		{
			while (get_current_time() - start_time < micro)
				;
			break ;
		}
	}
}
