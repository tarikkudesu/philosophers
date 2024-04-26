/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:58:45 by tamehri           #+#    #+#             */
/*   Updated: 2024/04/26 11:54:42 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_BONUS_H
# define PHILOS_BONUS_H

# include "struct_bonus.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <signal.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>

char		*ft_strjoin(char const *s1, char const *s2);
void		ft_usleep(t_philos *philo, size_t milliseconds);
int			fill_table(t_table *table);
size_t		get_current_time(void);

int			parsing(t_table *table, char **av);
int			_error(t_errors _error_type);
void		putendl_fd(char *s, int fd);
int			quit(t_errors _error_type);
int			ft_atoi(const char *str);

void		print_status(t_philos *philo, t_status status);
bool		check_death(t_philos *philo);
int			one_philo(t_table *table);
int			routine(t_philos *philo);

#endif
