/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:58:45 by tamehri           #+#    #+#             */
/*   Updated: 2024/04/04 18:29:33 by tamehri          ###   ########.fr       */
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

bool		b_mutex_read(pthread_mutex_t *mutex, bool *var);
long		l_mutex_read(pthread_mutex_t *mutex, long *var);
void		b_mutex_read_and_write(pthread_mutex_t *mutex, bool *var, bool value);
void		l_mutex_read_and_write(pthread_mutex_t *mutex, long *var, long value);
long		get_current_time();
void		ft_usleep(long micro);
int 		dinner_served(t_table *table);

int			parsing(t_table *table, char **av);
void		putendl_fd(char *s, int fd);
int			ft_atoi(const char *str);
int			quit(char *s);



/* FUNCTIONS */
void	*monitor(void *param);
void	print_status_d(t_philos *philo, char *status, long time, long i);
void	print_status(t_philos *philo, char *status, long time);
void	l_mutex_read_and_write(pthread_mutex_t *mutex, long *var, long value);
void	b_mutex_read_and_write(pthread_mutex_t *mutex, bool *var, bool value);
long	l_mutex_read(pthread_mutex_t *mutex, long *var);
bool	b_mutex_read(pthread_mutex_t *mutex, bool *var);
int		fill_table(t_table *table);

#endif
