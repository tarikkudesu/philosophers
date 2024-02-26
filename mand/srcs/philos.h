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
void	assign_forks(t_philos *philos, t_table *table, int i);
int		init_philos(t_table *table);
int		init_mutex(t_table *table);
int		init_data(t_table *table);

int		ft_atoi(const char *str);
int 	parsing(t_table *table, char **av);
int	    quit(char *s);
void	putendl_fd(char *s, int fd);

#endif
