/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 20:01:55 by tamehri           #+#    #+#             */
/*   Updated: 2024/05/06 10:22:52 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_BONUS_H
# define STRUCT_BONUS_H

# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>

typedef struct s_philos	t_philos;
typedef struct s_table	t_table;
typedef enum e_status	t_status;
typedef enum e_errors	t_errors;

struct s_philos
{
	int				philo_id;
	pid_t			process_id;
	char			*sem_name;
	sem_t			*philo_s;
	t_table			*table;
};

struct s_table
{
	size_t			t_die;
	size_t			t_eat;
	size_t			t_sleep;
	int				philos_n;
	size_t			meals_nbr;
	size_t			last_eaten;
	size_t			meals_eaten;
	size_t			simu_start_time;
	sem_t			*end_simu_s;
	sem_t			*full_s;
	sem_t			*fork_s;
	sem_t			*print_s;
	t_philos		*philos;
};

enum e_status
{
	DIED,
	FORK,
	EATING,
	SLEEPING,
	THINKING,
};

enum e_errors
{
	ERROR,
	SEM_OPEN,
	ERROR_MAL,
	ERROR_ARGS,
	ERROR_FORK,
	ERROR_TIME,
	ERROR_FORMAT,
	PTHREAD_CREATE,
};

#endif
