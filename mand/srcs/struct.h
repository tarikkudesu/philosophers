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
# define ERR_TIME		"Error : time should be more 60ms"
# define ERR_MAL		"Error : malloc"
# define ERR_MUTEX_INIT	"Error : pthread_mutex_init"
# define G				"\033[32m"
# define R				"\033[31m"
# define N				"\033[0m"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <pthread.h>

typedef struct s_philos	t_philos;
typedef struct s_table	t_table;
typedef struct s_fork	t_fork;

struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
};


struct s_philos
{
	int			tid;
	long		meals_eaten;
	bool		full;
	int			last_meal_time;
	t_fork		*right_fork;
	t_fork		*left_fork;
	t_table		*table;
	pthread_t	thread_id;
};

struct s_table
{
	long		t_die;
	long		t_eat;
	long		t_sleep;
	int			num_eat;
	int			stop;
	int			simulation_start_time;
	int			end_simulation;
	t_philos	*philos;
	t_fork		*forks;
	long		philos_n;
	long		forks_n;
};

#endif
