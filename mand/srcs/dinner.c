/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:19:00 by tamehri           #+#    #+#             */
/*   Updated: 2024/02/27 15:19:18 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void    *routine(void *param)
{
    t_philos    *philo;

    philo = (t_philos *)param;
    printf("philo %d started the routine\n", philo->tid);
    return (NULL);
}

int dinner_served(t_table *table)
{
    int i;

    i = -1;
    while (++i < table->philos_n)
    {
        if (-1 == pthread_create(&table->philos[i].thread_id, NULL, routine, &table->philos[i]))
            return (quit(ERR_THREAD_CREATE));
        pthread_detach(table->philos[i].thread_id);
    }
    // i = -1;
    // while (++i < table->forks_n)
    // {
    //     if (-1 == pthread_join(table->philos[i].thread_id, NULL))
    //         return (quit(ERR_THREAD_CREATE));
    // }
    return (0);
}
