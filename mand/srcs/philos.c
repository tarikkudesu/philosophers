/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:58:48 by tamehri           #+#    #+#             */
/*   Updated: 2024/04/04 14:45:00 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	l_mutex_read_and_write(pthread_mutex_t *mutex, long *var, long value)
{
	pthread_mutex_lock(mutex);
	*var = value;
	pthread_mutex_unlock(mutex);
}

void	b_mutex_read_and_write(pthread_mutex_t *mutex, bool *var, bool value)
{
	pthread_mutex_lock(mutex);
	*var = value;
	pthread_mutex_unlock(mutex);
}

long	l_mutex_read(pthread_mutex_t *mutex, long *var)
{
	long	value;

	pthread_mutex_lock(mutex);
	value = *var;
	pthread_mutex_unlock(mutex);
	return (value);
}

bool	b_mutex_read(pthread_mutex_t *mutex, bool *var)
{
	bool	value;

	pthread_mutex_lock(mutex);
	value = *var;
	pthread_mutex_unlock(mutex);
	return (value);
}

void	print_arg(t_table *table)
{
	printf("\033[33mnumber_of_philosophers\t\t\t\t%ld\n", table->philos_n);
	printf("number_of_forks\t\t\t\t\t%ld\n", table->forks_n);
	printf("time_to_die\t\t\t\t\t%ld micro seconds\n", table->t_die);
	printf("time_to_eat\t\t\t\t\t%ld micro seconds\n", table->t_eat);
	printf("time_to_sleep\t\t\t\t\t%ld micro seconds\n", table->t_sleep);
	printf("number_of_times_each_philosopher_must_eat\t%ld\n", table->meals_number);
}

void	print_philos(t_table *table)
{
	printf("\n\n");
	t_philos *philos;
	for (long i = 0; i < table->philos_n; i++) {
		philos = table->philos + i;
		printf("philospher %3d, (right : %3d, left : %3d)\n", philos->tid, philos->right_fork->fork_id, philos->left_fork->fork_id);
		printf("\tmeals_eaten %ld, full : %d\n", philos->meals_eaten, philos->full);
	}
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac != 5 && ac != 6)
		return (quit(ERR_ARG_NUM));
	if (-1 == parsing(&table, av + 1))
		return (quit(NULL));
	// print_arg(&table);
	if (init_data(&table))
		return (1);
	// print_philos(&table);
	dinner_served(&table);
}
