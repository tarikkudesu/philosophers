/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:58:48 by tamehri           #+#    #+#             */
/*   Updated: 2024/02/25 10:55:02 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	print_arg(t_philos *table)
{
	printf("\033[33mnumber_of_philosophers\t\t\t\t%d\n", table->philos);
	printf("number_of_forks\t\t\t\t\t%d\n", table->forks);
	printf("time_to_die\t\t\t\t\t%d\n", table->t_die);
	printf("time_to_eat \t\t\t\t\t%d\n", table->t_eat);
	printf("time_to_sleep\t\t\t\t\t%d\n", table->t_sleep);
	printf("number_of_times_each_philosopher_must_eat\t%d\n", table->num_eat);
}

int	main(int ac, char **av)
{
	t_philos	table;

	if (ac != 5 && ac != 6)
		return (quit(ERR_ARG_NUM));
	if (-1 == parsing(&table, av + 1))
		return (quit(NULL));
	print_arg(&table);
}
