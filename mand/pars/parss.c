/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parss.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 20:29:36 by tamehri           #+#    #+#             */
/*   Updated: 2024/02/24 09:43:23 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/philos.h"

void	parsing(t_philos *table, char **av)
{
	int	i;

	i = 0;
	(void)table;
	while (*(av + i))
	{
		if (!are_digits(*(av + i)))
			exit_error_code(ERR_ARG_FORMAT);
		i++;
	}
}
