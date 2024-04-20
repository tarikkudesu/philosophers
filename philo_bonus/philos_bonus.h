/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:58:45 by tamehri           #+#    #+#             */
/*   Updated: 2024/04/20 11:19:18 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_BONUS_H
# define PHILOS_BONUS_H

# include "struct_bonus.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

char		*ft_strjoin(char const *s1, char const *s2);
void		ft_usleep(t_philos *philo, long micro);
int			fill_table(t_table *table);
long		get_current_time(void);

int			parsing(t_table *table, char **av);
void		putendl_fd(char *s, int fd);
int			quit(t_errors _error_type);
int			ft_atoi(const char *str);
char		*ft_itoa(int n);

void		print_status(t_philos *philo, t_status status);
int			one_philo(t_table *table);
void		routine(t_philos *philo);

#endif
