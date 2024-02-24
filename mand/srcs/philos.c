/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:58:48 by tamehri           #+#    #+#             */
/*   Updated: 2024/02/23 20:32:26 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	main(int ac, char **av)
{
	t_philos	table;

	if (ac != 4 && ac != 5)
		exit_error_code(ERR_ARG_NUM);
	parsing(&table, av + 1);
}
