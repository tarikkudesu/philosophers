/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:16:28 by tamehri           #+#    #+#             */
/*   Updated: 2024/04/13 15:30:05 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	quit(t_errors _error_type)
{
	if (_error_type == ERR_DEF)
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
	else
		return (-1);
	return (-1);
}
