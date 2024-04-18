/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:58:48 by tamehri           #+#    #+#             */
/*   Updated: 2024/04/17 16:47:10 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos_bonus.h"

/* void	print_philos(t_table *table) */
/* { */
/* 	printf("\n\n"); */
/* 	t_philos *philos; */
/* 	for (long i = 0; i < table->philos_n; i++) { */
/* 		philos = table->philos + i; */
/* 		printf("philospher %3d, (right : %s, left : %s)\n", philos->pid, philos->right_fork->name, philos->left_fork->name); */
/* 	} */
/* } */

int	main(int ac, char **av)
{
	t_table	table;

	if (ac != 5 && ac != 6)
		return (quit(ERROR_ARGS));
	if (-1 == parsing(&table, av + 1))
		return (1);
	if (-1 == fill_table(&table))
		return (1);
	dinner_served(&table);
	/* clean_table(&table); */
}

