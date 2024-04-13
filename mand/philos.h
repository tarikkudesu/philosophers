/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:58:45 by tamehri           #+#    #+#             */
/*   Updated: 2024/04/13 15:29:45 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H

# include "struct.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

# include <fcntl.h>

long		get_current_time(void);
void		ft_usleep(t_philos *philo, long micro);
int			fill_table(t_table *table);
int			dinner_served(t_table *table);

int			parsing(t_table *table, char **av);
void		putendl_fd(char *s, int fd);
int			ft_atoi(const char *str);

void		*have_dinner(void *param);
void		monitor(t_table *table);
int			single_philo(t_table *table);
int			quit(t_errors _error_type);
bool		simu_ended(t_table *table);
void		print_status(t_philos *philo, t_status status);
void		wl_mutex(pthread_mutex_t *mutex, long *var, long value);
void		wb_mutex(pthread_mutex_t *mutex, bool *var, bool value);
long		rl_mutex(pthread_mutex_t *mutex, long *var);
bool		rb_mutex(pthread_mutex_t *mutex, bool *var);

#endif
