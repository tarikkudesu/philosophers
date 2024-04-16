/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:16:28 by tamehri           #+#    #+#             */
/*   Updated: 2024/04/15 10:03:10 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos_bonus.h"

void	putendl_fd(char *s, int fd)
{
	if (!s || fd < 0)
		return ;
	while (*s)
		write(fd, s++, 1);
	write(fd, "\n", 1);
}

int	quit(t_errors _error_type)
{
	if (_error_type == ERROR_DEF)
		putendl_fd("Error", 2);
	else if (_error_type == ERROR_MAL)
		putendl_fd("Error : malloc", 2);
	else if (_error_type == ERROR_ARGS)
		putendl_fd("\033[31mError : wrong number of arguments\033[0m", 2);
	else if (_error_type == ERROR_TIME)
		putendl_fd("\033[31mError : time should be more 60ms\033[0m", 2);
	else if (_error_type == ERROR_FORMAT)
		putendl_fd("\033[31mError : argument format\033[0m", 2);
	else if (_error_type == PTHREAD_CREATE)
		putendl_fd("\033[31mError : pthread_create\033[0m", 2);
	else if (_error_type == PTHREAD_JOIN)
		putendl_fd("\033[31mError : pthread_join\033[0m", 2);
	else if (_error_type == PTHREAD_DETACH)
		putendl_fd("\033[31mError : pthread_detach\033[0m", 2);
	else if (_error_type == PTHREAD_MUTEX_INIT)
		putendl_fd("\033[31mError : pthread_mutex_init\033[0m", 2);
	else if (_error_type == PTHREAD_MUTEX_DESTROY)
		putendl_fd("\033[31mError : pthread_mutex_destroy\033[0m", 2);
	else if (_error_type == SEM_OPEN)
		putendl_fd("\033[31mError : sem_open\033[0m", 2);
	else if (_error_type == SEM_POST)
		putendl_fd("\033[31mError : sem_post\033[0m", 2);
	else if (_error_type == SEM_WAIT)
		putendl_fd("\033[31mError : sem_wait\033[0m", 2);
	else if (_error_type == SEM_UNLINK)
		putendl_fd("\033[31mError : sem_unlink\033[0m", 2);
	else if (_error_type == SEM_CLOSE)
		putendl_fd("\033[31mError : sem_close\033[0m", 2);
	else if (_error_type == ERROR_FORK)
		putendl_fd("\033[31mError : fork\033[0m", 2);
	else if (_error_type == ERROR_WAIT)
		putendl_fd("\033[31mError : waitpid\033[0m", 2);
	else
		return (-1);
	return (-1);
}

