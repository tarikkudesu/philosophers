/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:58:45 by tamehri           #+#    #+#             */
/*   Updated: 2024/02/26 17:59:51 by tamehri          ###   ########.fr       */
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

/* FUNCTIONS */
size_t  get_current_time();
void    ft_usleep(size_t micro);
void	assign_forks(t_philos *philos, t_table *table, int i);
int     dinner_served(t_table *table);
int		init_philos(t_table *table);
int		init_mutex(t_table *table);
int		init_data(t_table *table);

int 	parsing(t_table *table, char **av);
void	putendl_fd(char *s, int fd);
int		ft_atoi(const char *str);
int	    quit(char *s);

#endif
