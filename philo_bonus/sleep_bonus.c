/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:51:42 by tamehri           #+#    #+#             */
/*   Updated: 2024/04/17 09:46:11 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos_bonus.h"

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
void	ft_usleep(t_philos *philo, long micro)
{
	long	start;

	(void)philo;
	start = get_current_time();
	while ((get_current_time() - start) < micro)
		;
	return ;
}

