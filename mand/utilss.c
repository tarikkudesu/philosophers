/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilss.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:51:26 by tamehri           #+#    #+#             */
/*   Updated: 2024/04/13 15:29:28 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

bool	simu_ended(t_table *table)
{
	return (rb_mutex(&table->table_m, &table->end_simu));
}

void	wl_mutex(pthread_mutex_t *mutex, long *var, long value)
{
	pthread_mutex_lock(mutex);
	*var = value;
	pthread_mutex_unlock(mutex);
}

void	wb_mutex(pthread_mutex_t *mutex, bool *var, bool value)
{
	pthread_mutex_lock(mutex);
	*var = value;
	pthread_mutex_unlock(mutex);
}

long	rl_mutex(pthread_mutex_t *mutex, long *var)
{
	long	value;

	pthread_mutex_lock(mutex);
	value = *var;
	pthread_mutex_unlock(mutex);
	return (value);
}

bool	rb_mutex(pthread_mutex_t *mutex, bool *var)
{
	bool	value;

	pthread_mutex_lock(mutex);
	value = *var;
	pthread_mutex_unlock(mutex);
	return (value);
}
