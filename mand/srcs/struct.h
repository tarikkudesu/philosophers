/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 20:01:55 by tamehri           #+#    #+#             */
/*   Updated: 2024/02/24 12:29:41 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define ERR_ARG_NUM	"Error : wrong number of arguments"
# define ERR_ARG_FORMAT	"Error : argument format"
# define G				"\033[32m"
# define N				"\033[0m"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>

typedef struct s_philos	t_philos;

struct s_philos
{
	int		philos;
	int		forks;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		num_eat;
	int		stop;
};

#endif
