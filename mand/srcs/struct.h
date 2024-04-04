/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 20:01:55 by tamehri           #+#    #+#             */
/*   Updated: 2024/04/04 15:06:43 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define ERR_ARG_NUM		"\033[31mError : wrong number of arguments\033[0m"
# define ERR_TIME			"\033[31mError : time should be more 60ms\033[0m"
# define ERR_MUTEX_DESTROY	"\033[31mError : pthread_mutex_destroy\033[0m"
# define ERR_MUTEX_INIT		"\033[31mError : pthread_mutex_init\033[0m"
# define ERR_ARG_FORMAT		"\033[31mError : argument format\033[0m"
# define ERR_THREAD_CREATE	"\033[31mError : pthread create\033[0m"
# define ERR_THREAD_JOIN	"\033[31mError : pthread_join\033[0m"
# define ERR_MAL			"\033[31mError : malloc\033[0m"
# define G					"\033[32m"
# define R					"\033[31m"
# define N					"\033[0m"
# define ST_DIED			"died"
# define ST_EAT				"is eating"
# define ST_SLEEP			"is sleeping"
# define ST_THINK			"is thinking"
# define ST_FORK			"has taken a fork"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <pthread.h>

typedef struct s_philos	t_philos;
typedef struct s_table	t_table;
typedef struct s_fork	t_fork;

struct s_table
{
	long			t_die;
	long			t_eat;
	long			t_sleep;
	long			philos_n;
	long			forks_n;
	long			meals_number;
	long			simulation_start_time;
	bool			end_simulation;
	bool			ready;
	t_fork			*forks;
	t_philos		*philos;
	pthread_mutex_t	print_m;
	pthread_mutex_t	table_m;
};

struct s_philos
{
	int				tid;
	bool			out;
	bool			full;
	bool			dead;
	long			last_meal_time;
	long			meals_eaten;
	t_fork			*right_fork;
	t_fork			*left_fork;
	t_table			*table;
	pthread_t		thread_id;
	pthread_mutex_t	philo_m;
};

struct s_fork
{
	pthread_mutex_t	fork_m;
	int				fork_id;
};

#endif
