/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usleep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:51:42 by tamehri           #+#    #+#             */
/*   Updated: 2024/04/04 18:20:15 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/philos.h"

long	get_current_time()
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(long micro)
{
	long	start_time;

	start_time = get_current_time();
	while (1)
	{
		if (get_current_time() - start_time >= micro)
			break ;
		usleep(50);
	}
}
