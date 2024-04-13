/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:58:48 by tamehri           #+#    #+#             */
/*   Updated: 2024/04/13 10:10:52 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

// static int	all_finished_execution(t_table *table)
// {
// 	long	i;

// 	return (1);
// 	while (1)
// 	{
// 		i = 0;
// 		while (rb_mutex(&table->philos[i].philo_m, \
// 			&table->philos[i].out) == true && i < table->philos_n)
// 			i++;
// 		if (i == table->philos_n)
// 			break ;
// 	}
// 	return (1);
// }

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

// static int	clean_table(t_table *table)
// {
// 	long	i;

// 	i = -1;
// 	while (++i < table->philos_n)
// 	{
// 		if (0 != pthread_mutex_destroy(&table->forks[i].fork_m))
// 			return (quit(PTHREAD_MUTEX_DESTROY));
// 		if (0 != pthread_mutex_destroy(&table->philos[i].philo_m))
// 			return (quit(PTHREAD_MUTEX_DESTROY));
// 	}
// 	if (0 != pthread_mutex_destroy(&table->print_m))
// 		return (quit(PTHREAD_MUTEX_DESTROY));
// 	if (0 != pthread_mutex_destroy(&table->table_m))
// 		return (quit(PTHREAD_MUTEX_DESTROY));
// 	free(table->philos);
// 	free(table->forks);
// 	return (0);
// }

int	main(int ac, char **av)
{
	t_table	table;

	if (ac != 5 && ac != 6)
		return (quit(ERROR_ARGS));
	if (-1 == parsing(&table, av + 1))
		return (1);
	if (fill_table(&table))
		return (1);
	// print_philos(&table);
	dinner_served(&table);
	// if (all_finished_execution(&table))
	// 	clean_table(&table);
}
