/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 20:01:55 by tamehri           #+#    #+#             */
/*   Updated: 2024/02/24 09:42:51 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define ERR_ARG_NUM	"Error : wrong number of arguments"
# define ERR_ARG_FORMAT	"Error : argument format"

typedef struct s_philos	t_philos;

struct s_philos
{
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
};


#endif
